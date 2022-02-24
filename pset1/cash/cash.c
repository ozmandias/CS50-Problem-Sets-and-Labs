#include<cs50.h>
#include<math.h>
#include<stdio.h>

int calculatecoins(int convertedcoins);

int main(void)
{
    float change;
    int changeincoins;
    int coins = 0;

    //asks user how much change is owed and asks them again if they enter a negative value.
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    //converts the change in dollars to coins.
    changeincoins = round(change * 100);
    //printf("Change owed in coins: %i\n", changeincoins);

    //calculates the total coins required to make the change based on converted change in coins.
    coins = calculatecoins(changeincoins);

    //printf("Collected change: %0.2f\n",change);
    //printf("Collected coins: %i\n",coins);
    //printf("Required coins: %i\n", coins);

    //prints the total coins required to make the change.
    printf("%i\n", coins);
}

//calculates the total coins required to make the change by subtracting the change with quarters(25 cents), dimes(10 cents), nickels(5 cents), pennies(1 cent).
int calculatecoins(int convertedcoins)
{
    int totalcoins = 0;
    for (int i = convertedcoins; i > 0; i = i - 1)
    {
        if (convertedcoins >= 25)
        {
            convertedcoins = convertedcoins - 25;
            totalcoins = totalcoins + 1;
        }
        else if (convertedcoins >= 10)
        {
            convertedcoins = convertedcoins - 10;
            totalcoins = totalcoins + 1;
        }
        else if (convertedcoins >= 5)
        {
            convertedcoins = convertedcoins - 5;
            totalcoins = totalcoins + 1;
        }
        else if (convertedcoins >= 1)
        {
            convertedcoins = convertedcoins - 1;
            totalcoins = totalcoins + 1;
        }
    }
    //printf("Change left: %i\n",convertedcoins);
    return totalcoins;
}