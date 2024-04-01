#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define N 5

int main()
{
	srand(time(NULL));
	int fd1[2];
	int fd2[2];
	
	pid_t pid[3];
	
	if (pipe(fd1) == -1 || pipe(fd2)== -1){
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	
	for (int i = 0; i < 3; i++) {
		pid[i] = fork();
		if (pid[i] < 0) {
			fprintf(stderr, "fork Failed");
			return 1;
		}

		// child process: process A
		else if(pid[i] == 0 && i==0){
			close(fd1[0]); 
			int nums[N];
				
			printf("\nin process: A, pid num: %d, generating numbers.\n",getpid());
				
			for(int j=0; j<N; j++){
				nums[j] = rand()%90 +10;
				printf("%d ",nums[j]);
			}
				
			write(fd1[1], nums, N*sizeof(int));
			close(fd1[1]);
				
			exit(0);
		}
		
		// child process: process B
		else if(pid[i] == 0 && i==1){
			close(fd1[1]);
			close(fd2[0]); 
			int nums[N];
			
			printf("\nin process: B, pid num: %d, calculating squares.\n",getpid());
			
			read(fd1[0], &nums, N*sizeof(int));
			
			for(int j=0; j<N; j++){
				nums[j] = nums[j] * nums[j];
				printf("%d ",nums[j]);
			}
			
			close(fd1[0]);
			write(fd2[1], nums, N*sizeof(int));
			close(fd2[1]);
			
			exit(0);
		}
		
		// child process: process C
		else if(pid[i] == 0 && i==2){
			close(fd2[1]);
			int nums[N], sum=0;
			read(fd2[0], &nums, N*sizeof(int));
			
			printf("\nin process: C, pid num: %d, calculating sum.\n",getpid());
			
			for(int j=0; j<N; j++){
				sum += nums[j];
			}
			
			printf("The sum of the squares is: %d\n", sum);
    
    			close(fd2[0]);
    			exit(0);
		}
	}
	
	// parent process
	//printf("\nin parent process, pid num: %d, waiting child processes.\n",getpid());
			
	int status;
	for(int j=0; j<3; j++){
		waitpid(pid[j], &status, 0);
	}

	return 0;
}
