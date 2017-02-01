/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

//empty space coordinates
int empty_x = 0;
int empty_y = 0;

//# of numbers are their right position.
int correct = 0;
bool correctStatus[81];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
bool even(int num);
int absolute(int num);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if  (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if  (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }
    
    empty_x = d-1;
    empty_y = d-1;
    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if  (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if  possible, else report illegality
        if  (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF fifteen\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // Convert the size of grid to largest number to print.    
    int number = d*d - 1;
    // Make a multidimensional array that represents the game.
    for(int i = 0;i < d;i++)
    {
        for(int j = 0;j < d;j++)
        {
            board[i][j] = number;
            number--;
        }
    }
    
    //If even, swap 1 and 2.
    if (even(d))
    {
        board[d - 1][d - 3] = 1;
        board[d - 1][d - 2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Print the multi dimensional array onto the terminal.
    printf("\n");
    for(int i = 0;i < d;i++)
    {   
        printf("    ");
        for(int j = 0;j < d;j++)
        {
            if (board[i][j] == 0){
                printf(" _  ");
            } else
            {
                printf("%2d  ",board[i][j]);
            }
        }
        printf("\n\n");
    }
}

/**
 * if  tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // x and y are the coordinates of the tile.
    int x,y;
    //Find x,y by searching the "board" array.
    for(int i = 0;i < d;i++)
    {
        for(int j = 0;j < d;j++)
        {
            if (board[i][j] == tile)
            {
                x = i;
                y = j;
            }
        }
        
    }
    //This checks if the blank space is at border.
    if ((x == empty_x && absolute(y - empty_y) == 1) || ((y == empty_y) && absolute(x - empty_x) == 1)) 
    {   
        // Swap the blank space and the user's number.       
        board[x][y] = 0;
        board[empty_x][empty_y] = tile;
        
        //Checks if  the number moved is at the right position.
        if (empty_x*d + empty_y + 1== tile)
        {
            correct++;
            correctStatus[tile] = true;
        } else if(correctStatus[tile])
        {
            correct--;  
            correctStatus[tile] = false;          
        }
        //Change the coordinates of empty space in the array.
        empty_x = x;
        empty_y = y;          
        return true;
    }
    return false;
}   

/**
 * Returns true if  game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // If the number of correct positions is equal to total elements, user wins.
    if(correct == (d*d - 1)){
        return true;
    }
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if  any, before first save
    static bool saved = false;
    if  (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if  (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if  (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if  (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

bool even(int num)
{
    //checks if  number is even
    if (num % 2 == 0)
    {
        return true;
    }
    return false;
}

int absolute(int num)
{
    if  (num > 0)
    {
        return num;
    }
    return -num;
}
