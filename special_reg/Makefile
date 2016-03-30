CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
CFLAGS = -fno-common -ffreestanding -O0 \
         -gdwarf-2 -g3 -Wall -Werror \
	 -mcpu=cortex-m3 -mthumb \
	 -Wl,-Tspecial_reg.ld -nostartfiles -g \

TARGET = special_reg.bin
all: $(TARGET)

$(TARGET): special_reg.c startup.c reg.S
	$(CC) $(CFLAGS) $^ -o special_reg.elf
	$(CROSS_COMPILE)objcopy -Obinary special_reg.elf special_reg.bin
	$(CROSS_COMPILE)objdump -S special_reg.elf > special_reg.list

qemu: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -M stm32-p103 -nographic -kernel special_reg.bin

debug: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -monitor stdio -M stm32-p103 -nographic \
	-kernel special_reg.bin -S -gdb tcp::1234

clean:
	rm -f *.o *.elf *.bin *.list



