#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
//Note: to run the program use "./<filename>.out &" so that program will run in the background we can check the process running using ps command.
printf("Thorat Amey Arun\n23MCS1004\n");
pid_t p;
p=fork();
if(p==0)
{
sleep(10); //putting child process to sleep so that parent will be executed
printf("I am child having PID %d\n",getpid());
printf("My parent PID is %d\n",getppid());
}
else
{
sleep(2);
printf("I am parent having PID %d\n",getpid());
printf("My child PID is %d\n",p);
}
}
