#include "list.h"
#include "cpu.h"
#include "task.h"
#include "schedulers.h"
//These libraries get added to the /usr/local/include or /user/indclude
//When we do apt install build-essential, that's when they get added there
#include <stdio.h>
#include <stdlib.h>

struct node *head = NULL;
struct node *tail = NULL;

void add(char *name, int priority, int burst) {
  Task *allocatedTask = (Task *) malloc(sizeof(Task));

  allocatedTask->name = name;
  allocatedTask->tid = 101;
  allocatedTask->priority = priority;
  allocatedTask->burst = burst;

  insert(&head, &tail, allocatedTask);
}

void schedule() {
  //You can't allocate a pointer to NULL and then try to dereference it.
  // Task *lowestBurstTask = NULL;

  while (head) {
    //If we come back to the top of the list, then we should set lowestBurst to the first birst that can be found
    struct node *temp = head;
    int lowestBurst = temp->task->burst;
    Task *lowestBurstTask = head->task;

    //I want to make sure I go through the whole list each time, therefore the condition while(temp),
    //because if I do it as temp->next->task->burst < lowestBurst, if a task is has a greater burst speed, but the
    // next one after that has the lowest burst speed encountered, that condition will just skip it no matter what.
    while (temp) {
      if (temp->task->burst < lowestBurst) {
        lowestBurst = temp->task->burst;
        lowestBurstTask = temp->task;
      }
      temp = temp->next;
    }

    run(lowestBurstTask, lowestBurstTask->burst);
    delete(&head, lowestBurstTask);
  }
}

