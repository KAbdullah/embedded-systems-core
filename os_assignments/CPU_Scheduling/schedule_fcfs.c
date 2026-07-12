#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

//Any variable living outside of a function lives in tehe Data Segment. This area behaves like malloc 
//in the sense that it lives for the entire duration of the program, not created or destroyed once a
//function starts or ends, but rather when the program terminates. However, unlike malloc, once you define it 
//with a certain memory space (in our case struct node pointer, 8 bytes - pointers are always 8 bytes), 
//it stays that way and can't be grown or shurnk unlike heap memory.
struct node *head = NULL;
struct node *tail = NULL;

void add(char *name, int priority, int burst) { 
  //The reason I need to allocate here also, is because if I just create it on the stack
  //when a new add gets called in driver.c, the name, priority and burst are overwritten, meaning
  //the memory the newNode was referencing got corrupted, therefore we use malloc
  Task *allocatedTask = (Task *) malloc(sizeof(Task));
  allocatedTask->name = name;
  allocatedTask->tid = 101;
  allocatedTask->priority = priority;
  allocatedTask->burst = burst;

  insert(&head, &tail, allocatedTask);
};

void schedule() {
  struct node *temp = head;
  //The total time a task waits around in the ready queue (aka. could be affected by quantum time for other algorithms)
  //Wait time can simply be calculated by seeing what was the Turn around time - the birst time = rest of the time it just waited in the queue
  double avgWait = 0;
  //Total lifespan of a process in the system, from the moment it arrives until it completely finished execution
  double avgTurn = 0;
  //The total time from when the process was first submitted to when the CPU grants its first slice of execution time
  double avgRsp = 0;
  int totalTasks = 0;
  int currentTime = 0;

  while (temp != NULL) {
    Task *tempTask = temp->task;
    run(tempTask, tempTask->burst);

    avgWait += currentTime;
    avgRsp += currentTime;

    currentTime += tempTask->burst;
    avgTurn += currentTime;

    totalTasks++;
    temp = temp->next;
  }

  printf("\nAverage waiting time = %.2lf\n", avgWait / totalTasks);
  printf("Average turnaround time = %.2lf\n", avgTurn / totalTasks);
  printf("Average response time = %.2lf\n", avgRsp / totalTasks);
}