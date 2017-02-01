#include <stdio.h>
#include <cs50.h>

int main(void)
{    
    int height;
    //This part asks for the input. 
    while(true){
        printf("Height:");
        height = GetInt();
        if(height>=0 && height<=23){
            break;
        }
    }
    //This code does the mario stuff.
    for(int i = 1;i <= height; i++){
        for(int j = 1;j <= height; j++){
            if(j <= height - i){
                printf(" ");
            } 
            else{
               printf("#"); 
            }
        }
        printf("  ");
        for(int j = 1;j <= i; j++){
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
