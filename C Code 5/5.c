#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct node {
    int data; // Integer value stored in the node
    struct node *next; // Pointer to the next node
};
typedef struct node NODE; // Define struct node as NODE

NODE *createList(int *arr, int len) {
    int i;
    NODE *first, *current, *prev; // Set pointers
    for (i = 0; i < len; i++) {
        current = (NODE*)malloc(sizeof(NODE)); // Allocate memory the size of itself for a new node
        current->data = arr[i];

        if (i == 0) {
            first = current; // If it's the first element in the array, set it as the first node of the list
        }
        else {
            prev->next = current; // Else, connect the previous node to the current node
        }

        current->next = NULL; // Set the next pointer to NULL
        prev = current; // Update previous node to current node
    }
    return first; // Return the first node of the created list
}

void printList(NODE* first) {
    NODE* node = first;

    if (first == NULL) { // If the first node is NULL
        printf("List is empty."); 
    }
    else {
        while (node != NULL) {
            printf("%3d", node->data); // Go through the list and print each element
            node = node->next;
        }
    }
    printf("\n");
}

void combineList(NODE* first1, NODE* first2) {
    NODE* current = first1;

    if (current == NULL) {
        first1 = first2; // If first1 is empty, then update it with first2
    }
    else {
        while (current->next != NULL) {
            current = current->next; // Traverse until the last node of first1
        }
        current->next = first2; // Update the next pointer of the last node to the first node of first2
    }
}

void insertFirstNode(NODE** first, int num) { // ** means a pointer to a pointer of the first node, so we can pass the address of the first_1 pointer in main to insertFirstNode function, so that we can access and modify it inside the function
    NODE *newnode;
    newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = num; // Assign data
    newnode->next = *first; // Let the original first node to be after newnode
    *first = newnode; // Update the newnode as the first node
}

int listLength(NODE* first) {
    int list_len = 0;
    NODE* current = first;
    while (current != NULL) {
        list_len++; // Traverse the list and increment list_len
        current = current->next;
    }
    return list_len;
}

void reverseList(NODE** first) {
    NODE* prev = NULL;
    NODE* current = *first;
    NODE* next = NULL;

    while (current != NULL) {
        next = current->next; // 'next' is used to temporary store the pointer to the next node
        current->next = prev; // Set the previous value as the next value by changing the pointer
        prev = current;
        current = next; // These two lines are used in the next loop
    }

    *first = prev; // Update the head pointer to the original last node of the list
}

int main() {
    int arr1[] = {12, 43, 56, 34, 98};
    int arr2[] = {36, 77, 99};
    int arr1_len = sizeof(arr1) / sizeof(arr1[0]); // Get the length of elements in the array
    int arr2_len = sizeof(arr2) / sizeof(arr2[0]);

    // Create linked list 1
    NODE *first_1, *first_2;
    first_1 = createList(arr1, arr1_len);
    printf("List 1:");
    printList(first_1);

    // Create linked list 2
    first_2 = createList(arr2, arr2_len);
    printf("List 2:");
    printList(first_2);

    // Combine the two lists
    printf("\n");
    combineList(first_1, first_2);
    printf("Combined List:");
    printList(first_1);
    printf("\n");

    // Insert new node
    int select, num;
    do {
        printf("Choose one mode: \n");
        printf("(1) Enter a new node (2) Exit : "); // Set a selection here to continuously insert new nodes
        scanf("%d", &select);
        while (getchar() != '\n');
        if (select != 2) {
            printf("Please enter a number to insert as a new node: ");
            scanf("%d", &num);
            while (getchar() != '\n');
            insertFirstNode(&first_1, num); // The & is to pass the address of the first_1 pointer
            printf("Done! The new list is :");
            printList(first_1);
        }
        printf("\n");
    } while (select != 2); // Exit the do while loop if 2 is selected

    // Get the length of the list
    int first_1_len = listLength(first_1);
    printf("Length of list: %d \n", first_1_len);
    printf("\n");

    // Reverse the order of the list
    reverseList(&first_1);
    printf("Reversed List:");
    printList(first_1);

    system("pause");
    return 0;
}
