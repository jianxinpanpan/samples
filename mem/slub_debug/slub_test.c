#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

void create_slub_error(void)
{
  int i;

  buf = kmalloc(32, GFP_KERNEL);
  if(buf) {
    memset(buf, 0x55, 80);
    for(i = 0; i < 80; i++) 
      printk("%x ", *(buf+i));
    printk("\n");
  }
}

static int __init my_test_init(void)
{
  printk("al: slub error test init\n");
  create_slub_error();
  return 0;
}

static void  __exit my_test_exit(void)
{
  printk("al: slub error test exit\n");
}

MODULE_LICENSE("GPL");
module_init(my_test_init);
module_exit(my_test_exit);

