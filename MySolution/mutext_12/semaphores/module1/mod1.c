#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>

DEFINE_SEMAPHORE(my_sem);
EXPORT_SYMBOL(my_sem);

static int __init my_init(void) {
    pr_info("Success loaded module %s\n", KBUILD_MODNAME);
    return 0;
}

static void __exit my_exit(void) {
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

