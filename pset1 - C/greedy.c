#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    float change;
    int coins = 0;
    int coinArray[4]= {25,10,5,1};
    //Asking the user for input.
    do
    {
        printf("O hai! How much change is owed?\n"); 
        change = GetFloat();  
    } while (change < 0);
    
    int cents = (int)(change*100 + 0.5);
    //This calculates the minimum number of coins.
    if(cents != 0)
    {
            for(int i = 0;i < 4;i++)
            {   
                int currentCoin = coinArray[i];
                coins += cents/currentCoin;
                cents -= (cents/currentCoin)*currentCoin;
            }
    }
    printf("%i\n",coins); 
}
