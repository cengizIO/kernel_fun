/* **************** LFD420:5.3 s_06/lab_ps_thread.c **************** */
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
/*
 * Iterating over process threads
 *
 * As an enhanced variation, write a module that uses the
 * for_each_process_thread?  macro to generate information:
 *
 * #define for_each_process_thread(p, t)			\
 *        for_each_process(p) for_each_thread(p, t)
 *
 *  which is a double loop
 *
 * For each task, printout the thread group ID, process ID,
 *  state, command line and any other interesting
 *  information.

@*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/oom.h>

static int __init my_init(void)
{
	struct task_struct *p, *t;
	pr_info("Mini ps: pid, command, state\n\n");

	for_each_process_thread(p, t) {
		pr_info("tgid=%d, pid=%d, comm=%s, state=%ld\n",
			t->tgid, t->pid, t->comm, t->state);
	}
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein");
MODULE_AUTHOR("Behan Webster");
MODULE_DESCRIPTION("LFD420:5.3 s_06/lab_ps_thread.c");
MODULE_LICENSE("GPL v2");
