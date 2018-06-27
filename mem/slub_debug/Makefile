BASEINCLUDE	?= ../../../android_49_qemu/
slub-objs	:= slub_test.o
slub2-objs	:= slub_test2.o
slub3-objs	:= slub_test3.o
slub4-objs	:= slub_test4.o

obj-m	:= slub.o slub2.o slub3.o slub4.o

all :
	$(MAKE) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(BASEINCLUDE) SUBDIRS=$(PWD) modules;

clean :
	$(MAKE) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -rf *.ko

