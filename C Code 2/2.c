#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int i, j;
void shuffle(int R[]) { // Set up a function to shuffle the array R of 10 numbers
    for (i=0; i<1000; i++) { // Shuffle 1000 times
        int x = rand()%10;
        int y = rand()%10; // For n=10, select a random number between 0 to 9 as the position of the array R
        int tmp = R[x];
        R[x] = R[y];
        R[y] = tmp; // Switch the position of two numbers
    }    
}

int main() {
    int mode;
    // Begins the game, the code will end only if it reaches the exit in case 4
    printf("Welcome to the number guessing game 1A2B!\n");
    while (1) {
        printf("\nPlease select one of the game modes below.\n");
        printf("**********************************************\n");
        printf("Game mode 1: Guesser (4-digit version).\n");
        printf("Game mode 2: Number setter.\n");
        printf("Game mode 3: Guesser (5-digit version).\n");
        printf("Game mode 4: Exit the game.\n");
        printf("**********************************************\n");
        printf("Enter a number between 1 and 4: ");
        scanf("%d", &mode);
        getchar();

        // The code of the game begins here.
        switch (mode) {
            // Game mode 1
            case 1:
            {
                printf("You are currently the guesser for the 4-digit version.\n");
                srand((unsigned)time(NULL)); // Seed the random number generator with the current time
                int R[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Declare an array as domain of the random number, we use the first four numbers as the random number after shuffling
                shuffle(R); // Call out the function

                int a, b, G[4], times=0; // 'a' and 'b' are the counters for how many As and Bs, 'G[4]' is an integer array to store the user's guess as 4 digits, 'times' is to store the number of tries

                do {
                    while(1) {
                        printf("Guess a 4 digit number with different digits¡G");
                        int num, count=0;
                        while(1) {
                            char c = getchar(); // Reads one character and retures its ASCII value
                            if (isdigit(c)) {  // A function from the <ctype.h>, check if the character is a digit
                                num = c-'0';  // Convert the character to an integer by taking the difference between two ASCII values
                                G[count] = num; // Store the guess into each index of G[4]
                                count++;
                            }
                            if (c=='\n') break; // Break out of the while loop if 'enter' button is detected
                        }
            
                        if (count<4 || count>4) {
                            printf("You didn't enter a 4 digit number, try again.\n");
                            continue; // If the digits of guess is less than or more than 4, continue to guess
                        }
            
                        if(G[0]==G[1] || G[0]==G[2] || G[0]==G[3] || G[1]==G[2] || G[1]==G[3] || G[2]==G[3]) {
                            printf("You guessed a number with repeated digits, try again.\n");
                            continue; // If any of the digits are repeated, continue to guess
                        }
                        break;
                    }
        
                    a=0, b=0;
                    for (i=0; i<4; i++) {
                        for (j=0; j<4; j++) { // Set up a double for loop to compare each digit of the random number to every digit of the guess
                            if(R[i]==G[j] && i!=j) {
                                b++; // If a digit of the random number matches a digit of the guess, but the position is not the same, increment b by 1
                            }
                            if(R[i]==G[j] && i==j) {
                                a++; // If a digit of the random number matches a digit of the guess, and the position is the same, increment a by 1
                            }
                        }
                    }
                    times++; // Increment number of tries after one guess
                    printf("%dA%dB\n", a, b);
                } while (a!=4); // Use a do-while loop to repeat while the user didn't guess 4As

                printf("Congrats! You guessed the number %d%d%d%d after %d tries.\n", R[0], R[1], R[2], R[3], times);
                break; // Return to main menu after completing game mode 1
            }
            
            // Game mode 2
            case 2:
            {
                printf("You are currently the number setter.\n");
                srand((unsigned)time(NULL)); // Seed the random number generator with the current time
                int a, R[4]; // 'a' is the counter for how many As, 'R[4]' is an integer array to store the user's random number as 4 digits
    
                while(1) {
                    printf("Set up a 4 digit number with different digits¡G");
                    int num, count=0;
                    while(1) {
                        char c = getchar(); // Reads one character and retures its ASCII value
                        if (isdigit(c)) {  // A function from the <ctype.h>, check if the character is a digit
                            num = c-'0';  // Convert the character to an integer by taking the difference between two ASCII values
                            R[count] = num; // Store the guess into each index of R[4]
                            count++;
                        }
                        if (c=='\n') break; // Break out of the while loop if 'enter' button is detected
                    }
            
                    if (count<4 || count>4) {
                        printf("You didn't enter a 4 digit number, try again.\n");
                        continue; // If the digits of input is less than or more than 4, continue to input
                    }
    
                    if(R[0]==R[1] || R[0]==R[2] || R[0]==R[3] || R[1]==R[2] || R[1]==R[3] || R[2]==R[3]) {
                        printf("You entered a number with repeated digits, try again.\n");
                        continue; // If any of the digits are repeated, continue to input
                    }
                    break;
                }
    
                int times=0; // 'times' is to store the number of tries
                do {    
                    int G[4]; // 'G[4]' is an integer array to store the computer's guess as 4 digits
                    while(1) {
                        for(i=0; i<4; i++) {
                            int x = rand()%10; // Select a random number between 0 to 9
                            G[i] = x; // Store it as the i position of array G
                        }
            
                        if(G[0]==G[1] || G[0]==G[2] || G[0]==G[3] || G[1]==G[2] || G[1]==G[3] || G[2]==G[3]) {
                        continue; // If any of the digits are repeated, continue to guess
                        }
                        break; // If a number with non-repeating digits is chosen, exit the loop
                    }
                    
                    int i, j;
                    a=0; // Declare the value of 'a' here so it will reset every time the do-while loop is run
                    for (i=0; i<4; i++) {
                        for (j=0; j<4; j++) { // Set up a double for loop to compare each digit of the random number to every digit of the guess
                            if(R[i]==G[j] && i==j) {
                                a++; // If a digit of the random number matches a digit of the guess, and the position is the same, increment a by 1
                            }
                        }
                    }
                    times++; // Increment number of tries after one guess
                } while (a!=4); // Use a do-while loop to repeat while the computer didn't guess 4As

                printf("The computer guessed the number %d%d%d%d after %d tries.\n", R[0], R[1], R[2], R[3], times);
                break; // Return to main menu after completing game mode 2
            }
            
            // Game mode 3
            case 3:
            {
                printf("You are currently the guesser for the 5-digit version.\n");
                srand((unsigned)time(NULL)); // Seed the random number generator with the current time
                int R[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Declare an array as domain of the random number, we use the first five numbers as the random number after shuffling
                shuffle(R); // Call out the function
                
                int a, b, G[5], times=0; // 'a' and 'b' are the counters for how many As and Bs, 'G[5]' is an integer array to store the user's guess as 5 digits, 'times' is to store the number of tries

                do {
                    while(1) {
                        printf("Guess a 5 digit number with different digits¡G");
                        int num, count=0;
                        while(1) {
                            char c = getchar(); // Reads one character and retures its ASCII value
                            if (isdigit(c)) {  // A function from the <ctype.h>, check if the character is a digit
                                num = c-'0';  // Convert the character to an integer by taking the difference between two ASCII values
                                G[count] = num; // Store the guess into each index of G[5]
                                count++;
                            }
                            if (c=='\n') break; // Break out of the while loop if 'enter' button is detected
                        }
            
                        if (count<5 || count>5) {
                            printf("You didn't enter a 5 digit number, try again.\n");
                            continue; // If the digits of guess is less than or more than 5, continue to guess
                        }
            
                        if(G[0]==G[1] || G[0]==G[2] || G[0]==G[3] || G[0]==G[4] || G[1]==G[2] || G[1]==G[3] || G[1]==G[4] || G[2]==G[3] || G[2]==G[4] || G[3]==G[4]) {
                            printf("You guessed a number with repeated digits, try again.\n");
                            continue; // If any of the digits are repeated, continue to guess
                        }
                        break;
                    }
                    
                    a=0, b=0;
                    for (i=0; i<5; i++) {
                        for (j=0; j<5; j++) { // Set up a double for loop to compare each digit of the random number to every digit of the guess
                            if(R[i]==G[j] && i!=j) {
                                b++; // If a digit of the random number matches a digit of the guess, but the position is not the same, increment b by 1
                            }
                            if(R[i]==G[j] && i==j) {
                                a++; // If a digit of the random number matches a digit of the guess, and the position is the same, increment a by 1
                            }
                        }
                    }
                    times++; // Increment number of tries after one guess
                    printf("%dA%dB\n", a, b);
                } while (a!=5); // Use a do-while loop to repeat while the user didn't guess 4As

                printf("Congrats! You guessed the number %d%d%d%d%d after %d tries.\n", R[0], R[1], R[2], R[3], R[4], times);
                break; // Return to main menu after completing game mode 3
            }
            
            // Game mode 4
            case 4:
            {
                char choice; // Declare a char variable to store y or n
                while (1) {
                    printf("Are you sure you want to exit? (Y/N)\n");
                    scanf(" %c", &choice);
                    if (toupper(choice) == 'Y') { // toupper is a fcn in ctype.h, it will convert lowercase letters to uppercase
                        printf("Thanks for playing!"); // If the user enters 'Y' or 'y', end the game
                        system("pause");
                        return 0; // End the program
                    }
                    
                    if (toupper(choice) == 'N') {
                        printf("Returning to main menu.\n");  // If the user enters 'N' or 'n', return to the main menu
                        break; // Exit the while loop
                    }
                
                    else {
                        printf("Invalid input, please enter Y or N.\n"); // Repeat the while loop for invalid input
                    }
                }
                break; // Exit the switch if the user enters no
            }
                
            default:
                printf("Invalid choice, please choose again.\n");
                break; // Return to main menu for invalid input
        }
    }
}
