#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"


static struct node *head = NULL;
static struct node *tail = NULL;

void add(char *name, int priority, int burst) {
  Task *newTask = (Task *) malloc(sizeof(Task *));

  newTask->name = name;
  newTask->tid = 101;
  newTask->priority = priority;
  newTask->burst = burst;

  insert(&head, &tail, newTask);
}

void schedule() {
  
  while (head) {
    struct node *temp = head;
    int burstTime = 0;

    //Run the first task that comes in for q time
    if (temp->task->burst > QUANTUM) {
      burstTime = QUANTUM;
    } else {
      burstTime = temp->task->burst;
    }

    run(temp->task, burstTime);

    //Now create a temporary Task of the original with reduced Burst time only if burst > 0
    if (temp->task->burst - burstTime > 0) {
      Task *tempTask = (Task *) malloc(sizeof(Task *));
      tempTask->name = temp->task->name;
      tempTask->tid = temp->task->tid;
      tempTask->priority = temp->task->priority;
      tempTask->burst = temp->task->burst - burstTime;
      insert(&head, &tail, tempTask);
    }
    

    //Now delete the original
    delete(&head, temp->task);
  }
}