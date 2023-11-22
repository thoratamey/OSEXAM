#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
//Note: Zombie process is a process which has terminated but it's entry is there in the system.
//NOTE:To check the pid in linux cmd : "ps -e -o pid,stat"
int main() {
printf("Thorat Amey Arun\n23MCS1004\n");
int pid=fork();
if(pid == 0)
{
printf("child process id : %d has parent id : %d \n", getpid(),
getppid());
}
else if(pid > 0)
{
sleep(60); //Putting parent into sleep so that child get executed.
printf("parent process id: %d has grand parent id : %d \n",
getpid(), getppid());
}
else
{
printf("process not created");
}
return 0;
}
