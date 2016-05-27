CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
CFLAGS = -fno-common -ffreestanding -O0 \
         -gdwarf-2 -g3 -Wall -Werror \
	 -mcpu=cortex-m3 -mthumb \
	 -Wl,-Tdo_stack_operations.ld -nostartfiles -g \

TARGET = do_stack_operations.bin
all: $(TARGET)

$(TARGET): do_stack_operations.c startup.c stack_op.S
	$(CC) $(CFLAGS) $^ -o do_stack_operations.elf
	$(CROSS_COMPILE)objcopy -Obinary do_stack_operations.elf do_stack_operations.bin
	$(CROSS_COMPILE)objdump -S do_stack_operations.elf > do_stack_operations.list

qemu: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -M stm32-p103 -nographic -kernel do_stack_operations.bin

debug: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -monitor stdio -M stm32-p103 -nographic \
	-kernel do_stack_operations.bin -S -gdb tcp::1234

clean:
	rm -f *.o *.elf *.bin *.list



