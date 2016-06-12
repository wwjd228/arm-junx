#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/systick.h>

/* Called when systick fires */
void sys_tick_handler(void)
{
	gpio_set(GPIOD, GPIO12); // LED on
        gpio_clear(GPIOD, GPIO12); // LED off
}

/* Set up a timer to create 1mS ticks. */
static inline void systick_setup(void)
{
	/* clock rate / 1000 to get 1mS interrupt rate */
	systick_set_reload(2000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();

	/* set system tick priority to 0x00 F0 */
	nvic_set_priority(NVIC_SYSTICK_IRQ, 0x00);
	nvic_enable_irq(NVIC_SYSTICK_IRQ);

	/* this done last */
	systick_interrupt_enable();
}

static inline void gpio_setup(void)
{
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);

	/* Set GPIO11-15 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
			GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

static inline void button_setup(void)
{
	/* use NVIC_EXTI0_IRQ to control button */

	/* set priority */
	nvic_set_priority(NVIC_EXTI0_IRQ, 0xF0);

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
	gpio_setup();
	button_setup();
	systick_setup();

	while (1) {
	}

	return 0;
}

void exti0_isr(void)
{
	if (exti_get_flag_status(EXTI0))
		exti_reset_request(EXTI0);

	/* LED (PD13) on the board */
	gpio_set(GPIOD, GPIO13);
	while (1); // do some work
	gpio_clear(GPIOD, GPIO13);
}
