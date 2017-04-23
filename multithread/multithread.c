#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/syscall.h>  

int count = 1;

long int gettid(void) {
    return (long int)syscall(SYS_gettid);
}

void * thread_func(void * arg) {
    while(1) {
        count += 5;
        printf("thread_func: pid=%d, tid=%ld, count=%d\n", getpid(), gettid(), count);
	//pthread_self() is a POSIX implementation
        //printf("thread_func: pid=%d, tid=%ld, count=%d\n", getpid(), pthread_self(), count);
        sleep(1);
    }
}


int main(void) {
    pthread_t tid;
    printf("MultiTreadDemo start...\n");
    printf("main: pid=%d, tid=%ld, count=%d\n", getpid(), gettid(), count);
    if (pthread_create(&tid, NULL, thread_func, NULL))
        printf("create thread failed!\n");
    printf("main: tid = %d\n", (unsigned int)tid);   
    while (getchar() != 'q') {
        count += 1;
        printf("main: pid=%d, tid=%ld, count=%d\n", getpid(), gettid(), count);
	//pthread_self() is a POSIX implementation
        //printf("main: pid=%d, tid=%ld, count=%d\n", getpid(), pthread_self(), count);
    }
    printf("MultiTreadDemo End: pid=%d\n", getpid());
}
