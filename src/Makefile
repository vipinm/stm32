TARGET = final
OC = arm-none-eabi-objcopy
CC = arm-none-eabi-gcc
OS = arm-none-eabi-size
AS = arm-none-eabi-as

MACH=cortex-m3
LDSCRIPT=stm32.ld
CFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(LDSCRIPT) -Wl,-Map=$(TARGET).map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32.ld -Wl,-Map=$(TARGET).map



C_SRC  = main.c
C_SRC += startup.c
C_SRC += led.c
C_SRC += uart.c
C_SRC += syscalls.c

OBJDIR = ./

OBJS  = $(C_SRC:.c=.o)

.PHONY: all
all: $(TARGET).bin

%.o : %.c
	@echo Compiling $<
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

.PHONY: clean
clean:
#	rm -f $(OBJS)
	rm -f $(TARGET).elf
	rm -f $(TARGET).bin
	rm -f $(TARGET).map

load:
	openocd -f board/stm32.cfg
        
