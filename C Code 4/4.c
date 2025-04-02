#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Print an array
void print_arr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Selection sort function in descending order
void selection_sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        int max = i; // Initialize an index named max to the current index
        for (j = i + 1; j < n; j++) {
            if (arr[max] < arr[j]) // Compare the current max value with the following elements
                max = j; // If the next element is larger, update the index max
        }
        temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp; // Interchange arr[i] with arr[max]
    }
}

bool parse_int(char *ch, int *n) {
    int i=0;
    // The function can directly access and modify the characters in the ch string without needing to use the indirection operator * below
    while (isspace(ch[i])) i++; // Starts checking the ch, move on if blank space is detected, isspace is a fcn from <ctype.h>
    int length = strlen(ch); // Get the length of ch, strlen is from <string.h>
    if (length == i) return false; // If the entire input are blank spaces, return false
  
    char n_buffer[1024]; // Set a temporary buffer to store each valid input
    int j=0;
    if (ch[i] == '-') {
        n_buffer[j] = '-'; // Add the minus sign from ch to deal_buffer
        j++;
        i++;
        if (!isdigit(ch[i])) return false; // If the char following after the minus is not a digit, then it is an invalid input
    }
  
    while (i<length && !isspace(ch[i])) { // In the range of length and the char in ch is not a blank space
        if (!isdigit(ch[i])) return false; // If other than digits are detected, like letters and punctuation marks, or even the dot from a decimal, return false
        n_buffer[j] = ch[i]; // Store the valid digits in the buffer
        j++;
        i++;
    }
  
    n_buffer[j] = '\0'; // Set a null terminator to make it a proper string
    while (isspace(ch[i])) i++; // Move on for blank spaces
    if (ch[i] != '\0') return false; // While still remains true, if any type of char is detected after blank spaces, return false, ex. "___1___2___"
    *n = atoi(n_buffer); // atoi from <stdlib.h> converts string type to int type, and return the value of deal with a pointer
  
    return true; // Return true to indicate successful parsing
}

int main(void) {
    printf("**********************************\n");
    printf("Selection Sort in descending order\n");
    printf("**********************************\n");
    int arr[100];
    int n = 0;
    bool parsed_correct = true; // Set the intial parsed_correct's boolean value as true

    do {
        printf("Please enter the size of the array which undergoes selection sort (2-100): ");
        char ch[1024];
        fgets(ch, 1024, stdin); // fgets means file gets which is a fcn from <stdio.h>, which reads a certain size of ch string form the user, from the standard input stream stdin

        parsed_correct = parse_int(ch, &n); // Call out the parsing fuction, which inputs the ch string and outputs a valid deal number, the use of & is to modify the value of the n variable directly

        if (!parsed_correct) {
               printf("Invalid input, please enter a number.\n"); // Request the user to enter again if the value of parsed_correct is changed to false
        }
        
        else if (n < 2 || n > 100) {
            printf("You didn't enter a number between 2-100, try again.\n");
            parsed_correct = false; // If the number is less than 2 or more than 100, change the parsed_correct to false
        }
    } while (!parsed_correct); // Request the user to input again if parsed_correct is false

    printf("Please enter the numbers one by one to do selection sort, in which a number is in the range of 0-99: \n"); // Set a range for every number in the array
    int i;
	for (i = 0; i < n; i++) {
        bool parsed_right = true;
        int num = 0;
        
        do {
            printf("Number %d: ", i+1);
            char Ch[1024];
            fgets(Ch, 1024, stdin);
            parsed_right = parse_int(Ch, &num);
            if (!parsed_right) {
               printf("Invalid input, please enter a number.\n");
            }
        
            else if (num < 0 || num > 99) {
                printf("Out of range, please try again.\n");
                parsed_right = false;
            }
        } while (!parsed_right);
        
        arr[i] = num; // Assign the space in the array with a valid num
    }
    
    printf("Origin: ");
    print_arr (arr, n);

    selection_sort(arr, n); // Call out the fcn above
    
    printf("Result: ");
    print_arr (arr, n);
    
    system("pause");
    return 0;
}
