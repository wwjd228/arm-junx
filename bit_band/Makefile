CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
CFLAGS = -fno-common -ffreestanding -O0 \
         -gdwarf-2 -g3 -Wall -Werror \
	 -mcpu=cortex-m3 -mthumb \
	 -Wl,-Tbit_band.ld -nostartfiles -g \

TARGET = bit_band.bin
all: $(TARGET)

$(TARGET): bit_band.c startup.c
	$(CC) $(CFLAGS) $^ -o bit_band.elf
	$(CROSS_COMPILE)objcopy -Obinary bit_band.elf bit_band.bin
	$(CROSS_COMPILE)objdump -S bit_band.elf > bit_band.list

qemu: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -M stm32-p103 -nographic -kernel bit_band.bin

debug: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -monitor stdio -M stm32-p103 -nographic \
	-kernel bit_band.bin -S -gdb tcp::1234

clean:
	rm -f *.o *.elf *.bin *.list
