#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
    
    int option = start();
    if(option == 1)
    {
        
        struct Ponger pg1;
        pg1.posx = 3;
        pg1.posy = 0;
        pg1.size = 3;
        pg1.map_repr = 5;
        
        struct PlayingField pf;
        pf.sizex = 10;
        pf.sizey = 10;
        pf.field = create_playing_field(pf.sizex, pf.sizey);
        
        // Place ponger on the map.
        for(int x = 0; x < pg1.size; x++)
        {
            pf.field[pg1.posx-x][pg1.posy] = pg1.map_repr;
        }
        
        draw_field(pf.field, pf.sizex, pf.sizey);

        
    } else {
        
        printf("We are there");
        
    }
    return 0;
    
}
