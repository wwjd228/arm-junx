#include <stdint.h>
#include "asm.h"

static inline uint32_t is_priviledged_access() 
{
    uint32_t control = __get_CONTROL();
    // in unpriviledge access level
    if ( (control & 0x1) ) return 0;

    // in unprovoledge access level
    else return 1;
}

void main(void)
{
    uint32_t val;
    if (is_priviledged_access()) {
	val = __get_PRIMASK();
        __set_PRIMASK(1);
        val = __get_PRIMASK();
	__set_PRIMASK(0);
	val = __get_PRIMASK();
    }

    val = __get_CONTROL();
    go_to_unpriviledged_access_level();
    val = __get_CONTROL();
    val = __get_PRIMASK();
    __set_PRIMASK(1);
    val = __get_PRIMASK();
    __set_PRIMASK(0);
    val = __get_PRIMASK();

    go_to_priviledged_access_level();
    val = __get_CONTROL();

    val++;
    while(1);
}
