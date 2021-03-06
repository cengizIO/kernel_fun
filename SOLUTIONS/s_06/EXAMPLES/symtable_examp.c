/* **************** LFD420:5.3 s_06/symtable_examp.c **************** */
/*
 * The code herein is: Copyright the Linux Foundation, 2019
 *
 * This Copyright is retained for the purpose of protecting free
 * redistribution of source.
 *
 *     URL:    https://training.linuxfoundation.org
 *     email:  training@linuxfoundation.org
 *
 * This code is distributed under Version 2 of the GNU General Public
 * License, which you should have received with the source.
 *
 */
#include <linux/module.h>
#include <linux/init.h>

static unsigned long exported_symbol;

static int __init my_init(void)
{
        pr_info("Module loaded\n");
        return 0;
}

static void __exit my_exit(void)
{
        pr_info("Module_unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL v2");
EXPORT_SYMBOL(exported_symbol);
