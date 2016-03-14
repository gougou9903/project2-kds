#include "stdint.h"

#ifndef _MYMEMORY_H
#define _MYMEMORY_H
int8_t mymemmove(uint8_t * src, uint8_t * dst, uint32_t length);
int8_t mymemcpy(uint8_t * src, uint8_t * dst, uint32_t length);
int8_t mymemzero(uint8_t * src, uint32_t length);
int8_t myreverse(uint8_t * src, uint32_t length);
#endif
