#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void)
{
    //getting the owed change
    float owed = get_float("Please provide the owed change:\n ");
    //checking if greater than 0
    while (owed < 0)
    {
        get_float("Please provide the owed change:\n ");
    }
    //apdating value
    int change = round(owed * 100);
    //calculating number of coins
    int coins = 0;

    while ((change - 100) >= 0)
    {
        change -= 100;
        coins += 4;
    }
    while ((change - 25) >= 0)
    {
        change -= 25;
        coins += 1;
    }
    while ((change - 10) >= 0)
    {
        change -= 10;
        coins += 1;
    }
    while ((change - 5) >= 0)
    {
        change -= 5;
        coins += 1;
    }
    while ((change - 1) >= 0)
    {
        change -= 1;
        coins += 1;
    }

    //printing number of coins
    printf("%i\n", coins);
}
