#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>

#define __NR_my_sys_call 436
#define my_sys_call(a) syscall(__NR_my_sys_call,a)

int main(int argc, char* argv[]) {
    unsigned long p1 = 1;
    long rc;
    printf("call my_sys_call with %ld\n", p1);
    rc = my_sys_call(p1);
    printf("\nReturned from syscall rc = %ld\n", rc);
    exit(EXIT_SUCCESS);
}