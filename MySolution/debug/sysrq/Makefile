obj-m := mysysrq.o
KDIR := /home/xzhou/Downloads/linux-5.3.11/
PWD := $(shell pwd)

default:
		$(MAKE) -C $(KDIR) M=$(PWD) modules

install:
		$(MAKE) -C $(KDIR) M=$(PWD) modules_install

clean:
		rm -rf *.o *.mod.c *.mod.o  *.ko *.mod
		