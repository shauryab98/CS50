#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,string argv[])
{   
    int key = 0;
    string str;
    if(argc == 2 && atoi(argv[1]) >= 0)
    {
        key = atoi(argv[1]) % 26;
    } else
    {   
        printf("You didn't give me a key. :(\n");
        return 1;
    }
      
    str = GetString();
    
    for(int i = 0; i<strlen(str);i++)
    {   
        char currentChar = str[i];
        int changed = currentChar + key;
        //Checks for the lower case chars.
        if(islower(currentChar))
        {                     
            if(changed > 'z')
            {
                changed = 'a' + (changed%'z') - 1;
            }
            printf("%c",changed);
        } 
        //Checks for the upper case chars.
        else if(isupper(currentChar))
        {
            if(changed > 'Z')
            {
                changed = 'A' + changed%'Z' - 1;
            }
            printf("%c",changed);
        } 
        //The rest remain the same.
        else
        {
            printf("%c",currentChar);
        }
    }
    printf("\n");
}
