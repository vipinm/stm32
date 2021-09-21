OBJCPY=arm-none-eabi-objcopy
CC=arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32.ld -Wl,-Map=final.map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32.ld -Wl,-Map=final.map

all:main.o led.o syscalls.o uart.o startup.o final.elf final.bin
debug:main.o led.o uart.o startup.o final_debug.elf final_debug.bin

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^

uart.o:uart.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o:startup.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf:main.o led.o uart.o startup.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

final_debug.elf:main.o led.o uart.o startup.o
	$(CC) $(LDFLAGS) -o $@ $^

final_debug.bin:final_debug.elf
	$(OBJCPY) -O binary $< $@
clean:
	rm -rf *.o *.elf

load:
	openocd -f board/stm32.cfg
        
