#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>

int main(void){
	pid_t pids[3];
	int i, character_count = 0, word_count = 0, line_count = 0, n = 3;
    char c;
	FILE *file;
	
	for(i=0; i<n; i++){
		pids[i] = fork();
		
		if (pids[i] < 0) {
	    	printf("Error creating child process \n");
	    	exit(-1);
	    		
		}
		else if (pids[i] == 0) { 
		    if (i == 0) {
		    
		        //first child process to count the characters
	    		file = fopen("input.txt", "r");
				if (file == NULL) {
					printf("Error opening file \n");
					exit(-1);
				}

				while ((c = fgetc(file)) != EOF) {
					if (c != '\n') { 
						character_count++;
					}
				}
				fclose(file);

				printf("Number of characters: %d\n", character_count);
				exit(0);
			
		    } 
		    
		    else if (i == 1) {
		    
		        //second child process to count the words
	    		file = fopen("input.txt", "r");
				if (file == NULL) {
					printf("Error opening file \n");
					exit(-1);
				}

				int flag = 0;
				while ((c = fgetc(file)) != EOF) {
					if (c == ' ' || c == '\t' || c == '\n') {
						flag = 0;
					} 
					else if (flag == 0) {
						flag = 1;
						word_count++;
					}
				}
				fclose(file);

				printf("Number of words: %d\n", word_count);
				exit(0);
			
		    } 
		    else if (i == 2) {
		    
		        //third child process to count the lines
	    		file = fopen("input.txt", "r");
				if (file == NULL) {
					printf("Error opening file \n");
					exit(-1);
				}

				while ((c = fgetc(file)) != EOF) {
					if (c == '\n') {
						line_count++;
					}
				}
				fclose(file);

				printf("Number of lines: %d\n", line_count);
				exit(0);
			
		    }
		}
    } 
    
    for(i=0; i<n; i++){
	 	//parent process waits child processes
		waitpid(pids[i], NULL, 0);
    }
	
	return 0;
}
