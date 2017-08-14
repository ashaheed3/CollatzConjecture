#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void collatzConject(int x){
	int n = x;
	printf("%d, ", n);

	while (n != 1){
		
		if((n % 2) == 0){
			n = (n/2);
		}else if ((n % 2) == 1){
			n = (3 * n + 1);
		}

		printf("%d, ", n);
	}
}	

int main( int argc, char *argv[] ){
	
	int x = atoi(argv[1]);
	
	/*Checks if command line argument if a positive number*/
	while(x < 1){
		printf("Please enter a number greater than 0 \n");
		scanf("%d", &x);
	}

	
	pid_t pid, pid1;

	/*Fork a child process*/
	pid = fork();

	if (pid < 0){ /*Error occurred*/
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { /*Child process*/
		pid1 = getpid();
		printf("child: pid = %d\n", pid); /*A*/
		printf("child: pid1 = %d\n", pid1); /*B*/
		collatzConject(x);
		printf("\n");
	}
	else { /*parent process */
		pid1 = getpid();
		printf("parent: pid = %d\n", pid); /*C*/
		printf("parent: pid1 = %d\n", pid1); /*D*/
		wait(NULL);
	}
	return 0;
}

	
