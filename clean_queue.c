#include <stdio.h>
#include <stdlib.h> //rand
#include <unistd.h> //sleep
#include <sys/time.h> //gettimeofday
#include <sys/types.h> //gettid
#include <sys/syscall.h>
#include <syscall.h>
#include <string.h>
#include <linux/kernel.h>
#define gettid() syscall(SYS_gettid)
int clean_wait_queue(int x) {
    return syscall(352, x);
}


void main(){
	int random_num1, random_num2;
	int ttid, count;
	char str[300];
	
	char str1[300];
	char str2[300];
	char str3[300];
	
	char file[25]="file_";
	char pid[20];
	
	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);
	ttid=gettid();
	count=0;
	
	FILE *fp;
	sprintf(pid,"%d",ttid);
	
	strcat(file, pid);
	fp = fopen( file , "w" );
	
	while(1){
		gettimeofday(&t2, NULL);
		if((t2.tv_sec-t1.tv_sec)>300){
			break;
		}
		//給予不同的seed
		srand(getpid()+time(NULL));
		random_num1= (rand()%3)+1;
		random_num2= (rand()%60)+1;
		sleep(random_num2);
		
		sprintf(str,"Wake up all processes in wait queue final_queue_%d\n", random_num1);
		printf("Wake up all processes in wait queue final_queue_%d\n", random_num1);
		fwrite(str,1,strlen(str),fp);
		
		clean_wait_queue(random_num1);
		printf("After wake up all processes in wait queue final_queue_%d\n", random_num1); 
	}
	
	sprintf(str1,"Clean wait wait queue final_queue_1\n");
	printf("Clean wait wait queue final_queue_1\n");
	fwrite(str1,1,strlen(str1),fp);
	clean_wait_queue(1);

	sprintf(str2,"Clean wait wait queue final_queue_2\n");	
	printf("Clean wait wait queue final_queue_2\n");
	fwrite(str2,1,strlen(str2),fp);
    clean_wait_queue(2);
	
	sprintf(str3,"Clean wait wait queue final_queue_3\n");
	printf("Clean wait wait queue final_queue_3\n");
	fwrite(str3,1,strlen(str3),fp);
	clean_wait_queue(3);

	fclose(fp);
	printf("process %d completes!\n", ttid);
}
	
	