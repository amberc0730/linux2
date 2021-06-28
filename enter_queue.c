#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep
#include <sys/time.h>
#include <sys/types.h> //gettid
#include <sys/syscall.h>
#include <syscall.h>
#include <string.h>
#include <linux/kernel.h>
#define gettid() syscall(SYS_gettid)

int enter_wait_queue(int x) {
    return syscall(351, x);
}


void main(){
	int	random_num;
	int	ttid, count;
	char file[25]="file_";
	char pid[20];
	char str[300];
	struct timeval  t1, t2;
	
	gettimeofday(&t1, NULL);
	ttid=gettid();
	count=0;
	
	FILE *fp;
	sprintf(pid,"%d",ttid);
	strcat(file, pid);
	fp = fopen( file , "w" );
	
	while(1){
		gettimeofday(&t2, NULL);
		if((t2.tv_sec-t1.tv_sec)>180){
			break;
		}
		
		srand(gettid()+time(NULL));
		random_num= (rand()%3)+1;

		sprintf(str,"process %d is added into wait queue final_queue_%d the %d th time\n", ttid, random_num, count);
		printf("process %d is added into final_queue_%d the %d th time\n", ttid, random_num, count);
		count++;

		fwrite(str,1,strlen(str),file);
		enter_wait_queue(random_num); 
		sleep(5);//wait for a while 

		printf("process %d wake up from wait queue fianl_queue_%d\n", ttid, random_num); 
	}
	fclose(file);
	printf("process %d completes!\n", ttid);
}