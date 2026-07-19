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
    int samePriority = 0;
    int highestPriority = 0;
    struct node *queuehead = NULL;
    struct node *queuetail = NULL;

    //This while loop basically selects tasks with next highest Priority
    while (temp) {
      if (temp->task->priority > highestPriority) {
        while (samePriority) {
          delete(&queuehead, queuehead->task);
          samePriority--;
        }
        //Don't want the queuetail pointer to stay dangling, so reset it here, for 100% safety
        queuehead = NULL;
        queuetail = NULL;

        samePriority = 1;
        highestPriority = temp->task->priority;
        insert(&queuehead, &queuetail, temp->task);
      } else if (temp->task->priority == highestPriority) {
        samePriority++;
        insert(&queuehead, &queuetail, temp->task);
      }
      temp = temp->next;
    }

    while (queuehead) {
      int burstTime = 0;
      if (queuehead->task->burst < QUANTUM) {
        burstTime = queuehead->task->burst;
      } else {
        burstTime = QUANTUM;
      }

      run(queuehead->task, queuehead->task->burst);

      if (queuehead->task->burst - burstTime > 0) {
        Task *tempTask = malloc(sizeof(Task));
        tempTask->name = queuehead->task->name;
        tempTask->tid = queuehead->task->tid;
        tempTask->priority = queuehead->task->priority;
        tempTask->burst = queuehead->task->burst - burstTime;
        insert(&queuehead, &queuetail, tempTask);
        delete(&queuehead, queuehead->task);
      } else {
        delete(&queuehead, queuehead->task);
      }

    }

  }
}