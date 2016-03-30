#ifndef __ASM_H_
#define __ASM_H_

#include <stdint.h>

void __set_PRIMASK(unsigned int x);
uint32_t __get_PRIMASK();
void __set_FAULTMASK(unsigned int x);
uint32_t __get_FAULTMASK();
void __set_BASEPRI(unsigned int x);
uint32_t __get_BASEPRI();
uint32_t __get_MSP();
void __set_MSP(uint32_t x);
uint32_t __get_PSP();
void __set_PSP(uint32_t x);

#endif
