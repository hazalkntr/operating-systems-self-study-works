#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	//num of child processes is 3 and 1 parent process = 4 pipes needed 
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];
	
	pid_t pid[3];
	
	char str[] = "Operating Systems";
	
	if (pipe(fd1) == -1 || pipe(fd2)== -1 ||pipe(fd3) == -1 ||pipe(fd4) == -1){
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	
	for (int i = 0; i < 3; i++) {
		pid[i] = fork();
		if (pid[i] < 0) {
			fprintf(stderr, "fork Failed");
			return 1;
		}

		// Parent process
		else if (pid[i] > 0) {
			char received[100];
		
			close(fd1[0]);
			write(fd1[1], str, strlen(str) + 1);
			close(fd1[1]);
			
			wait(NULL);
			wait(NULL);
			wait(NULL);
			
			if(i==2){
			
				close(fd4[1]);
				read(fd4[0], received, 100);
				close(fd4[0]);
				
				
				printf("Original string %s\n", str);
				printf("Received string %s\n", received);
				
			}
			
		}
		
		// child process 1
		else if(pid[i] == 0 && i==0){
			char received[100];
			//char add[7] = "Hello ";
		
		 	close(fd1[1]);
			read(fd1[0], received, 100);
			close(fd1[0]);
			printf("in child %d, Received string: %s\n",i,received);
			
			received[10] = 'Z';
			//strcat(received, add);
			printf("in child %d, Modified string: %s\n",i,received);
			
			close(fd2[0]);
			write(fd2[1], received, strlen(received) + 1);
			close(fd2[1]);
			
			exit(1);
		}
		// child process 2
		else if(pid[i] == 0 && i==1){
			char received[100];
			
		 	close(fd2[1]);
			read(fd2[0], received, 100);
			close(fd2[0]);
			printf("in child %d, Received string: %s\n",i,received);
			
			received[0] = 'A';
			printf("in child %d, Modified string: %s\n",i,received);
			
			close(fd3[0]);
			write(fd3[1], received, strlen(received) + 1);
			close(fd3[1]);
			
			exit(1);
		}
		// child process 3
		else if(pid[i] == 0 && i==2){
			char received[100];
		
		 	close(fd3[1]);
			read(fd3[0], received, 100);
			close(fd3[0]);
			printf("in child %d, Received string: %s\n",i,received);
			
			received[16] = '!';
			printf("in child %d, Modified string: %s\n",i,received);
			
			close(fd4[0]);
			write(fd4[1], received, strlen(received) + 1);
			close(fd4[1]);
			
			exit(1);
		}
	}
		
	return 0;
}
