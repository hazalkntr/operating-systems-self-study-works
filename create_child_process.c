#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void){
	int status;
	pid_t pid = fork();
	
	if (pid < 0) {
        printf("Error creating child process \n");
        exit(-1);
    } 
	else if (pid == 0) {
	    printf("Who are you? \n");
        sleep(3);
    } 
    else if (pid > 0) {
        int child_pid = wait(&status);
        printf("I am the doctor, from Gallifrey. \n");
    } 
	
	return 0;
}
