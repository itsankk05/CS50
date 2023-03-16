from cs50 import get_float
while True:
    n = get_float("Change Owned: ")
    if n >= 0:
        break
cents = n * 100
coins = 0

while cents >= 25:
    cents = cents - 25
    coins += 1
while cents >= 10:
    cents = cents - 10
    coins += 1
while cents >= 5:
    cents = cents - 5
    coins += 1
while cents >= 1:
    cents = cents - 1
    coins += 1

print(coins)