
#include <stdio.h>
#include <wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int i=0;
	int pid=1;
	int  w;
	printf("%s \n", "Roditel");
	printf("%d  %d \n", getpid(), getppid());

if(	fork()==0)
	{
		printf("Potomok 1: %d  %d \n", getpid(), getppid());
		i++;
	}

	if(fork()==0)
	{
		wait(&w);
		printf("Potomok 2: %d  %d \n", getpid(), getppid());
		i++;
	}
	if(i==1)
		{
			pid =fork();
			if (pid==0)
			{
				wait(&w);
				printf("potomok 3 %d  %d \n", getpid(), getppid());
			}
		}

exit(0);
}
