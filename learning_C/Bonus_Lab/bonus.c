#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[100];
  int employee_id;
  float salary;
  char department[50];
  int years_of_experience;
  float performance_score;
} Employee;

typedef enum {
  ADD = 1, 
  UPDATE,
  DISPLAY,
  SEARCH,
  EXIT
} Options;

Employee * addEmployee();

void updateEmployee(Employee * employee, int numberofempoyees);


int main() {
  int userOption;
  Employee *ptr = (Employee *) malloc(1 * sizeof(Employee));
  int nextEmployeeIndex = 0;
  int currCapacity = 1;

  //Best if you want to run the loop right from the jump and don't have a condition right at the start, but after
  do {
    printf("\n===Employee Performance Management System===\n");
    printf("1. Add Employee\n");
    printf("2. Update Employee\n");
    printf("3. Display All Employees\n");
    printf("4. Search Employee by Name\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &userOption) == 0) {
      printf("Invalid input!\n");
      //exits the most inner loop
      break;
    }

    if (userOption == ADD) {
      if (nextEmployeeIndex >= currCapacity) {
        currCapacity = currCapacity * 2;
        Employee *temp = realloc(ptr, currCapacity * sizeof(Employee));

        if (temp == NULL) {
          printf("We couldn't increase the wise of the Database.");
          //Free the original memory before exiting.
          free(ptr);
          return 1;
        }
        //ptr sill holds the memory address of the old heap memory area, so we change it to reference the new large one
        ptr = temp;
      }

      
      //I want to free the memory area created in addEmployee here, because addEmployee can't free it before or after returning the pointer
      Employee *tempEmployee = addEmployee();
      
      //When you index into a pointer, you also dereference, so it's no longer a pointer,
      //Therefore addEmployee can't return a pointer
      ptr[nextEmployeeIndex] = *tempEmployee;

      //Once it's added to our ptr heap array above, we can free it here.
      free(tempEmployee);

      printf("\n\n %s, %d, %f, %s, %d, %f \n\n", ptr[nextEmployeeIndex].name, ptr[nextEmployeeIndex].employee_id, ptr[nextEmployeeIndex].salary, 
      ptr[nextEmployeeIndex].department, ptr[nextEmployeeIndex].years_of_experience, ptr[nextEmployeeIndex].performance_score);

      nextEmployeeIndex++;
    } else if (userOption == UPDATE) {
        updateEmployee(ptr, currCapacity);

        for (int i = 0; i < currCapacity; i++) {
          Employee tempPtr = ptr[i];
          printf("Employee Name: %s", tempPtr.name);
          printf("Employee Id: %d", tempPtr.employee_id);
          printf("Employee Salary: %f", tempPtr.salary);
          printf("Employee department: %s", tempPtr.department);
        }

    } else if (userOption == EXIT) {
      printf("Exiting...");
    }

  } while (userOption != EXIT);

  free(ptr);
  return 0;
}

Employee * addEmployee() {
  Employee * heap_area = (Employee *) malloc(sizeof(Employee));

  Employee *ptr = heap_area;

  char tempChar[100];
  int tempEmployeeId;
  float tempSalary;
  char tempDepartment[50];
  int yearsOfExperience;
  float performanceScore;

  printf("Enter name of Employee: ");
  scanf("%s", tempChar);
  printf("Enter employee ID: ");
  scanf("%d", &tempEmployeeId);
  printf("Enter salary: ");
  scanf("%f", &tempSalary);
  printf("Enter department: ");
  scanf("%s", tempDepartment);
  printf("Enter years of experience: ");
  scanf("%d", &yearsOfExperience);
  performanceScore = (0.3 * yearsOfExperience + 0.7 * tempSalary / 1000);

  //you can't regularly assign a character array, because it's an address and not longer a value, if it's just one Char, then you can
  //assign via =
  strcpy(ptr->name, tempChar);
  ptr->employee_id = tempEmployeeId;
  ptr->salary = tempSalary;
  strcpy(ptr->department, tempDepartment);
  ptr->years_of_experience = yearsOfExperience;
  ptr->performance_score = performanceScore;

  return ptr;

}

void updateEmployee(Employee * employees, int currCapacity) {
  int enteredID;
  float newSalary;
  char newDepartment[50];

  Employee ptr;
  
  printf("Enter Employee ID to update: ");
  scanf("%d", &enteredID);
  printf("\n");

  printf("Enter new salary: ");
  scanf("%f", &newSalary);
  printf("\n");

  printf("Enter new department: ");
  scanf("%s", newDepartment);
  printf("\n");

  for (int i = 0; i < currCapacity; i++) {
    ptr = employees[i];

    if (ptr.employee_id == enteredID) {
      ptr.salary = newSalary;
      strcmp(ptr.department, newDepartment);
    }
  }  
}