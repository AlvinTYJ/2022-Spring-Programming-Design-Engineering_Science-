#include <stdio.h>  //Standard input/output functions
#include <stdlib.h> //Standard library functions
#include <time.h>   //Time functions

int main(void)
{
    srand((unsigned)time(NULL)); //The seed for random number generator of the current time
    int i, j, pulls=1000000, fiveS=0, fourS=0; //Set the pulls to 1 million, and the counters for 4 and 5 star characters obtained
    
    while(i <= pulls) //Drawing pool of 5-Star
    {
        int draw = rand()%1000+1; //Generates a random number between 1 and 1000
        if(draw <= 6) {
            fiveS++; //If the random number is equal or below 6 (probability of 0.6%), increase fiveS obtained by 1
        }
        i++; //Increment the loop counter
    }
    
    while(j <= pulls) //Drawing pool of 4-Star
    {
        int draw = rand()%1000+1;
        if(draw <= 51) { //If the random number is equal or below 51 (probability of 5.1%), increase fourS obtained by 1
            fourS++;
        }
        j++;
    }
    
    printf("Total pulls in pool A: %d\n", pulls);
    printf("Number of 5-Star obtained : %d\n", fiveS);
    printf("Probability for drawing a 5-Star:%f%%\n\n", ((double)fiveS / pulls) * 100); //To show the overall probability for 5-Star
    
    printf("Total pulls in pool B: %d\n", pulls);
    printf("Number of 4-Star obtained : %d\n", fourS);
    printf("Probability for drawing a 4-Star:%f%%\n", ((double)fourS / pulls) * 100); //To show the overall probability for 4-Star
    
    system("pause"); //Pause the program before exiting
    return 0; //To show successful execution
}
