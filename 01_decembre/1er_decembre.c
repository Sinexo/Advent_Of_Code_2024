/******************************************************************************

Creator : Sinexo
Date : 01/12/2024
First day of 2024's Advent of Code

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "ta foiré ton malloc gars\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void sortList(Node** head) {
    if (*head == NULL) return;

    Node* current = *head;
    Node* index = NULL;
    int temp;

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

int distance(Node* list1, Node* list2){
    if (list1 == NULL || list2 == NULL)
        return 0;
    
    Node* current1 = list1;
    Node* current2 = list2;
    
    int acc = 0;
    
    while (current1 != NULL){
        acc+= abs(current1->data - current2->data);
            
        current1 = current1->next;
        current2 =current2->next;
    }
    return acc;
}

int main() {
    FILE *file = fopen("liste.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur.\n");
        return 1;
    }

    Node* leftList = NULL;
    Node* rightList = NULL;

    int leftValue, rightValue;

    while (fscanf(file, "%d %d", &leftValue, &rightValue) == 2) {
        insertEnd(&leftList, leftValue);
        insertEnd(&rightList, rightValue);
    }
    
    fclose(file);

    sortList(&leftList);
    sortList(&rightList);
    int res = distance(leftList, rightList);
    printf("distance = %d",res);
    return 0;
}