#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#include <linux/errno.h>
#include <linux/percpu.h>

static DEFINE_PER_CPU(int, my_cpuvar) = 101;
static long __percpu *cpualloc;

EXPORT_SYMBOL(my_cpuvar);

static DEFINE_SPINLOCK(dumb_lock);
static int which_cpu(void)
{
	int cpu;
	spin_lock(&dumb_lock);
	cpu = smp_processor_id();
	spin_unlock(&dumb_lock);
	return cpu;
}

static int __init my_init(void) {
    int cpu_id;
    // set my_cpuvar;
    get_cpu_var(my_cpuvar) = 99;
    pr_info("static my_cpuvar = %d\n", get_cpu_var(my_cpuvar));

    // set dynamic variable;
    cpualloc = alloc_percpu(long);
    cpu_id = which_cpu();
    *per_cpu_ptr(cpualloc, cpu_id) = 1000;
    return 0;
}

static void __exit my_exit(void) {
    int cpu_id;
    pr_info("cpuvar = %d", my_cpuvar);
    cpu_id = which_cpu();
    free_percpu(cpualloc);
    pr_info("per_cpu_ptr = %ld\n", *per_cpu_ptr(cpualloc, cpu_id));
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

