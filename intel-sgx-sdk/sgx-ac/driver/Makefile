obj-m          += driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

unload:
	sudo rmmod driver.ko || true

load: unload all
	sudo insmod driver.ko
	dmesg | tail
