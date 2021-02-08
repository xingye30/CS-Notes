obj-m += hello_module.o

KVERN = $(shell uname -r)
CURDIR = ${shell pwd}

all:
	make -C /lib/modules/${KVERN}/build M=${CURDIR} modules

clean:
	make -C /lib/modules/${KVERN}/build M=${CURDIR} clean