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
--start \n");
    fgets(answer, 9, stdin);
    
    int equality = strcmp(answer, option_s);
    if(equality == 0)
    {
        return 1;
    } else {
        return 0;
    }
    
}

int main()
{
    
    int option = start();
    if(option == 1)
    {
        printf("We are here");
    } else {
        printf("We are there");
    }
    return 0;
    
}
