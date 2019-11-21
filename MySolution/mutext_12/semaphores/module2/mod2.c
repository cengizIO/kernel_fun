#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#include <linux/errno.h>

extern struct semaphore my_sem;

static int __init my_init(void) {
    if (!down_interruptible(&my_sem)) {
        pr_info("Got the sem from %s, count = %d\n", KBUILD_MODNAME, my_sem.count);
        return 0;
    } else {
        pr_info("Failed to get sem from %s\n", KBUILD_MODNAME);
        return -EBUSY;
    }
    return 0;
}

static void __exit my_exit(void) {
    up(&my_sem);
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

