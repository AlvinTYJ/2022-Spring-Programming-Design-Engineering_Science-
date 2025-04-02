#include <stdio.h>  //Standard input/output functions
#include <stdlib.h> //Standard library functions
#include <time.h>   //Time functions

int main(void)
{
    srand((unsigned)time(NULL)); //The seed for random number generator of the current time
    int i, j, pulls=1000000, cumulated_pulls=0, fiveS=0, fourS=0; //Set the pulls to 1 million, a variable cumulated pulls for resetting the prob, and the counters for 4 and 5 star characters obtained
        
    for (i=1; i<=pulls; i++) //Drawing pool of 5-Star
    {
        int prob=6; //Set the initial probability to 0.6%
        int draw=rand()%1000+1; //Generates a random number between 1 and 1000
        cumulated_pulls++; 
            
        if (cumulated_pulls>73) {
            prob=6+60*(cumulated_pulls-73); //For every cumulated pulls above 73, set a specific probability which increases by 6% per pull
        }
            
        if (draw<=prob) {
            fiveS++; //If the random number is equal or below the current prob, increase fiveS obtained by 1
            cumulated_pulls=0; //If a 5-Star is drawn, reset the cumulated_pulls counter, thus reset the prob to 0.6%
        }
    }
    
    for (j=1; j<=pulls; j++) //Drawing pool of 4-Star
    {
        int prob=51; //Set the initial probability to 5.1%
        int draw=rand()%1000+1;
        cumulated_pulls++;
            
        if (cumulated_pulls==9) {
            prob=562; //Set the probability to 56.2% for every 9th pull
        }
        
        if (cumulated_pulls==10) {
            prob=994; //Set the probability to 99.4% for every 10th pull
            cumulated_pulls=0; //Reset the counter and prob whether a 4-Star is drawn or not
        }
            
        if (draw<=prob) {
            fourS++; //If the random number is equal or below the current prob, increase fourS obtained by 1
            cumulated_pulls=0; //If a 4-Star is drawn, reset the cumulated_pulls counter, thus reset the prob to 5.1%
        }
    }
    
    printf("Total pulls in pool A: %d\n", pulls);
    printf("Number of 5-Star obtained¡G%d\n", fiveS);
    printf("Probability for drawing a 5-Star:%f%%\n\n", ((double)fiveS/pulls)*100); //To show the overall probability for guaranteed 5-Star system
    
    printf("Total pulls in pool B: %d\n", pulls);
    printf("Number of 4-Star obtained¡G%d\n", fourS);
    printf("Probability for drawing a 4-Star:%f%%\n", ((double)fourS/pulls)*100); //To show the overall probability for guaranteed 4-Star system
    
    system("pause"); //Pause the program before exiting
    return 0; //To show successful execution
}
