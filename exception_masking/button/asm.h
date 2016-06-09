#ifndef __ASM_H_
#define __ASM_H_

#include <stdint.h>

void __set_PRIMASK(unsigned int x);
uint32_t __get_PRIMASK(void);
void __set_FAULTMASK(unsigned int x);
uint32_t __get_FAULTMASK(void);
void __set_BASEPRI(unsigned int x);
uint32_t __get_BASEPRI(void);
uint32_t __get_MSP(void);
void __set_MSP(uint32_t x);
uint32_t __get_PSP(void);
void __set_PSP(uint32_t x);

#endif
