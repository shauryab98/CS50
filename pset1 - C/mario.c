#include <stdio.h>
#include <cs50.h>

int main(void)
{    
    int height;
    //This part asks for the input. 
    do
    {
        printf("Height: ");
        height = GetInt();   
    } while (height < 0 || height > 23);
    
    //This code does the mario stuff.
    
    for(int i = 1;i <= height; i++)
    {
        for(int j = 1;j <= height+1; j++)
        {
            if(j <= height - i)
            {
                printf(" ");
            } 
            else
            {
               printf("#"); 
            }
        }
        
        printf("\n");
    }
}
