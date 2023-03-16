#include <cs50.h>
#include<math.h>
#include <stdio.h>
#include<ctype.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

float input;
float cents;
int main(void)
{
    input = get_float("Change: ");
    // Ask how many cents the customer is owed
    //for( i=0 ; i < len(input) ; i++)
    if (isdigit(input))
    {
        cents = input*100;
        continue;
    }

    // Calculate the number of quarters to give the customer
    int quaters = floor(cents / 25);
    cents = cents - (quaters * 25);

    // Calculate the number of dimes to give the customer
    int dimes = floor(cents / 10);
    cents = cents - (dimes * 10);

    // Calculate the number of nickels to give the customer
    int nickels = floor(cents / 5);
    cents = cents - (nickels * 5);

    // Calculate the number of pennies to give the customer
    int pennies = floor(cents / 1);
    cents = cents - (pennies * 1);

    // Sum coins
    int coins = quaters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

