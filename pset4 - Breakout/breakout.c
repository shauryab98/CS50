//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Paddle 
#define PADDLE_Y (HEIGHT - 40.0)
#define PADDLE_WIDTH 75	

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball, int* pointer)

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    //velocity of the ball
    double velocity_y,velocity_x;
    do
	{
    	velocity_x = rand()/((double)RAND_MAX);
    	velocity_y = rand()/((double)RAND_MAX);
    } while((velocity_x < 0.20 || velocity_y < 0.20)||(velocity_x > 0.35 || velocity_y > 0.35));
    
    
    // Collision type 
    // 0:none/ignored; 1:top-left; 2:top-right 3:bottom-left 4:bottom-right;  
    int collision = 0;
    
    // wait for click before starting
    waitForClick(); 
           
   // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // This part moves the paddle...
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {   
                if(getX(event)>PADDLE_WIDTH/2 && getX(event)<WIDTH-PADDLE_WIDTH/2)
                    setLocation(paddle,getX(event)-(PADDLE_WIDTH/2),PADDLE_Y);
            }
        }
        
        //This moves the ball.
        move(ball,velocity_x,velocity_y);
       //Detect the object that the ball collided with. 
        GObject object = detectCollision(window,ball,&collision);
        //Check is there was some collision
        if(collision!=0)
        { 
		    //Check if the hit object is a brick. 
		    if ((object != paddle) && strcmp(getType(object),"GRect")==0)
            {	
                //Remove the bricks and update score.	                   
                removeGWindow(window,object);
                bricks--;
                updateScoreboard(window,label,ROWS*COLS - bricks);
                
                //bounce off the bricks.
                if(((collision==1||collision==3)&&(velocity_x<0)) || ((collision==2 || collision==4)&&(velocity_x>0)))
                {
                    velocity_x = -velocity_x;
                }
                else if(((collision==4||collision==3)&&(velocity_y>0)) || ((collision==2 || collision==1)&&(velocity_y<0)))
                {
                    velocity_y = -velocity_y;
                }
            } 
            //Bouncing off the paddle
            else if (object == paddle)
            {   
                if (getY(ball)+RADIUS >= PADDLE_Y/2)
                {
                    setLocation(ball,getX(ball) - 1,PADDLE_Y - 2*RADIUS - 1); 
                }                      
                velocity_y = -velocity_y;                            
            }
            
        }   
        
        //This makes the ball bounce if it touches the upper edge of window.       
        else if (getY(ball)<=0)
        {                       
            velocity_y = -velocity_y;                        
        }
        // Makes the ball bounce from left and right edges.
        else if (getX(ball)<=0 || getX(ball)+getWidth(ball)>=WIDTH)
        {          
            velocity_x = -velocity_x;    
        }
        //If the ball touches the bottom edge of window.
        else if (getY(ball)+getHeight(ball)>=HEIGHT)
        {   
            removeGWindow(window,ball);
            ball = initBall(window);
            lives--;
            do{
                velocity_x = rand()/((double)RAND_MAX);
                velocity_y = rand()/((double)RAND_MAX);
            } while((velocity_x < 0.20 || velocity_y < 0.20)||(velocity_x > 0.35 || velocity_y > 0.35));
            
            // wait for click before starting
            waitForClick();
         }                       
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Calculate width along with the required gap and the height is 10.   
    int width = WIDTH/COLS - 6 ;
    int height = 10;
    // array of colors
    char* colors[ROWS] = {"#F11A93","#1CE963","#2D7FBC","#EE702E","#DD4B39"};
    for(int i = 0;i < ROWS;i++)
    {
        for(int j = 0;j < COLS;j++)
        {   
            int x = (5 + width)*(j)+5;
            int y = 15 + (5 + height)*(i+1);            
            GRect brick = newGRect(x,y,width,height);
            setColor(brick,colors[i]);
            setFilled(brick,true);
            add(window,brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(getWidth(window)/2 - RADIUS,getHeight(window)/2 - RADIUS,2*RADIUS,2*RADIUS);
    setColor(ball,"Black");
    setFilled(ball,true);
    add(window,ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    double x = (WIDTH - 50.0)/2.0;
    GRect paddle = newGRect(x, PADDLE_Y, PADDLE_WIDTH,10);
    setColor(paddle,"Black");
    setFilled(paddle,true);
    add(window,paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("");
    setLabel(label,"0");
    setFont(label,"SansSerif-36");
    setColor(label,"#D8DDE3");
    setLocation(label,(WIDTH-getWidth(label))/2 ,HEIGHT/2-getHeight(label));
    add(window,label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball, int* pointer)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {   
        *pointer = 1;
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        *pointer = 2;
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        *pointer = 3;
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {   
        *pointer = 4;
        return object;
    }

    // no collision
    *pointer = 0;
    return NULL;
}

