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

  while(head) {
    struct node *temp = head;
    int highestPriority = 0;
    struct node *queuehead = NULL;
    struct node *queuetail = NULL;

    //This while loop basically selects tasks with next highest Priority
    while (temp) {
      if (temp->task->priority > highestPriority) {
        highestPriority = temp->task->priority;
      }
      temp = temp->next;
    }

    temp = head;
    while (temp) {
      struct node *nextTemp = temp->next;
      if (temp->task->priority == highestPriority) {
        Task *queueheadTask = (Task *) malloc(sizeof(Task));

        queueheadTask->name = temp->task->name;
        queueheadTask->tid = temp->task->tid;
        queueheadTask->priority = temp->task->priority;
        queueheadTask->burst = temp->task->burst;

        insert(&queuehead, &queuetail, queueheadTask);
        delete(&head, temp->task);
      }
      temp = nextTemp;
    }

    while (queuehead) {
      int burstTime = (queuehead->task->burst < QUANTUM) ? queuehead->task->burst : QUANTUM;

      run(queuehead->task, burstTime);

      queuehead->task->burst -= burstTime;

      if (queuehead->task->burst > 0) {
        Task *tempTask = (Task *) malloc(sizeof(Task));
        tempTask->name = queuehead->task->name;
        tempTask->tid = queuehead->task->tid;
        tempTask->priority = queuehead->task->priority;
        tempTask->burst = queuehead->task->burst;
        insert(&queuehead, &queuetail, tempTask);

        delete(&queuehead, queuehead->task);
      } else {

        delete(&queuehead, queuehead->task);

      }

    }

  }
}