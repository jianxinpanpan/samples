#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

void create_slub_error(void)
{
  int i;
  buf = kmalloc(32, GFP_KERNEL);
  for(i = 0; i < 32; i++) 
    printk("%x ", *(buf+i));
  printk("\n");
  if(buf) {
    kfree(buf);
    printk("al: Access after free\n");
    memset(buf, 0x55, 32);
    for(i = 0; i < 32; i++) 
      printk("%x ", *(buf+i));
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

