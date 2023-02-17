#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>

int start()
{   
    
    char answer[10];
    // Newline character to simplify comparison.
    char option_s[10] = "--start\n";
    printf("Hello, welcome to game of pong. If you would like to start a new \n\
game, please type in: \n \
--start \n \
Type anything else to exit. \n");
    fgets(answer, 9, stdin);
    
    int equality = strcmp(answer, option_s);
    if(equality == 0)
    {
        
        return 1;
        
    } else {
        
        return 0;
        
    }
    
}

// Intro into pointers and memory allocation:
int **create_playing_field(int size_x, int size_y)
{
    
    int **field;
    field = malloc(size_x * sizeof(int * ));
    for(int x = 0; x < size_x; x++)
    {
        
        field[x] = malloc(size_y * sizeof(int));
        for(int i = 0; i < size_y; i++)
        {
            field[x][i] = 1;
        }
        
    }
    
    // Temporarily here for Debugging, etc. 
    /*
    printf("%s", "\n");
    for(int x = 0; x < size_x; x++)
    {
        for(int y = 0; y < size_y; y++)
        {
            printf(" %d ", field[x][y]);
        }
        
        printf("%s", "\n");
        
    }
    */
    return field;
    
}

int draw_field(int **field, int size_x, int size_y)
{
    
    printf("%s", "\n");
    for(int x = 0; x < size_x; x++)
    {
        for(int y = 0; y < size_y; y++)
        {
            printf(" %d ", field[x][y]);
        }
        
        printf("%s", "\n");
        
    }
    
}

struct Ball
{
    int posx;
    int posy;
    int map_repr;
    int speed;
    int direction;
    int sway;
};

struct Ponger
{
    int posx;
    int posy;
    int size;
    int map_repr;
};

struct PlayingField
{
    int sizex;
    int sizey;
    int **field;
};

