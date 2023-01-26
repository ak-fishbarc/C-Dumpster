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
    printf("%s", "\n");
    for(int x = 0; x < size_x; x++)
    {
        for(int y = 0; y < size_y; y++)
        {
            printf("%d", field[x][y]);
        }
        
        printf("%s", "\n");
        
    }

    return field;
    
}


int main()
{
    
    int option = start();
    if(option == 1)
    {
        printf("We are here");
        create_playing_field(10, 10);
    } else {
        printf("We are there");
    }
    return 0;
    
}
