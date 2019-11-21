#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>

static void find_tainted_module(void) {
    int j = 0;
    struct module *m;
    struct list_head *module_head;
    struct module *this_module = THIS_MODULE;
    module_head = &this_module->list;
    module_head = module_head->prev;

    list_for_each_entry(m, module_head, list) {
        pr_info("%3d MOD:%20s, tainted = %lu\n", j++, m->name, m->taints);
    }
}

static int __init my_init(void) {
    pr_info("Load taint_finder module\n");
    find_tainted_module();
    return 0;
}

static void __exit my_exit(void) {
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