int main()
{
    int game = 0;
    int option = start();
    if(option == 1)
    {
        
        struct PlayingField pf;
        pf.sizex = 10;
        pf.sizey = 10;
        pf.field = create_playing_field(pf.sizex, pf.sizey);
        
        struct Ponger pg1;
        pg1.posx = 3;
        pg1.posy = 0;
        pg1.size = 3;
        pg1.map_repr = 5;
        
        struct Ponger pg2;
        pg2.posx = 3;
        pg2.posy = (pf.sizey-1);
        pg2.size = 3;
        pg2.map_repr = 5;
        
        struct Ball ball;
        ball.posx = 5;
        ball.posy = 5;
        ball.map_repr = 0;
        ball.speed = 0;
        ball.direction = 0;
        ball.sway = 0;
        
        // Place ponger on the map.
        for(int x = 0; x < pg1.size; x++)
        {
            pf.field[pg1.posx-x][pg1.posy] = pg1.map_repr;
            pf.field[pg2.posx-x][pg2.posy] = pg2.map_repr;
            pf.field[ball.posx][ball.posy] = ball.map_repr;
        }
        
        draw_field(pf.field, pf.sizex, pf.sizey);
        
        game = 1;
        
        /////// Positions for map drawing /////////
        ball.speed = 1;
        ball.direction = 1;
        int old_ball_x = ball.posx;
        int old_ball_y = ball.posy;
        int old_pg1_x = pg1.posx;
        int old_pg1_y = pg1.posy;
        int old_pg2_x = pg2.posx;
        int old_pg2_y = pg2.posy;
        
        /////////////////////
        ///// THREADING /////
        ///// Move pg1  /////
        /////////////////////
        void * move_pg(void *)
        {
            char wsad[2];
            fgets(wsad, 2, stdin);
            if(strcmp(wsad, "s") == 0)
            {
                if(pg1.posx+1 <= pf.sizex-1)
                {
                    pg1.posx += 1;
                }
                else
                {
                    printf("SHOUT !!!");
                }
            }
            else if(strcmp(wsad, "w") == 0)
            {   
                if(pg1.posx-3 >= 0)
                {
                    pg1.posx -= 1;
                }
                else
                {
                    printf("SHOUT !!!");
                }
            }
        }
        pthread_t thread;
        
        //////////////////////
        ///// THREADING //////
        ///// Move pg2  //////
        //////////////////////
        void * move_pg2(void *)
        {
            // ball.posx+1 to center the ponger on the ball.
            if(pg2.posx != ball.posx+1)
            {
                if(pg2.posx <= ball.posx)
                {
                    pg2.posx += 1;
                } else if(pg2.posx >= ball.posx && pg2.posx-3 >= 0) {
                    pg2.posx -= 1;
                }
            }
        }
        pthread_t thread2;
        
        ///// Main Game /////////////
        while(game == 1)
        {   
            
            sleep(1.0);
            printf("The game is on!\n");

            ////////////////////
            //// Move ponger ///////////////////////////////
            // Use separate threads for ponger movements ///
            ////////////////////////////////////////////////
            pthread_create(&thread, NULL, move_pg, NULL);
            pthread_create(&thread2, NULL, move_pg2, NULL);
            
            // Sway to make ball randomly go straight, upwards or downwards.
            // Very crude for now.
            switch (ball.sway)
            {
                case 1:
                {
                    ball.posx -= ball.speed;
                    break;
                }
                case 2:
                {
                    ball.posx += ball.speed;
                    break;
                }
                case 3:
                {
                    ball.posx += ball.speed;
                    break;
                }
                case 4:
                {
                    ball.posx -= ball.speed;
                    break;
                }
            }
            //////////////////////////////////////////////////
            // Move ball in the opposite direction if it reaches end of PlayingField
            // Later to be changed, if ball reaches the end. End the game.
            if(ball.posy == 1)
            {   
                if(pf.field[ball.posx][ball.posy-1] != 1)
                {
                    ball.direction = 2;
                    ball.sway = rand()%2;
                } 
            } 
            else if(ball.posy == 0)
            {
                printf("Player1 lost the game !");
                break;
            }
            else if(ball.posy == (pf.sizey - 2))
            {
                if(pf.field[ball.posx][ball.posy+1] != 1)
                {
                    ball.direction = 1;
                    ball.sway = rand()%2;
                }
            }
            else if(ball.posy == (pf.sizey - 1))
            {
                printf("Player2 lost the game !");
                break;
            }
            if(ball.posx == 0)
            {
                ball.sway = 3;
            }
            else if(ball.posx == (pf.sizex - 1))
            {
                ball.sway = 4;
            }
            /////////// Temporarily here for testing. ///////
            switch (ball.direction)
            {
                case 1:
                {
                    ball.posy -= ball.speed;
                    break;
                }
                case 2:
                {
                    ball.posy += ball.speed;
                    break;
                }
            }
            
            // Update position of objects on the map
            // Clear field behind the ball as it is moving.
            for(int i = 0; i < pg1.size; i++)
            {
                pf.field[old_ball_x][old_ball_y] = 1;
                old_ball_x = ball.posx;
                old_ball_y = ball.posy;
                /* Pongers positions saved for cleaning*/
                ///////////////////////
                pf.field[old_pg1_x-i][old_pg1_y] = 1;
                pf.field[old_pg2_x-i][old_pg2_y] = 1;
                ///////////////////////
            }
            
            /* Place ponger on the map.
            Save its current position as old position for map update. */
            for(int x = 0; x < pg1.size; x++)
            {   
                old_pg1_x = pg1.posx;
                old_pg1_y = pg1.posy;
                old_pg2_x = pg2.posx;
                old_pg2_y = pg2.posy;
                pf.field[pg1.posx-x][pg1.posy] = pg1.map_repr;
                pf.field[pg2.posx-x][pg2.posy] = pg2.map_repr;
                pf.field[ball.posx][ball.posy] = ball.map_repr;
            }
            system("clear");
            draw_field(pf.field, pf.sizex, pf.sizey);
        }
        
    } else {
        printf("We are there");
    }
    
    return 0;
    
}
