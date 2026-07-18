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
  double avgTurn = 0;
  double avgRsp = 0;
  int totalElapsedTime = 0;
  int howManyruns = 0;
  
  while (head) {
    struct node *temp = head;
    int burstTime = 0;

    //Run the first task that comes in for q time
    if (temp->task->burst > QUANTUM) {
      burstTime = QUANTUM;
    } else {
      burstTime = temp->task->burst;
    }

    totalElapsedTime += burstTime;

    //No equal sign, because we don't want to add the burst of the last task, since response looks at when the task 
    //got executed, not how long it got to execute
    if (howManyruns < totalTasks) {
      avgRsp += totalElapsedTime;
    }

    howManyruns++;
    run(temp->task, burstTime);

    //Now create a temporary Task of the original with reduced Burst time only if burst > 0
    if (temp->task->burst - burstTime > 0) {
      Task *tempTask = (Task *) malloc(sizeof(Task *));
      tempTask->name = temp->task->name;
      tempTask->tid = temp->task->tid;
      tempTask->priority = temp->task->priority;
      tempTask->burst = temp->task->burst - burstTime;
      insert(&head, &tail, tempTask);

      //Now delete the original
      delete(&head, temp->task);      
    
      //else statement just so we can count avgTurn
    } else {

      //We only count Average turn around time when the task is completed
      avgTurn += totalElapsedTime;

      //Now delete the completed task
      delete(&head, temp->task);
      
    }
    
  }

  printf("\nAverage waiting time = %.2lf\n", (avgTurn - totalElapsedTime) / totalTasks);
  printf("Average turnaround time = %.2lf\n", avgTurn / totalTasks);
  printf("Average response time = %.2lf\n", avgRsp / totalTasks);
}