#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int my_exported_fun(void) {
    pr_info("my exported function in module 1");
    return 0;
}

static int __init my_init(void) {
    pr_info("module init \n");
    return 0;
}

static void __exit my_exit(void) {
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");
EXPORT_SYMBOL(my_exported_fun);