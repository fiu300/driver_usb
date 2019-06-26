
KERN_DIR:=/home/ftp/anonymous/linux-2.6.22/
obj-m += usbmouse_as_key.o 

all:
	make -C $(KERN_DIR) M=`pwd` modules

clean:
	-make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf Module.symvers
