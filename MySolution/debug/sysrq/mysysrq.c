#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#include <linux/sysrq.h>

#define MY_SYSRQ_KEY 'a'

static void my_sysrq_handler(int key) {
    pr_info("call my handler function %s", __func__);
    pr_info("key pressed was '%c'\n", key);
}

static struct sysrq_key_op my_sysrq_key_op = {
    .handler = my_sysrq_handler,
	.help_msg = "e(X)ample",
	.action_msg = "eXample action message",
};

static int __init my_init(void) {
    
    int rc = register_sysrq_key(MY_SYSRQ_KEY, &my_sysrq_key_op);
    if (rc == 0) {
        pr_info("sysrq key registered\n");
    } else {
        pr_info("sysrq key failed to register");
    }

    pr_info("Success loaded module %s\n", KBUILD_MODNAME);
    return 0;
}

static void __exit my_exit(void) {
    int rc = unregister_sysrq_key(MY_SYSRQ_KEY, &my_sysrq_key_op);
	if (rc == 0) 
		pr_info("sysrq key unregistered\n");
	else 
		pr_err("sysrq key failed to unregister\n");
    
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

