#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/module.h>

static struct task_struct *tsk[NR_CPUS];

static void print_cpu(char *s)
{
	preempt_disable();
	pr_info("%s cpu=%d.\n", s, smp_processor_id());
	preempt_enable();
}

int f(void* param) {
    do {
        print_cpu("sleep in thread");
        msleep_interruptible(1000);
        print_cpu("sleep over");
    } while (!kthread_should_stop());
    return 0;
}

static int __init my_init(void) {
    // create kernel threads
    int cpu_id;
    for_each_online_cpu(cpu_id) {
        tsk[cpu_id] = kthread_create(f, NULL, "thr_fun%d", cpu_id);
    
        if (!tsk[cpu_id]) {
            pr_info("Failed to generate a kernel thread\n");
            return -1;
        }
        kthread_bind(tsk[cpu_id], cpu_id);
        wake_up_process(tsk[cpu_id]);
        pr_info("starting thread for cpu %d\n", cpu_id);
        print_cpu("on");
    }

    pr_info("Success loaded module %s\n", KBUILD_MODNAME);
    return 0;
}

static void __exit my_exit(void) {
    int i;
	for_each_online_cpu(i) {
		pr_info(" Kill Thread %d", i);
		kthread_stop(tsk[i]);
		print_cpu("Kill was done on ");
	}
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");
