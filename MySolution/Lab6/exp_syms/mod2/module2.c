#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/kmod.h>

int my_exported_fun(void);

static int __init my_init(void) {
    pr_info("module 2 init ...");
    request_module("module1");
    my_exported_fun();
    pr_info("module 2 init complete \n");
    return 0;
}

static void __exit my_exit(void) {
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");