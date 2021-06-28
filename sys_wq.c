#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/sched.h>

//create and initialize three wq head
DECLARE_WAIT_QUEUE_HEAD(final_wait_queue1);
DECLARE_WAIT_QUEUE_HEAD(final_wait_queue2);
DECLARE_WAIT_QUEUE_HEAD(final_wait_queue3);
int con1 = 0;
int con2 = 0;
int con3 = 0;

//enter
asmlinkage int sys_enter_wait_queue(int x) {
		if(x == 1){
			con1 = 0;
			wait_event(final_wait_queue1,con1 == 1);
		}
		else if (x == 2){
			con2 = 0;
			wait_event(final_wait_queue2,con2 == 1);
		}
		else if (x == 3){
			con3 = 0;
			wait_event(final_wait_queue3,con3 == 1);
		}
        return 1;
}

//clean
asmlinkage int sys_clean_wait_queues(int x) {
	if(x == 1){
		con1 = 1;
		wake_up(&final_wait_queue1);
	}
	else if (x == 2){
		con2 = 1;
		wake_up(&final_wait_queue2);
	}
	else if (x == 3){
		con3 = 1;
		wake_up(&final_wait_queue3);
	}
        return 1;
}
