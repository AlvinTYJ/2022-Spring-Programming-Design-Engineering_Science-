#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    char suit[9];
    char number[3];
} card; // Create a new data type called "card", which has two attributes "suit" and "number"

void shuffle(card deck[]) {
	int i;
    for (i=0; i<1000; i++) { // Shuffle 1000 times
        int x = rand()%52;
        int y = rand()%52; // Select a random number between 0 to 51 as the index of the deck to swap two cards by switching of the suits and numbers
        card temp = deck[x];
        deck[x] = deck[y];
        deck[y] = temp; // Swap two random cards
    }
}

bool parse_int(char *ch, int *deal) {
    int i=0;
    // The function can directly access and modify the characters in the ch string without needing to use the indirection operator * below
    while (isspace(ch[i])) i++; // Starts checking the ch, move on if blank space is detected, isspace is a fcn from <ctype.h>
    int length = strlen(ch); // Get the length of ch, strlen is from <string.h>
    if (length == i) return false; // If the entire input are blank spaces, return false
  
    char deal_buffer[1024]; // Set a temporary buffer to store each valid input
    int j=0;
    if (ch[i] == '-') {
        deal_buffer[j] = '-'; // Add the minus sign from ch to deal_buffer
        j++;
        i++;
        if (!isdigit(ch[i])) return false; // If the char following after the minus is not a digit, then it is an invalid input
    }
  
    while (i<length && !isspace(ch[i])) { // In the range of length and the char in ch is not a blank space
        if (!isdigit(ch[i])) return false; // If other than digits are detected, like letters and punctuation marks, or even the dot from a decimal, return false
        deal_buffer[j] = ch[i]; // Store the valid digits in the buffer
        j++;
        i++;
    }
  
    deal_buffer[j] = '\0'; // Set a null terminator to make it a proper string
    while (isspace(ch[i])) i++; // Move on for blank spaces
    if (ch[i] != '\0') return false; // While still remains true, if any type of char is detected after blank spaces, return false, ex. "___1___2___"
    *deal = atoi(deal_buffer); // atoi from <stdlib.h> converts string type to int type, and return the value of deal with a pointer
  
    return true; // Return true to indicate successful parsing
}

void dealCards(card deck[], int deal, card hand[]) {
	int i, j;
    for (i=0, j=0; i<52; i++) {
        hand[j] = deck[i]; // After shuffling the cards, copy the first "deal" number of cards from deck to hand, act as dealing the cards
        j++;
    
        if (j==deal) {
            break; // Stop dealing
        }
    }
}

void swapCards(card *card1, card *card2) { // A fcn used in the fcn permute for swapping two cards
    card temp = *card1;
    *card1 = *card2;
    *card2 = temp;
}

void permute(card deck[], int start, int end) {
    static int count=1; // To indicate which sequence is it
    int i;
    if (start==end) { // When a permutation is complete
        printf("\n");
        printf("Sequence %d: \n", count); 
        for (i=0; i<=end; i++) {
            printf("%s of %s\n", deck[i].number, deck[i].suit); // Print out the order of the cards in the sequence
        }
        count++;
    }
	else {
        for (i=start; i<=end; i++) {
            swapCards(&deck[start], &deck[i]); // Swap the card in every i with the card in start position
            permute(deck, start+1, end); // Permute the remaining cards recursively
            swapCards(&deck[start], &deck[i]); // Swapping the cards again to restore the original position
        }
    }
}

