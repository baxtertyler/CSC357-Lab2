#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX 100

void printOptions();
void pushString();
void getItem();
void deleteItem();
void reverseList();
void printList();
void endProgram();
void invalidInput();

/* struct for my linkedList */
struct linkedList
{
    struct linkedList* next;
    struct linkedList* prev;
    char* data;
};

/* global structs for head, and two temp structs to maniipulate/traverse list */
struct linkedList* head = NULL;
struct linkedList* temp = NULL;
struct linkedList* temp2 = NULL;

int main() {
    char c;
    head = malloc(sizeof(struct linkedList));
    temp2 = malloc(sizeof(struct linkedList));
    head->data = (char*)-1;

    printf("%s\n%s\n%s\n%s\n%s\n%s\n\n", 
      "1 push string", 
      "2 get item",
      "3 delete item",
      "4 reverse list",
      "5 print list",
      "6 end program");
    c = 0;
    while (0<1) {
        scanf("%s", &c);
        if (c == '1') pushString();
        else if (c == '2') getItem();
        else if (c == '3') deleteItem();
        else if (c == '4') reverseList();
        else if (c == '5') printList();
        else if (c == '6') endProgram(); 
        else invalidInput();

        printOptions();
    }
    return 0;
}

void printOptions() {
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n\n", 
    "1 push string", 
    "2 get item",
    "3 delete item",
    "4 reverse list",
    "5 print list",
    "6 end program");
}

void pushString() {
    char* input;

    /* create space for a new struct */
    temp = malloc(sizeof(struct linkedList));
    if (temp == NULL) {
        perror("Memory allocation was unsuccessful");
        exit(EXIT_FAILURE);
    }
    input = malloc(INPUT_MAX * sizeof(char));
    printf("%s\n", "insert text");

    /* get data for struct */
    fgetc(stdin);
    fgets(input, INPUT_MAX, stdin);
    temp->data = input;
    temp->next = NULL;

    /* if head.data is NULL, then there are no elements currently in the linked list. 
     * thus, only change is that head now has the input data */
    if (head == NULL || head->data == (char*)-1) {
        head->next = NULL;
        head->prev = NULL;
        head->data = input;
    }
    else {
        temp2 = head;
        while (temp2->next != NULL) {
            temp2 = temp2->next;
        }
        temp2->next = temp;
        temp->prev = temp2;
    }
    printf("%s\n", "done");
    return;
}

void getItem() {
    int idx;
    /* case for nonexistent and for wrong spot */
    temp = head;
    printf("%s\n", "get item #");
    scanf("%d", &idx);

    if (temp->data == (char*)-1) {
        printf("%s\n", "no such element");
        return;
    }
    if (temp->next == NULL && idx == 0) {
        printf("%s", temp->data);
        return;
    }

    /* loop through until correct index is reached and print the value at the end */
    while (idx > 0) {
        if (temp->next == NULL) {
            printf("%s\n", "no such element");
            return;
        }
        temp = temp->next;
        idx--;
    }
    printf("%s", temp->data);
}

void deleteItem() {
    int idx;
    /* case for when there is 0, 1, 2 items in list */
    temp = head;
    printf("%s\n", "get item #");
    scanf("%d", &idx);
    if (idx == 0) {
        if (head == NULL) {
            printf("%s\n", "no such element");
            return;
        }
        if (head->next == NULL) {
            head = NULL;
            printf("%s\n", "done");
            return;
        }
        temp = head->next;
        temp->prev = NULL;
        head = temp;
    }
    else {
        while (idx > 0) {
            temp = temp->next;
            if (temp == NULL) {
                printf("%s\n", "no such element");
                return;
            }
            idx--;
        }
        temp2=temp->next;
        temp->prev->next = temp->next;
        temp2->prev = temp->prev;
    }
    printf("%s\n", "done");
    
}

void reverseList() {
    /* flip head and head.next so we can stop looping when temp = head */
    temp = head;
    if (temp == NULL || temp->data == (char*)-1) return;
    temp2 = NULL;
    temp2 = temp->prev;
    temp->prev = temp->next;
    temp->next = temp2;
    temp = temp->prev;
    /* loop through list and switch prev with next */
    while (temp != NULL) {
        temp2 = temp->prev;
        temp->prev = temp->next;
        temp->next = temp2;
        temp = temp->prev;
    }
    head = temp2->prev;
    printf("%s\n", "done");
}

void printList() {
    /* prints head, then loops from head.next to end, printing each value */
    if (head == NULL || head->data == (char*)-1) {
        invalidInput();
    }
    else {
        temp = head;
        while(temp->next != NULL) {
            printf("%s", temp->data);
            temp = temp->next;
        }
        printf("%s", temp->data);
    }
}

void endProgram() {
    if(head == NULL) {
        exit(1);
    }
    else if (head->data == (char*)-1) {
        free(head);
        free(temp2);
    }
    else {
        while (temp != NULL) {
            temp2 = temp->next;
            free(temp);
            temp = temp2;
            free(temp2);
        }
    }
    exit(1);
}

void invalidInput() {
    printf("%s\n", "Invalid input");
    return;
}