#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

#include <linux/slab.h>

struct kmem_cache* my_memcache;
static char* kbuf;

static int __init my_init(void) {
    // allocate slab;
    my_memcache = kmem_cache_create("my_memcache", 16, 0, SLAB_HWCACHE_ALIGN, NULL);
    if (!my_memcache) {
        pr_err("Failed to allocate cache");
        return -ENOMEM;
    }

    // allocate from the cache;
    kbuf = kmem_cache_alloc(my_memcache, GFP_ATOMIC);
    if (!kbuf) {
        pr_err("failed to create cache object");
        (void)kmem_cache_destroy(my_memcache);
        return -1;
    }

    pr_info("cache object create");
    pr_info("Success loaded module %s\n", KBUILD_MODNAME);
    return 0;
}

static void __exit my_exit(void) {
    kmem_cache_free(my_memcache, kbuf);
    kmem_cache_destroy(my_memcache);
    pr_info("module unloaded \n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("xzhou");
MODULE_LICENSE("GPL v2");

