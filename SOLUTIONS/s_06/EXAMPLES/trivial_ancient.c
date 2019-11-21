/* **************** LFD420:5.3 s_06/trivial_ancient.c **************** */
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

int __init init_module(void)
{
        pr_info("Hello: init_module loaded at 0x%p\n", init_module);
        return 0;
}

void __exit cleanup_module(void)
{
        pr_info("Bye: cleanup_module loaded at 0x%p\n", cleanup_module);
}
