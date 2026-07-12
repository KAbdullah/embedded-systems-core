/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

#define SIZE    100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    //This is because the first argument is the name of the file itself, so driver.c
    in = fopen(argv[1],"r");

    if (in == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    while (fgets(task,SIZE,in) != NULL) {
        //temp here get's allocated memory via the strdup function, this function copies task into a memory and assigns the pointer the address of where it's located
        temp = strdup(task);
        //strsep is better than strtok because if you have two delimeters like so T1,,20, signifying missing data, strtok will just skip it, but strsep recognizes it as missing data and
        //returns an empty string "". Additionally, and most importantly, if two threads call strtok(), because the function keeps an interal pointer, that pointer can be overwritten by 
        //the 2nd thread. However, strsep(&temp, "delimeter"), takes an external pointer, so you it's thread safe. temp is a pointer so, &temp is a pointer to pointer
        name = strsep(&temp,",");
        //atoi is basicaly string to integer
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    schedule();

    return 0;
}
