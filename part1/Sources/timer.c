/*
 * timer.c
 *
 *  Created on: Mar 4, 2016
 *      Author: HaoranFang
 */

#include "timer.h"
#include "MKL25z4.h"

void timer_init(){
	MCG_BASE_PTR->C1 = MCG_C1_CLKS_MASK ;

	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK | SIM_SCGC6_TPM0_MASK;
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(1); 

	//enable timer and set dividers
	TPM2_BASE_PTR->SC = TPM0_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(4);
	TPM2_BASE_PTR->MOD = TPM0_BASE_PTR->MOD = 10000;

	//TPM2_BASE_PTR->SC |= TPM_SC_TOIE_MASK;
	//NVIC->ISER[0] = 1 << 19;

	//GPIOB_PTOR |= ( 1 << 18 );
	PTB_BASE_PTR->PDDR = (1 << 18 ) | ( 1 << 19 );
//	TPM2_BASE_PTR->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
//	TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD / 8;

	PTD_BASE_PTR->PDDR = 1 << 1;
//	TPM0_BASE_PTR->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
//	TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD / 8;
}
