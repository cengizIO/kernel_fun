// call user mode helper function

#include <linux/kmod.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#include <linux/errno.h>

static char* argv []= {"cp", "/var/log/syslog", "/tmp/syslog", NULL };

static int __init my_init(void) { 
    if (call_usermodehelper("/bin/cp", argv, NULL, UMH_NO_WAIT)) {
        pr_info("Failed to run the program ls\n");
    }

    return 0;
}

static void __exit my_exit(void) {
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

