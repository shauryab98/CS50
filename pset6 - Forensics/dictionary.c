/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"


/**
 * Returns true if word is in dictionary else false.
 */
trie* start = NULL;
int numOfWords = 0;
bool check(const char* word)
{
    trie* current = start; 
    for(int i = 0;i < strlen(word);i++)
    {
        int index = word[i] == '\'' ? 26 : tolower(word[i]) - 'a';
        current = current->array[index];
        if(current == NULL)
        {
            return false;
        }
    }
    // this condition is to correctly handle substrings.
    if(current->array[27]!=NULL)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Open the dictionary file.
    FILE* file;
    file = fopen(dictionary,"r");
    // If the file exists...
    if(file)
    { 
        // If the load function is called twice, this condition makes sure that we don't do it twice.
        if(start==NULL)
        {
            start = malloc(sizeof(trie));
            for(int i =0; i < 28; i++)
            {
                start->array[i]=NULL;
            }
        }
        else
        {
            fclose(file);
            return true;
        }
        char c = '\0';
        char* word = malloc(LENGTH+1);
        while((c = fgetc(file))!=EOF)
        {  
            int index = 0;            
            for(;c!='\n';index++)
            {
                word[index] = c;
                c=fgetc(file);
            }
            // End the word.
            word[index++] = '\0';             
            // now add it to the trie.
            add(word);
            //Increment the number of words.
            numOfWords++;
        }
        //free the word and close the file.
        free(word);
        fclose(file);        
        return true;       
    }
    return false;
}

void add(char* word)
{
    trie* current = start;
    trie* previous = NULL;
    int i = 0;
    // First go through the trie to reach the point where the word will be further added.
    while(current!=NULL && i < strlen(word))
    {
        previous = current;
        int index = ((word[i] == '\'') ? 26 : word[i] - 'a');        
        current = current->array[index];  
        i++;      
    }
    // decrement i to go back one char in the word.
    i--;
    // add the rest of the word.
    for(;i < strlen(word);i++)
    {
        int index = (word[i] == '\'') ? 26 : word[i] - 'a';
        previous->array[index] = malloc(sizeof(trie));
        previous = previous->array[index];
        for(int i =0; i < 28; i++)
        {
            previous->array[i]=NULL;
        }
    }
    //mark the end of the word.
    previous->array[27] = malloc(sizeof(trie));   
    previous = previous->array[27];  
    for(int i =0; i < 28; i++)
    {
        previous->array[i]=NULL;
    }     
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return the number of words.
    return numOfWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    //call the clear function to free the trie.
    clear(start);
    return true;
}

void clear(trie* current)
{
    //recursive function to clear the trie.
    if(current!=NULL)
    {
        for(int i = 0;i < 28;i++)
        {
            clear(current->array[i]);
        }
        free(current);
    }
}

