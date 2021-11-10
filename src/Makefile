OBJCPY=arm-none-eabi-objcopy
CC=arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32.ld -Wl,-Map=final.map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32.ld -Wl,-Map=final.map

OBJDIR=/home/vipin/work/stm32/src
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
all:final.elf

$(OBJDIR)/%.o : %.c
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

final.elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.elf *.bin

load:
	openocd -f board/stm32.cfg
        
