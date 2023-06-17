TARGET = final
OC = arm-none-eabi-objcopy
CC = arm-none-eabi-gcc
OS = arm-none-eabi-size
AS = arm-none-eabi-as

MACH=cortex-m3
LDSCRIPT=ld/stm32.ld
CFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(LDSCRIPT) -Wl,-Map=$(TARGET).map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32.ld -Wl,-Map=$(TARGET).map



C_SRC  = ./src/main.c
C_SRC += ./src/startup.c
#C_SRC += ./src/led.c
C_SRC += ./src/uart.c
C_SRC += ./src/syscalls.c
C_SRC += ./src/debug.c

INC_PATH := h
CFLAGS += $(addprefix -I, $(INC_PATH))
OBJDIR = ./src

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
        
