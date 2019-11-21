/* **************** LFD420:5.3 s_13/my_getcpu.c **************** */
/*
 * The code herein is: Copyright the Linux Foundation, 2019
 *
 * This Copyright is retained for the purpose of protecting free
 * redistribution of source.
 *
 *     URL:    https://training.linuxfoundation.org
 *     email:  training@linuxfoundation.org
 *
 * This code is distributed under Version 2 of the GNU General Public
 * License, which you should have received with the source.
 *
 */
/* my_getcpu program */

/* to avoid a compiler warning */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main()
{
        printf("My cpu is %d\n", sched_getcpu());
        exit(EXIT_SUCCESS);
}
