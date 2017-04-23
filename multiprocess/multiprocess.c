#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int count = 1;

void sub_func(void)
{
    while(1) {
        count += 5;
        printf("sub_func: pid=%d, count=%d\n", getpid(), count);
        sleep(1);
    }
}


int main(void) {
    int sub_pid = 0;
    printf("MultiTreadDemo start...\n");
    if ((sub_pid = fork()) == 0) {
        sub_func();
        //exit();
    }
    while(getchar() != 'q') {
        printf("main: pid=%d, count=%d\n", getpid(), count);
    }
    printf("MainProcess going to exit: pid=%d\n", getpid());
    printf("Now wait my child to exit...: pid=%d\n", sub_pid);
    sub_pid = wait(NULL);
    printf("child:%d exited! Over!\n", sub_pid);
}
