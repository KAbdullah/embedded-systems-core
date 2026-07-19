#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"

static struct node *head = NULL;
static struct node *tail = NULL;
static int totalTasks = 0;

void add(char *name, int priority, int burst) {
  //If you allocate for sizeof(Task *) instead of Task, you are allocating 8 bytes instead of 20,
  //and Task is of size 20 bytes
  Task *newTask = (Task *) malloc(sizeof(Task));

  newTask->name = name;
  newTask->tid = 101;
  newTask->priority = priority;
  newTask->burst = burst;

  totalTasks += 1;
  insert(&head, &tail, newTask);
}

void schedule() {
  struct node *temp = head;
  struct node *start = NULL;
  Task *tempTask = NULL;
  int samePriority = 0;
  int highestPriority = 0;
  int burstTime = 0;
  Task *samePriorityTasks[];

  while(head) {

    while (temp) {
      if (temp->task->priority > highestPriority) {
        start = temp;
        samePriority = 0;
        highestPriority = temp->task->priority;
      } else if (temp->task->priority == highestPriority) {
        samePriority ++;
      }
      temp = temp->next;
    }

    while (start && samePriority) {
      if (samePriority == 1) {
        run(start->task, start->task->burst);
        delete(&head, start->task);
        samePriority--;
      } else if (samePriority > 1) {
        
      }
    }


  }
}