obj-m += content.o
content-objs := kernel.o ctable.o csock.o trans_ack.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
