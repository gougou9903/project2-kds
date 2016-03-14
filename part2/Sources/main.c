/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include <stdio.h>
#include <math.h>
#include "mymemory.h"

static int i = 0;
volatile uint32_t count = 0;
volatile uint32_t count1 = 0;
volatile uint32_t count2 = 0;
volatile uint32_t colapse = 0;

int main(void)
{
	MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
	MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK;        //Select fast internal clock
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable TPM2 clock
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);

	TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(2); //4MHz clock divided by 4.
	TPM2_BASE_PTR->MOD = 10;

	TPM2_BASE_PTR->SC |= TPM_SC_TOIE_MASK;
	NVIC->ISER[0] = 1 << 19;

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	uint8_t array[6000];
	uint8_t * aptr_1 = array;
	uint8_t * aptr_2 = &array[5000];
//	uint8_t * aptr_3 = &array[6000];
//	char dest[5000];
//	char src[5000];

	while(1){
//		mymemmove(aptr_2, aptr_1, 5000);
//		memmove(aptr_1, aptr_2, 1000);
//		mymemcpy(aptr_3, aptr_1, 5000);

//		mymemzero(aptr_1, 5000);
//		memset(aptr_3, 0, 5000);

//		myreverse(aptr_1, 5000);

//		strcpy(dest, src);
//		strncpy(dest, src, 5000);

//		printf("222222222222222222222");
//		printf("%d", 45);
//		printf("%.8f", 45);

//		printf("%d%d", 45,45);
//		printf("%.8f%.8f", 45,45);

		printf("%.2f%.2f%.2f", 45, 45, 45);

	};

//	int count1 = count;
//	mymemmove(aptr_2, aptr_1, 16);
//	int count2 = count;
//	colapse = count2 - count1;

    return 0;

}

extern void TPM2_IRQHandler(){
	__disable_irq();
	count ++;
	TPM2_BASE_PTR->SC |= TPM_SC_TOF_MASK;
	__enable_irq();
}

