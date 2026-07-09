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

int compare(const void *a, const void *b);

void updateEmployee(Employee * employee, int numberofempoyees);

void displayEmployees(Employee *Employees, int numOfEmployees);

Employee * searchEmployeeByName(Employee *employees, int numEmployees);

void sortEmployeesByPerformance(Employee *employees, int numOfEmployees);


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
      //Pass Employee index instead of currCapacity, because currCapacity doesn't have an Employee stored in that position
      //meaning doing stuff like .name, .salary, etc. will cause Segmentation faults
        updateEmployee(ptr, nextEmployeeIndex);

        for (int i = 0; i < currCapacity; i++) {
          Employee tempPtr = ptr[i];
          printf("\n");
          printf("Employee Name: %s\n", tempPtr.name);
          printf("Employee Id: %d\n", tempPtr.employee_id);
          printf("Employee Salary: %.2f\n", tempPtr.salary);
          printf("Employee department: %s\n", tempPtr.department);
          printf("Employee performance score: %.2f\n", tempPtr.performance_score);
        }

    } else if (userOption == DISPLAY) {
        printf("\nEmployee Records (sorted by Performance Score): \n");

        displayEmployees(ptr, nextEmployeeIndex);

    } else if (userOption == SEARCH) {
      Employee searchedEmployees[] = searchEmployeeByName(ptr, nextEmployeeIndex);

      int searchedLen = sizeof(searchedEmployees) / sizeof(Employee);

      printf("Size of the searched array is: %d", searchedLen);

      printf("Searched Results: \n");
      
      

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

  //For all the scanf() here, I don't need to do scanf(" %s") - note the space -, because for the s character there is already a built in
  //loop that tells it to skip all whitespaces which include new-line characters (\n). However, for %c you must put a space since that captures
  //everything. Also, professionals recommend using fgets instead, because it doesn't ignore spaces at all,
  //useful when you have a first name like Mark Hue. Additionally you also then clean the input by, doing this,
  //varToStore[strcspn(varToStore, "\n")] = "\0", this replaces the buffer's \n with a null terminator (\0).

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

void updateEmployee(Employee * employees, int numEmployees) {
  int enteredID;
  float newSalary;
  char newDepartment[50];

  Employee *ptr;
  
  printf("Enter Employee ID to update: ");
  scanf("%d", &enteredID);

  printf("Enter new salary: ");
  scanf("%f", &newSalary);

  printf("Enter new department: ");
  scanf("%s", newDepartment);

  printf("Employee information updated successfully!");
  printf("\n");

  for (int i = 0; i < numEmployees; i++) {
    ptr = &employees[i];

    if (ptr->employee_id == enteredID) {
      ptr->salary = newSalary;
      strcpy(ptr->department, newDepartment);
      ptr->performance_score = (0.3 * ptr->years_of_experience + 0.7 * newSalary / 1000);
    }
  }  
}


void displayEmployees(Employee *employees, int numOfEmployees) {
  sortEmployeesByPerformance(employees, numOfEmployees);

  for (int i = 0; i < numOfEmployees; i++) {
    Employee tempEmployee = employees[i];

    printf("Name: %s\n", tempEmployee.name);
    printf("Employee ID: %d\n", tempEmployee.employee_id);
    printf("Salary: %.2f\n", tempEmployee.salary);
    printf("Department: %s\n", tempEmployee.department);
    printf("Years of Experience: %d\n", tempEmployee.years_of_experience);
    printf("Performance Score: %.2f\n", tempEmployee.performance_score);
    printf("\n");
  }

}

int compare(const void *a, const void *b) {
  const Employee* x = (Employee *) a;
  const Employee* y = (Employee *) b;

  if (x->performance_score > y->performance_score) {
    return -1;
  } else if (x->performance_score < y->performance_score) {
    return 1;
  } else {
    return 0;
  }
}

void sortEmployeesByPerformance(Employee *employees, int numOfEmployees) {
  int (*compar)(const void*, const void*) = compare;
  
  qsort((void *) employees, numOfEmployees, sizeof(Employee), compar);

}

Employee * searchEmployeeByName(Employee *employees, int numEmployees) {

  char name[50];
  int currPtrIndex = 0;

  printf("Enter name to search: ");
  scanf("%s", name);
  
  Employee *ptr;
  
  for (int i = 0; i < numEmployees; i++) {
    if (strstr(employees[i].name, name)) {
      ptr[currPtrIndex] = employees[i];
      currPtrIndex ++;
    }
  }

  return ptr;

}