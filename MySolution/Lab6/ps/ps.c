#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

#define for_each_process_thread(p, t) \
        for_each_process(p) for_each_thread(p, t)

static void iterator_all_process(void) {
    struct task_struct *p;
    
    for_each_process(p) {
        pr_info("pid = %d, comm = %s state=%ld\n",
                p->pid, p->comm, p->state);
    }
}

static int __init my_init(void) {
    iterator_all_process();
    return 0;
}

static void __exit my_exit(void) {
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

