import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():

    user_id = session["user_id"]
    transaction_data = db.execute("SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash_data = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_data[0]["cash"]
    """Show portfolio of stocks"""
    return render_template("index.html", database = transaction_data, cash = cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)

        if not symbol:
            return apology("Symbol not given")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("No Symbol Found")

        if not str(shares).isdigit():
            return apology("You cannot purchase negative shares.")

        # if str(shares).isdecimal():
        #     return apology("You cannot purchase partial shares.")

        transaction_val = stock["price"] * shares

        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash1 = user_cash[0]["cash"]

        if user_cash1 < transaction_val:
            return apology("Not Enough Money")

        new_cash = user_cash1 - transaction_val

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, stock["price"], date)
        flash("Stock Bought^^")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions = transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html"), 400
    else:
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Symbol not given")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("No Symbol Found")

        return render_template("quoted.html", name= stock["name"], price = stock["price"], symbol = stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Enter Username")
        if not password:
            return apology("Enter Password")
        if not confirmation:
            return apology("Enter Confirmation")
        if password != confirmation:
            return apology("Passwords do not match")
        hash = generate_password_hash(password)

        try:
            new = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("Username Exists")

        session["user_id"] = new
        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbol_user = db.execute("SELECT symbol FROM transactions WHERE user_id = :id GROUP BY symbol HAVING SUM(shares) > 0", id= user_id)
        return render_template("sell.html", symbols = [row["symbol"] for row in symbol_user])
    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("Symbol not given")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("No Symbol Found")

        if shares < 0:
            return apology("Atleast 1 Share Required")


        transaction_val = stock["price"] * shares

        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash1 = user_cash[0]["cash"]

        user_shares = db.execute("SELECT shares from transactions WHERE user_id= :id AND symbol= :symbol GROUP BY symbol", id=user_id, symbol= symbol)
        user_shares_real = user_shares[0]["shares"]

        if shares > user_shares_real:
            return apology("You Don't Have Enough Stocks")

        new_cash = user_cash1 + transaction_val

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], (-1)*shares, stock["price"], date)
        flash("Stock Sold! ^^")
        return redirect("/")