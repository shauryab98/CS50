/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	//This is binary search
	int start = 0;
	int end = n - 1;
	
	//Check through whole array.
	while(end >= start){		
	    int average = (start + end)/2;
		int current = values[average];
		//Check if middle number is correct.
		if(current == value)
		{
			return true;			
		} 
		//Check the right part.
		else if (current < value)
		{
			start = average + 1;
		} 
		//Check the left part.
		else if(current > value)
		{
			end = average - 1;
		}
	}
	//Since nothing has been found, return false.
	return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement an O(n^2) sorting algorithm(Insertion Sort)
    //Insertion sort.
    
    //Go through all the elements.
    for(int i = 1;i < n;i++)
    {
        //Select the "i"th element and compare it with previous elements.
        int current = values[i];
        for(int j = i-1;j >= 0;j--)
        {   
            int swap;
            //If any previous element is larger than current,swap.
            if(values[j] > current)
            {
               swap = values[j];
               values[j] = current;
               values[j+1] = swap;
            } else if (values[j] < current)
			{
				break;
			}
        }
    }
}

