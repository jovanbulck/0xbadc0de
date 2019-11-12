#ifndef SGX_STEP_IOCTL_H_INC
#define SGX_STEP_IOCTL_H_INC

#include <linux/ioctl.h>

#define DRV_AM_IOCTL_MAGIC            'L'
#define DRV_AM_IOCTL_CLEAR_AM         _IO(DRV_AM_IOCTL_MAGIC, 0)
#define DRV_AM_IOCTL_SET_AM           _IO(DRV_AM_IOCTL_MAGIC, 1)

#endif
