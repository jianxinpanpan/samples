#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

void create_slub_error(void)
{
  buf = kmalloc(32, GFP_KERNEL);
  if(buf) {
    memset(buf, 0x55, 32);
    kfree(buf);
    printk("al: Object already freed");
    kfree(buf);
  }
}

static int __init my_test_init(void)
{
  printk("al: slub error test init\n");
  create_slub_error();
  return 0;
}

static void __exit my_test_exit(void)
{
  printk("al: slub error test exit\n");
}

MODULE_LICENSE("GPL");
module_init(my_test_init);
module_exit(my_test_exit);
