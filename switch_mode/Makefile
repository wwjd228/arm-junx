CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
CFLAGS = -fno-common -ffreestanding -O0 \
         -gdwarf-2 -g3 -Wall -Werror \
	 -mcpu=cortex-m3 -mthumb \
	 -Wl,-Tswitch_mode.ld -nostartfiles -g \

TARGET = switch_mode.bin
all: $(TARGET)

$(TARGET): switch_mode.c startup.c reg.S switch.S
	$(CC) $(CFLAGS) $^ -o switch_mode.elf
	$(CROSS_COMPILE)objcopy -Obinary switch_mode.elf switch_mode.bin
	$(CROSS_COMPILE)objdump -S switch_mode.elf > switch_mode.list

qemu: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -M stm32-p103 -nographic -kernel switch_mode.bin

debug: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -monitor stdio -M stm32-p103 -nographic \
	-kernel switch_mode.bin -S -gdb tcp::1234

clean:
	rm -f *.o *.elf *.bin *.list