int main() {
    srand((unsigned)time(NULL)); // Seed the random number generator with the current time
    int deckSize = 52;
    card deck[deckSize]; // Set an array of card called "deck"
    char suits[][9] = {"Spades", "Hearts", "Diamonds", "Clubs"};
    char numbers[][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    int i, j;
	int k=0;
    for (i=0; i<4; i++) {
        for (j=0; j<13; j++) {
            strcpy(deck[k].suit, suits[i]);
            strcpy(deck[k].number, numbers[j]); // Use strcpy from <string.h> to assign string values to character arrays, a total of 52 times for the deck, so each index of the deck has a unique card
            k++;
        }
    }
    
    printf("**************************\n");
    printf("Poker card dealing system\n");
    printf("**************************\n");

    while (1) {
        shuffle(deck); // Shuffle function from above
        int deal=0;
        bool parsed_correct=true; // Set the intial parsed_correct's boolean value as true

        do {
            printf("Enter a number between 1-13 for the cards to be dealt: ");
            char ch[1024];
            fgets(ch, 1024, stdin); // fgets means file gets which is a fcn from <stdio.h>, which reads a certain size of ch string form the user, from the standard input stream stdin
    
            parsed_correct = parse_int(ch, &deal); // Call out the parsing fuction, which inputs the ch string and outputs a valid deal number, the use of & is to modify the value of the deal variable directly
    
            if (!parsed_correct) {
                printf("Invalid input. Please enter a number.\n"); // Request the user to enter again if the value of parsed_correct is changed to false
            }
            
            else if (deal<1 || deal>13) {
                printf("You didn't enter a number between 1-13, try again.\n");
                parsed_correct = false; // If the number is less than 1 or more than 13, change the parsed_correct to false
            }
        } while (!parsed_correct); // Request the user to input again if parsed_correct is false

        card hand[deal]; // Declare a deck of cards called "hand"
        dealCards(deck, deal, hand); // Call out the fcn, there are "deal" number of cards in hand after dealing
        printf("**********************\n");
        printf("Cards have been dealt.\n");
        printf("**********************\n");
        
        while (1) {
            // 1st Y/N
            printf("Do you want to have another round of dealing? (Y/N)\n");
            char choice; // Declare a char variable to store y or n
            scanf("%c", &choice);
            while (getchar() != '\n'); // Discard any remaining characters in the input buffer until \n is encountered, so unnecessary printf won't be run if while is repeated

            if (toupper(choice) == 'Y') { // toupper is a fcn from <ctype.h>, it converts lowercase letters to uppercase
                printf("*********************\n");
                printf("New round of dealing.\n");
                printf("*********************\n"); // If the user enters 'Y' or 'y', deal once more
                break;
            }

            if (toupper(choice) == 'N') { // If the user enters 'N' or 'n', continue to listing phase
                // 2nd Y/N
                while (1) {
                    printf("Do you wish to list out all the sequences of the cards dealt? (Y/N)\n");
                    char a;
                    scanf("%c", &a);
                    while (getchar() != '\n');

                    if (toupper(a) == 'Y') {
                        if (deal>6) { // For the case that cards dealt are larger than 6
                            // 3rd Y/N
                            while (1) {
                                printf("The number of cards dealt is larger than 6, there are a lot of sequences, do you still wish to list out the cards? (Y/N)\n");
                                char b;
                                scanf("%c", &b);
                                while (getchar() != '\n');

                                if (toupper(b) == 'Y') {
                                    printf("*********************\n");
                                    printf("All possible sequences of the cards dealt: \n");
                                    permute(hand, 0, deal-1); // Print out all possible sequences
                                    printf("*********************\n");
                                    printf("Thanks for playing!\n"); // Ends the game after showing the cards
                                    system("pause");
                                    return 0;
                                }
                                if (toupper(b) == 'N') {
                                    printf("Thanks for playing!\n"); // Ends the game directly after the user confirms not to show cards
                                    system("pause");
                                    return 0;
                                }
                                else {
                                    printf("Invalid input, please enter Y or N.\n"); // Repeat the while loop for invalid input
                                }
                            }
                            // end of 3rd Y/N
                        }
                        
                        if (deal<=6){ // For the case that cards dealt are smaller than or equal to 6
                            printf("*********************\n");
                            printf("All possible sequences of the cards dealt: \n");
                            permute(hand, 0, deal-1); // Print out all possible sequences
                            printf("*********************\n");
                            printf("Thanks for playing!\n"); // Ends the game after showing the cards
                            system("pause");
                            return 0;
                        }
                    }

                    if (toupper(a) == 'N') {
                        printf("Thanks for playing!\n"); // Ends the game if the user decided not to show, whether the number of cards are larger than 6 or not
                        system("pause");
                        return 0;
                    }
                        
                    else {
                        printf("Invalid input, please enter Y or N.\n");    
                    }
                }
                // end of 2nd Y/N
            }
            
            else {
                printf("Invalid input, please enter Y or N.\n");
            }
            // end of 1st Y/N
        }
    }
}
