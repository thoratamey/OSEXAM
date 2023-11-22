#include <stdio.h>
#include <pthread.h>
// Structure to hold employee information
struct Employee {
char name[50];
double basic;
double incentive;
double salary;
};
// Function executed by the thread
void *calculateSalary(void *arg) {
struct Employee *employee = (struct Employee *)arg;
employee->salary = employee->basic + 0.25 * employee->basic + 0.4 * employee->basic +
employee->incentive;
pthread_exit(NULL);
}
int main() {
pthread_t thread[3];
struct Employee employees[3];
// Input employee information
for (int i = 0; i < 3; i++) {
printf("Enter details for Employee %d:\n", i + 1);
printf("Name: ");
scanf("%s", employees[i].name);
printf("Basic Salary: ");
scanf("%lf", &employees[i].basic);
printf("Incentive: ");
scanf("%lf", &employees[i].incentive);
}
// Create threads to calculate salaries
for (int i = 0; i < 3; i++) {
pthread_create(&thread[i], NULL, calculateSalary, (void *)&employees[i]);
}
// Wait for threads to finish
for (int i = 0; i < 3; i++) {
pthread_join(thread[i], NULL);
}
// Display employee salaries
printf("\nEmployee Salaries:\n");
for (int i = 0; i < 3; i++) {
printf("Name: %s, Salary: %.2lf\n", employees[i].name, employees[i].salary);
}
return 0;
}
