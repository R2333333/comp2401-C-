//Comments start with "test" used to test the programme
//When testing, uncomment all test comments, the programme
//  will print out all detials of every round of fight
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PIRATENUM 10

typedef struct
{
    char name[10];
    int strength, armour, health;

} HeroType;

typedef struct
{
    int strength, health;

} PirateType;

typedef struct
{
    PirateType *pirates[PIRATENUM];
    int currentNum;

} ArrayType;

void initialTimmy   (HeroType*);
void initialHarold  (HeroType*);
void initialArray   (ArrayType*);

bool fight(HeroType*, ArrayType*);

void cleanHeap(ArrayType*);

int main()
{
    HeroType timmy, harold;
    ArrayType array;
    //int to record how many times did timmy and harold die
    int timmyDie, haroldDie, bothDie, bothSurvive;
    timmyDie    = 0;
    haroldDie   = 0;
    bothDie     = 0;
    bothSurvive = 0;
    /*For test purpose, to know where did them die, uncomment to test.
    int timmyDieAt[100];
    int haroldDieAt[100];
    */
    srand(time(NULL));

    for(int i=0; i<100; ++i)
    {
        initialTimmy(&timmy);
        initialHarold(&harold);
        initialArray(&array);  

/*test        for(int j=0; j<array.currentNum; ++j)                                                           
*           printf("%d %d\n", array.pirates[j]->health,array.pirates[j]->strength); 
*
*        printf("Rond %d \n \n", i);
*/
        while(array.currentNum>0)
        {
//test            printf("------------------------------------\n");
            fight(&timmy, &array);
            fight(&harold, &array);
//test            printf("--------------------------------------\n");
            if(harold.health<=0 && timmy.health<=0)    
            {
//test                printf("Both Dead!!!!!!\n");
                ++bothDie;
                break;
            }
        }
        if(timmy.health<=0 && (harold.health>0))
        {   
//test            timmyDieAt[timmyDie] = i;
            ++timmyDie;
        }
        else if(harold.health<=0 && (timmy.health>0))
        {
//test            haroldDieAt[haroldDie] = i;
            ++haroldDie;
        }
        else if(harold.health>0 && (timmy.health>0))
            ++bothSurvive;
        cleanHeap(&array);
    }

    printf("\nTimmy died: %d",timmyDie);
/*test    printf(" at Round: ");
    for(int die=0;die<timmyDie; ++die)
        printf(" %d,",timmyDieAt[die]);
*/  printf("\nHarold died: %d ",haroldDie);
/*test    printf(" at Round: ");
    for(int die=0;die<haroldDie; ++die)                                                                 
        printf(" %d,",haroldDieAt[die]);  
*/  printf("\nBoth Dead: %d\nBoth Survive: %d", bothDie, bothSurvive);
    printf("\nThe rate of Timmy survive is %d%%, for Harold is %d%%, for both survive is: %d%%,for both dead is: %d%%\n\n",timmyDie,haroldDie, bothSurvive, bothDie);

    return 0;
} 

/*  Funtion:     initialTimmy
 *  Purpose:     To initialize data for Timmy
 *  Parameter:   
 *      *timmy      The pointer of Timmy to be initialized
 */
void initialTimmy(HeroType *timmy)
{   
    strcpy(timmy->name, "Timmy");                                                                    
    timmy->strength  = 5;                                                                            
    timmy->armour    = 5;                                                                            
    timmy->health    = 30;
}

/*  Funtion:     initialHarold
 *  Purpose:     To initialize data for Harold
 *  Parameter:
 *      *harold  The pointer Harold to be initialized
 */
void initialHarold(HeroType *harold)
{
    strcpy(harold->name, "Harold");
    harold->strength = 7;
    harold->armour   = 3;
    harold->health   = 30;
}

/*  Funtion:     initialArray
 *  Purpose:     Takes an array of pirates as parameter to be initialized
 *  Parameter:
 *      *array   The array to be initialized
 */
void initialArray(ArrayType *array)
{
    for(int i=0; i<PIRATENUM; ++i)
    {   
        //allocate each pirates inside the array
        array->pirates[i] = calloc(1,sizeof(PirateType));
    }
    for(int i=0; i<PIRATENUM; ++i)                                                                         
    {   
        //set each pirate's health and strength
        array->pirates[i]->health   = 20;
        array->pirates[i]->strength = (rand()%4)+3;
    }
    //set the number of pirates currently in the array
    array->currentNum = PIRATENUM;
}

/*  Funtion:    fight
 *  Purpose:    Takes an hero and an array of pirates,
 *              then makes the hero fights with the last
 *              pirate in the array,till the hero or pirate
 *              dies. Returns a boolean to indicate if the 
 *              hero dead, for test purpose.
 *  Parameter:  
 *      *hero   The hero to fight
 *      *array  The array of pirates where the hero fights
 *  Return:
 *      heroDie The bool indicating if the hero dead
 */
bool fight(HeroType *hero, ArrayType *array)
{
    if(hero->health<=0)
    {
//test        printf("%s is dead, pass his turn.\n", hero->name);
        return true;
    }
    bool pirateDie, heroDie;
    pirateDie = false;
    heroDie   = false;

//test    printf("%s Health: %d\n", hero->name, hero->health);
        array->pirates[array->currentNum-1]->health -= hero->strength;
//test        printf("%dst Pirate Health: %d\n", 10-array->currentNum+1,array->pirates[array->currentNum-1]->health);
        if(array->pirates[array->currentNum-1]->health <= 0)
        {
            free(array->pirates[array->currentNum-1]);
            --(array->currentNum);
            hero->health += 3;
            pirateDie     = true;
//test            printf("%d pirates left\n \n", array->currentNum);
        }
        if(!pirateDie)
        {
            int pirateTempStrength = (array->pirates[array->currentNum-1]->strength)
                                     +rand()%((array->pirates[array->currentNum-1]->strength)+1);
            hero->health -= (pirateTempStrength>hero->armour)?(pirateTempStrength-hero->armour):0;

            if(hero->health<=0)
                return true;
            //recursively fight until the hero or pirate dead
            fight(hero, array);
        }
    return heroDie;
}

/*  Function:   cleanHeap
 *  Purpose:    To delete allocated elements inside the input array
 *  Parameter:
 *      *array  The array to be cleaned
 */
void cleanHeap(ArrayType *array)
{
    for(int i=0; i<(array->currentNum); ++i)
    {
        free(array->pirates[i]);
    }
}

