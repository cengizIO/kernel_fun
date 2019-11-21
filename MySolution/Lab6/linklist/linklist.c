#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <linux/list.h>

LIST_HEAD(my_list);

struct my_node {
    struct list_head node_list;
    int val;
};

void create_linklist(void) {
    // create link list
    struct my_node *me;
    int j;

    for(j = 0; j < 10; j++) {
        me = kmalloc(sizeof(struct my_node), GFP_KERNEL);
        me->val = j;
        list_add(&me->node_list, &my_list);
    }
    pr_info("create_linklist");
}

void delete_linklist(void) {
    // delete link list
    struct list_head *list;
    struct list_head *tmp;

    list_for_each_safe(list, tmp, &my_list) {
        struct my_node *node =
            list_entry(list, struct my_node, node_list);
        pr_info("delete %d \n", node->val);
        // free the nodes
        kfree(node);
    }
}


static int __init my_init(void) {
    create_linklist();
    return 0;
}

static void __exit my_exit(void) {
    delete_linklist();
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

