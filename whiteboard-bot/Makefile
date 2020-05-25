MAKEFLAGS +=  --no-print-directory

NAME := whiteboard_bot
SOURCES := wbb.c wbb_letters.c wbb_circle.c wbb_points.c wbb_accel.c wbb_shell.c wbb_server.c

include includes.mk


CFLAGS += -Wno-unused-function -Wno-unused-variable -DRPI_OS 

OBJS := $(NAME).o $(patsubst %.c, %.o, $(SOURCES)) start.o

DEPS := $(wildcard ./*.h) ./Makefile

all: $(OBJS) $(NAME).bin

%.o: %.c $(DEPS) 
	$(CC) $(CFLAGS) $< -c -o $@  -lm -lutil

$(OBJS): $(DEPS)

%.o: %.S
	$(CC) -c $(CPP_ASFLAGS) $< -o $@

# <LPI> will get rebuilt if anything changes, so we don't need any other
# dependencies.
%.bin: $(OBJS) $(DEPS) 
	$(LD) $(OBJS) -T memmap -o $*.elf $(LPI)
	$(OD) -D   $*.elf > $*.list
	$(OCP) $*.elf -O binary $*.bin

run:
	make
	./my-install ./$(NAME).bin  # use a hacky local version thats hacky but works better in this scenario

clean:
	rm -rf $(BUILD_DIR) $(NAME) $(NAME).o *~ wbb.o wbb_letters.o wbb_circle.o wbb_points.o wbb_accel.o wbb_shell.o wbb_server.o *.bin *.elf *.list *.img Makefile.bak  *.d

.PHONY: all clean run