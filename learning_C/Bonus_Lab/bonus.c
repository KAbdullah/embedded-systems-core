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

Employee* addEmployee();


int main() {

  printf("Size of this datatype is %zu", sizeof(float));

  int userOption;
  Employee *ptr[100];
  int nextEmployeeIndex = 0;

  //Best if you want to run the loop right from the jump and don't have a condition right at the start, but after
  do {
    printf("Employee Performance Management System\n");
    printf("1. Add Employee\n");
    printf("2. Update Employee\n");
    printf("3. Display All Employees\n");
    printf("4. Search Employee by Name\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");

    scanf("%d", &userOption);

    if (userOption == ADD) {
      ptr[nextEmployeeIndex] = addEmployee();
      nextEmployeeIndex++;
    } else {
      return 1;
    }

    printf("The new added record is: %s, %d, %.2f, %s, %d, %.2f\n\n", ptr[nextEmployeeIndex - 1]->name, ptr[nextEmployeeIndex - 1]->employee_id, 
    ptr[nextEmployeeIndex - 1]->salary, ptr[nextEmployeeIndex - 1]->department, ptr[nextEmployeeIndex - 1]->years_of_experience, 
    ptr[nextEmployeeIndex - 1]->performance_score
    );


  } while (userOption != EXIT);


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
  scanf("%s", &tempChar);
  printf("Enter employee ID: ");
  scanf("%d", &tempEmployeeId);
  printf("Enter salary: ");
  scanf("%f", &tempSalary);
  printf("Enter department: ");
  scanf("%s", &tempDepartment);
  printf("Enter years of experience: ");
  scanf("%d", &yearsOfExperience);
  performanceScore = ((0.3 * yearsOfExperience) + ((0.7 * tempSalary) / 1000));

  //you can't regularly assign a character array, because it's an address and not longer a value, if it's just one Char, then you can
  //assign via =
  strcpy(ptr->name, tempChar);
  ptr->employee_id = tempEmployeeId;
  ptr->salary = tempSalary;
  strcpy(ptr->department, tempDepartment);
  ptr->years_of_experience = yearsOfExperience;
  ptr->performance_score = performanceScore;

}