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
#include <string.h>

volatile int i = 0;
volatile uint8_t count = 0;

uint8_t array1[1024] ;
uint8_t array2[1024] ;

int main(void)
{
//////	uint8_t array1[10] = {1,1,1,1,1,1,1,1,1,1};
//	uint8_t * aptr_1 = array1;
//////	uint8_t array2[10] = {2,2,2,2,2,2,2,2,2,2};
//	uint8_t * aptr_2 = array2;

	/*-----set up tpm2 timer----*/
	MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
	MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK;        //Select fast internal clock
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable TPM2 clock
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);

	TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(2); //4MHz clock divided by 4.
	TPM2_BASE_PTR->MOD = 16383;

	TPM2_BASE_PTR->SC |= TPM_SC_TOIE_MASK;
	NVIC->ISER[0] = 1 << 19;

	/*----configure the dma----*/
	uint8_t array[1024];
	uint8_t * aptr_1 = array;
	uint8_t * aptr_2 = &array[1024];
	uint8_t * aptr_3 = &array[128];

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	DMAMUX0_CHCFG0 = 0x00;

	DMA_SAR0 = (uint32_t)aptr_1;
	DMA_DAR0 = (uint32_t)aptr_2;


	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(1000); // 10 bytes per transfer

	DMA_DCR0 |= (DMA_DCR_EINT_MASK |
				DMA_DCR_CS_MASK |
				DMA_DCR_SSIZE(2) |
				DMA_DCR_DSIZE(2) |
				DMA_DCR_DINC_MASK|
				DMA_DCR_DMOD(4)  |
				DMA_DCR_ERQ_MASK );

	// Enable DMA channel and source, enable to any source
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60);

	DMA_DCR0 |= DMA_DCR_START_MASK;


	// Enable interrupt
	NVIC_EnableIRQ(DMA0_IRQn);


	while(1){

	};

    return 0;
}

extern void DMA0_IRQHandler(){
	i = 1;
	count = TPM2_BASE_PTR->CNT;
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	// Clear Done Flag
}

//extern void TPM2_IRQHandler(){
//	__disable_irq();
//	count ++;
//	TPM2_BASE_PTR->SC |= TPM_SC_TOF_MASK;
//	__enable_irq();
//}
