#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
#include "asm.h"

static void gpio_setup(void)
{
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);

	/* Set GPIO12 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

static void button_setup(void)
{
	/* use NVIC_EXTI0_IRQ to control button */

	/* if BASEPRI = 0x80, and making proority NVIC_EXTI0_IRQ = 0x90 will block the interrupt */
	/* if BASEPRI = 0x80, and making proority NVIC_EXTI0_IRQ = 0x00 will allow the interrupt */
	nvic_set_priority(NVIC_EXTI0_IRQ, 0x00);
	/* Enable NVIC */
	nvic_enable_irq(NVIC_EXTI0_IRQ);

	/* Enable GPIOA clock. */
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Set GPIO0 (in GPIO port A) to 'input open-drain'. */
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);

	/* Configure the EXTI subsystem */
	exti_select_source(EXTI0, GPIOA);
	exti_set_trigger(EXTI0, EXTI_TRIGGER_RISING);
	exti_enable_request(EXTI0);
}

int main(void)
{
	button_setup();
	gpio_setup();

#if 0
	__set_PRIMASK(1);
#endif

#if 0
	/* 0x80 is the priority level, any interrupt which is same or lower priority will be blocked */
	__set_BASEPRI(0x80);
#endif

	while (1) {
	}

	return 0;
}

void exti0_isr(void)
{
	if (exti_get_flag_status(EXTI0))
		exti_reset_request(EXTI0);

	/* Blink the LED (PD12) on the board. */
	gpio_toggle(GPIOD, GPIO12);
}
