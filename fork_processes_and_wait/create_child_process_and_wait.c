#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	pid_t pid = fork();
	
	if (pid < 0) {
    	printf("Error creating child process \n");
    	exit(-1);
    } 
    else if (pid == 0) {
        printf("Who are you? \n");
    } 
    else if (pid > 0) {
		sleep(3);
        printf("I am the doctor, from Gallifrey. \n");
    } 
	
	return 0;
}
