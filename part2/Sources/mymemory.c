#include "mymemory.h"
#include "stdint.h"

int8_t mymemmove(uint8_t * src, uint8_t * dst, uint32_t length)
{
	if (src == 0 || dst == 0)
		return 1;
	if (length <= 0)
	 	return 2;
	 uint8_t * ptr = src;
	 uint8_t * ptr1 = dst;
	 ptr += length;
	 while ((ptr != src) && (--ptr != dst));//checking overlap condition
	if (ptr == src)
	{

		while (length-- != 0)
		{
			*ptr1++ = *ptr++;
		}
	}
	else
	{
		ptr = src + length;
		ptr1 += length;
		while (length-- != 0)
		{
			*--ptr1 = *--ptr;
		}
	}
	return 0;
}

int8_t mymemcpy(uint8_t * src, uint8_t * dst, uint32_t length)
{
	if (src == 0 || dst == 0)
		return 1;
	if (length <= 0)
		return 2;
	uint8_t * ptr = src;
	uint8_t * ptr1 = dst;
	ptr += length;
	while (ptr != src)
		if (--ptr == dst)
			return 3;
	ptr1 += length;
	while (ptr1 != dst)
		if (--ptr1 == src)
			return 3;
	while (length-- != 0)
		* ptr1++ = *ptr++;

	return 0;
}

int8_t mymemzero(uint8_t * src, uint32_t length)
{
	if (src == 0)
		return 1;
	if (length <= 0)
		return 2;
	uint8_t * ptr = src;
	while (length-- > 0)
	{
		* ptr++ = 0;
	}
	return 0;
}

int8_t myreverse(uint8_t * src, uint32_t length)
{
	if (src == 0)
		return 1;
	if (length <= 0)
		return 2;
	uint8_t * begin = src;
	uint8_t * end = src + length - 1;
	while (begin < end)
	{
		uint8_t swap = *begin;
		*begin++ = *end;
		*end-- = swap;
	}
	return 0;
}
