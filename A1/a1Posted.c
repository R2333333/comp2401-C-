#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_POS 70
#define MAX_STR 32
#define TRUE     1
#define FALSE    0

int  randomInt(int);

int timmyMove(char*[], int);

int haroldMove(char*[],int);

int main()
{
    char* pathUpMount[MAX_POS];
    int positionT = 0, positionH = 0;

    srand(time(NULL));

    for(int i=0; i<MAX_POS; ++i)
    {
        pathUpMount[i] = " ";
    }

    while(positionT < MAX_POS-1 && positionH < MAX_POS-1)
    {
        printf("| ");

        for(int i=0; i<MAX_POS; ++i)
            printf("%s", pathUpMount[i]);
        
        positionT = timmyMove(pathUpMount, positionT);
        positionH = haroldMove(pathUpMount, positionH);
        printf("|\n");

        //if(positionT==MAX_POS-1 || positionH==MAX_POS-1)
        //    break;
    }
   
    printf("| ");                                                                               
    for(int i=0; i<MAX_POS; ++i)                                                                
        printf("%s", pathUpMount[i]);
    printf("|\n"); 

    if(positionT == MAX_POS - 1)
        printf("Timmy is the winner!!!\n");
    else printf("Winner is Harold!!!\n");

    return 0;
}


/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max)
{
  return(rand() % max);
}

int timmyMove(char* path[], int position)
{
    int move = randomInt(9);
    int nextPos =position;
    
    path[position] = " ";

    if(move < 5)
        nextPos += 3;
    if(move < 8 && move >=5)
        ++nextPos;
    if(move >= 8) nextPos -= 6;
    
    if(nextPos<0)
        nextPos=position;
    else if(nextPos>=MAX_POS)
        nextPos = MAX_POS - 1;
    path[nextPos] = "T";

    return nextPos;
}

int haroldMove(char* path[], int position)
{
    int move = randomInt(99);
    int nextPos =position;

    path[position] = " ";

    if(move < 20)
        nextPos += 9;
    if(move < 50 && move >= 20)
        ++nextPos;
    if(move >= 50 && move <60)
        nextPos -= 12;
    if(move < 80 && move >= 60)
        nextPos -= 2;

    if(nextPos<0)
        nextPos = position;
    else if(nextPos>=MAX_POS)
        nextPos = MAX_POS - 1;
    path[nextPos] = "H";

    return nextPos;
}
