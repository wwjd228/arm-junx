#include <stdint.h>

#define BIT_BAND_REGION_MEM_ADDR_1	*((volatile unsigned long *) (0x20000000))

#define BIT_BAND_ALIAS_BASE_ADDRESS	(0x22000000)

/* bit band alias address to address bit 0, bit 1, bit 2 of the bit band memory address
   BIT_BAND_REGION_MEM_ADDR_1 */
#define BIT_BAND_ALIAS_ADDRESS_1	*((volatile unsigned long *) (BIT_BAND_ALIAS_BASE_ADDRESS+0))
#define BIT_BAND_ALIAS_ADDRESS_2	*((volatile unsigned long *) (BIT_BAND_ALIAS_BASE_ADDRESS+4))
#define BIT_BAND_ALIAS_ADDRESS_3	*((volatile unsigned long *) (BIT_BAND_ALIAS_BASE_ADDRESS+8))

int main(void)
{
    uint32_t val;
    BIT_BAND_REGION_MEM_ADDR_1 = 0xA0;
    BIT_BAND_ALIAS_ADDRESS_1 = 0x1;

    BIT_BAND_ALIAS_ADDRESS_2 = 0x1;
    BIT_BAND_ALIAS_ADDRESS_3 = 0x1;

    val = BIT_BAND_REGION_MEM_ADDR_1;

    while(1);
    return val;
}
