#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oleksii Shavykin");

static struct kmem_cache *kmem_cache;

// kmem_cache constructor
static void kmem_create(void *obj)
{
	pr_info("Hello from %s!\n", __func__);
}

// Module init
int init_module(void)
{
	void *node;

	// Create our cache
	kmem_cache = kmem_cache_create("my_cache", 19, 0, 0, &kmem_create);
	if (!kmem_cache)
		return -ENOMEM;

	// Try to alloc first node
	node = kmem_cache_alloc(kmem_cache, 0);
	if (!node)
		return -ENOMEM;

	// Free node
	kmem_cache_free(kmem_cache, node);

	return 0;
}

// Module exit
void cleanup_module(void)
{
	// Destroy our cache
	kmem_cache_destroy(kmem_cache);

	pr_info("Good bye!\n");
}

