#include <stdint.h>

extern int main(void);
void reset_handler(void)
{
    /* jump to C entry point */
    /* in handler mode and priviledge access level */
    main();
}

__attribute((section(".isr_vector")))
uint32_t *isr_vector[] = {
    0,
    (uint32_t *) reset_handler,   /* code entry point */
};
