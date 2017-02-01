#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Function declarations.
int formatKey(char);
int changeCounter(int, int);
int checkKey(string);

int main(int argc, string argv[])
{   
    //Checks if number of arguments is correct. Asks for the users input.
    string key,str = NULL;    
    if(argc == 2)
    {
        key = argv[1];
        if(checkKey(key) == 1)
        {
           printf("Your key must be a combination of a-z and/or A-Z");
           return 1;
        }
    } else
    {   
        printf("You didn't give me a key. :(\n");
        return 1;
    }
    
    str = GetString();
    //This converts the key into correponding numbers.
    int keyArray[strlen(key)];
    for(int i = 0;i < strlen(key);i++)
    {
        keyArray[i] = formatKey(key[i]);
    }
    //This is the encrypter.
    int count = 0;
    for(int i=0;i<strlen(str);i++)
    {   
        char currentChar = str[i];
        int changed = currentChar + keyArray[count];
        
        //Checks for the lower case chars.
        if(islower(currentChar))
        {                     
            if(changed > 'z')
            {
                changed = 'a' + (changed%'z') - 1;
            }
            printf("%c",changed);
            count = changeCounter(count,strlen(key));
        } 
        //Checks for the upper case chars.
        else if(isupper(currentChar))
        {
            if(changed > 'Z')
            {
                changed = 'A' + changed%'Z' - 1;
            }
            printf("%c",changed);
            count = changeCounter(count,strlen(key));
        } 
        //The rest remain the same.
        else
        {
            printf("%c",currentChar);
        }
    }
    printf("\n");
}

//These are the function definitions.
int formatKey(char letter)
{   
    if(islower(letter))
    {
        return letter - 'a';
    } else
    {
        return letter - 'A';
    }
}      
int changeCounter(int counter, int max)
{
    if(counter < max - 1)
    {
        counter++;
    } else
    {
        counter = 0;
    }
    return counter;
}
int checkKey(string key){
    for(int i = 0;i < strlen(key);i++)
    {
        if(!(islower(key[i]) || isupper(key[i])))
        {
            return 1;
        }
    } 
    return 0;  
}
