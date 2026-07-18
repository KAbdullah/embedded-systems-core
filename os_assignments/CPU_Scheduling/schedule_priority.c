#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"


struct node *head = NULL;
struct node *tail = NULL;

void add(char *name, int priority, int burst) {
  Task *newTask = (Task *) malloc(sizeof(Task));

  newTask->name = name;
  newTask->tid = 101;
  newTask->priority = priority;
  newTask->burst = burst;

  //Note, we pass the address (pass by reference), because if we pass by value, even for pointers,
  //we create copies of the actual pointer, so if we pass head to the function instead of &head, the next function is just 
  //going to mkae a local copy of head, and if we change what address that copied head address points to, our original head won't move
  //or point to that new address.
  insert(&head, &tail, newTask);
}


void schedule() {
  double avgWait = 0;
  double avgTurn = 0;
  double avgRsp = 0;
  int TotalElapsedTime = 0;
  int totalTasks = 0;

  while (head) {
    int highestPrio = -1;
    struct node *temp = head;
    Task *highestTask = NULL;

    //This is the selection process, so technically we don't include the timing functionality here
    while (temp) {
      if (temp->task->priority > highestPrio) {
        highestPrio = temp->task->priority;
        highestTask = temp->task;
      }
      temp = temp->next;
    }


    avgWait += TotalElapsedTime;
    avgRsp += TotalElapsedTime;
    TotalElapsedTime += highestTask->burst;
    avgTurn += TotalElapsedTime;

    totalTasks++;

    run(highestTask, highestTask->burst);
    //can't do temp->task as the second arguement in delete, because
    //temp is now null and that's why we exited the loop
    delete(&head, highestTask);
    
  }

  printf("\nAverage waiting time %.2lf\n", avgWait / totalTasks);
  printf("Average turnaround time %.2lf\n", avgTurn / totalTasks);
  printf("Average response time %.2lf\n", avgRsp / totalTasks);
}