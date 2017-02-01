#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int formatchar(char letter)
{
    if(islower(letter)){
        return letter - 'a';
    } else if(isupper(letter))
    {
        return letter - 'A';
    } else{
        return 0;
    }
}

int changeCounter(int counter, int max)
{
    if(counter < max - 1)
    {
        counter++;
    } else{
        counter = 0;
    }
    return counter;
}

int checkKey(string key){
    for(i = 0;i < key.length;i++){
        if(!(islower(key[i] || isupper(key[i])))){
            return 1;
        }
    }   
}

int main(int argc, string argv[])
{   
    string key,str;
    int count = 0;
    if(argc == 2)
    {
        key = argv[1];
    } else
    {   
        prinf("You didn't give me a key. :(");
        return 1;
    }
    str = GetString();
    if(checkKey(str) == 1){
        return 1;
    }
    
    for(int i=0;i<strlen(str);i++)
    {   
        char currentChar = str[i];
        int changed = currentChar + formatchar(key[count]);
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
        

