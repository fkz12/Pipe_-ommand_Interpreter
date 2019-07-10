#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main( ) {
	
	char p0[20], p1[20],  p2[20], p3[20], p4[20], p5[20];
	scanf("%s %s %s %s %s %s", p0, p1, p2, p3, p4, p5);
	printf("\n");
	
	pid_t pid;
	int fd[2];
	
	pipe(fd);		//unnamed pipe, 0 is ReadEndInput //  1 is WriteEndOutputi
	pid=fork();

	if (0!=pid) { 	        //parent
		dup2(fd[1], 1);	
		sleep(1);	//fflush
		execl(p0, p1, p2, NULL);
	}
	else { 		        //child_1
		pid=fork();
		
		if (0!=pid) {
			dup2(fd[0], 0);
			sleep(1);//fflush
			execl(p3, p4, p5, NULL);
		}
		else { 	        //child_1_2
			close(fd[0]);
			close(fd[1]);
			wait(NULL);
		}
	}
	return 0;
}
