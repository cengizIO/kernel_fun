#define _GNU_SOURCE
#include <sched.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>

int shared = 0;

int thread_function(void *data) {
    int j;
	printf("starting off slave thread, pid=%d\n", getpid());
	for (j = 0; j < 10; j++) {
		shared = j + 1000;
		sleep(1);
		printf("\nslave thread running: j=%d, shared=%d secs\n", j,
		       shared);
	}
	printf("\nSlave thread saying goodbye\n");
	return 0;
}

int main(int argc, char* argv[]) {
    void* stack;
    int pagesize, stacksize;
    int tid;
    int i;
    pagesize = getpagesize();
    stacksize = pagesize * 4;
    
    if (posix_memalign(&stack, pagesize, stacksize)) {
        perror("failed to allocate thread stack\n");
        exit(EXIT_FAILURE);
    }

    tid = clone(thread_function, (char*) stack + stacksize,
                CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM | CLONE_SIGHAND | CLONE_THREAD,
                0);
    if (tid < 0) {
        perror("failed to create thread");
        exit(EXIT_FAILURE);
    }           

    for (i = 0; i < 10; i ++) {
        shared = i;
        sleep(1);
        printf("\nmaster thread running j = %d, shared = %d \n", i, shared);
    } 
    printf("master exit\n");
    exit(EXIT_SUCCESS);
}