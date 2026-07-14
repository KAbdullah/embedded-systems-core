/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"


// add a new task to the list of tasks
void insert(struct node **head, struct node **tail, Task *newTask) {
    // add the new task to the list 
    struct node *newNode = malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = NULL;
    //Can't do **head, because head points to NULL, and NULL can't store a value aka you can't dereference it
    if (*tail == *head && *head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

// delete the selected task from the list
void delete(struct node **head, Task *task) {
    //Corrected the profs code to ensure that pointers are never initalized hanging. 
    struct node *temp = *head;
    struct node *prev = NULL;

    //If there's no head, meaning no node, then just return, otherwise there will be a seg fault
    if (temp == NULL) {
        return;
    }

    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        if (temp != NULL) {
            prev->next = temp->next;
        }
    }
    //Added free(temp) to ensure no memory leak
    if (temp != NULL) {
        //free the task too, since it was allocated memory and we don't want it floating around if we remove it from the queue 
        free(task);
        free(temp);
    } 
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}
