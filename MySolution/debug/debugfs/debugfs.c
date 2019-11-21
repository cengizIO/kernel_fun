#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>

#include <linux/fs.h>
#include <linux/debugfs.h>

static struct dentry *var32, *parent, *filen;
static u32 val = (u32) 111;
static u32 sub_val = (u32) 222;

#define KS 32
static char kstring[KS];	/* should be less sloppy about overflows :) */

static ssize_t
my_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes;
	nbytes = sprintf(kstring, "%d\n", val);
	pr_info("d_inode = %p\n", parent->d_inode);
	return simple_read_from_buffer(buf, lbuf, ppos, kstring, nbytes);
}

static ssize_t
my_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	int rc;
	int nbytes = lbuf;
	rc = copy_from_user(&kstring, buf, lbuf);
	sscanf(kstring, "%d", &val);
	pr_info("\n WRITING function, nbytes=%d, val=%d\n", nbytes, val);
	return nbytes;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
};

static void add_var_debugfs(void) {
    debugfs_create_u32("simple_var2", S_IRUGO | S_IWUSR, NULL, &val);
    return;
}

// problems?
static void add_stack_var(void) {
	int i = 678;
	debugfs_create_u32("simple_var2", S_IRUGO | S_IWUSR, NULL, &i);
	return;
}

// add a debugfs directory
static void add_dir(void) {
    parent = debugfs_create_dir("mydir2", NULL);
    debugfs_create_file("sub_file", S_IRUGO | S_IWUSR, parent, NULL, &fops);
}

static int __init my_init(void) {
    add_var_debugfs();
    add_dir();
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

