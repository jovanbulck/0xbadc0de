#include <linux/init.h>
#include <linux/module.h>
#include "driver_ioctl.h"
#include <linux/fs.h>
#include <linux/miscdevice.h>

#define DEV "drv-am"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anonymized");
MODULE_DESCRIPTION("Driver to set/clear Alignment Mask (CR0.AM)");
long driver_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
        case DRV_AM_IOCTL_CLEAR_AM:
            printk("%s: clearing CR0.AM\n", DEV);
            asm ("mov    %%cr0, %%rax       \n\t"
                 "and    $~(1 << 18),%%rax   \n\t"
                 "mov    %%rax,%%cr0        \n\t"
                :::"rax");
            break;
        case DRV_AM_IOCTL_SET_AM:
            printk("%s: setting CR0.AM\n", DEV);
            asm ("mov    %%cr0, %%rax       \n\t"
                 "or     $(1 << 18),%%rax   \n\t"
                 "mov    %%rax,%%cr0        \n\t"
                :::"rax");
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static const struct file_operations drv_fops = {
    .owner              = THIS_MODULE,
    .compat_ioctl       = driver_ioctl,
    .unlocked_ioctl     = driver_ioctl,
};

static struct miscdevice drv_dev = {
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = DEV,
    .fops   = &drv_fops,
    .mode   = S_IRUGO | S_IWUGO
};

int init_module(void)
{
    /* Register virtual device */
    if (misc_register(&drv_dev))
    {
        printk("%s: virtual device registration failed..\n", DEV);
        drv_dev.this_device = NULL;
        return -EINVAL;
    }

    printk("%s: listening on /dev/%s\n", DEV, DEV);
    return 0;
}

void cleanup_module(void)
{
    /* Unregister virtual device */
    if (drv_dev.this_device)
        misc_deregister(&drv_dev);

    printk("%s: kernel module unloaded\n", DEV);
}
