# setup useful variables that can be used by make.

ARM = arm-none-eabi
CC = $(ARM)-gcc
LD  = $(ARM)-ld
AS  = $(ARM)-as
AR = $(ARM)-ar
OD  = $(ARM)-objdump
OCP = $(ARM)-objcopy
LPP = ../libpi
LPI = $(LPP)/libpi.a


# perhaps theres a better way to do this without being so strung out...
INC = -I$(LPP) -I.
INC += -I$(LPP)/includes/libc-includes 
INC += -I$(LPP)/includes/libesp-includes 
INC += -I$(LPP)/includes/libinterrupt-includes
INC += -I$(LPP)/includes/libperipheral-includes
INC += -I$(LPP)/includes/libtools-includes
INC += -I$(LPP)/includes/libstepper-includes
INC += -I$(LPP)/includes/libservo-includes
INC += -I$(LPP)/includes/libimu-includes

CFLAGS = -Og -Wall -nostdlib -nostartfiles -ffreestanding -mcpu=arm1176jzf-s -mtune=arm1176jzf-s  -std=gnu99 $(INC) -ggdb -Wno-pointer-sign

ASFLAGS = --warn --fatal-warnings  -mcpu=arm1176jzf-s -march=armv6zk

CPP_ASFLAGS =  -nostdlib -nostartfiles -ffreestanding   -Wa,--warn -Wa,--fatal-warnings -Wa,-mcpu=arm1176jzf-s -Wa,-march=armv6zk   $(INC)
