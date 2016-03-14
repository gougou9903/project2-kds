#include "MKL25Z4.h"
#include <string.h>
#include <stdio.h>
#include "timer.h"
#include "ports.h"
#include <math.h>

void Delay(int cycles){
	while(cycles --);

}

int main()
{
	portb_setup();
	timer_init();

	TPM2_BASE_PTR->CONTROLS[0].CnSC
	= TPM2_BASE_PTR->CONTROLS[1].CnSC
	= TPM0_BASE_PTR->CONTROLS[1].CnSC
	= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	double frequency = 0.05;

	for(double phase = 0;;phase += 0.005){
		double portion1 =  0.5 + sin(phase) / 2;
		double portion2 = 0.5 + sin(phase + 2) / 2;
		double portion3 = 0.5 + sin(phase + 4) / 2;
		//double redPortion = (sin(frequency*i + 0)*(127) + 128) / 255.0;
		//double greenPortion = (sin(frequency*i + 2)*(127) + 128) / 255.0;
		//double bluePortion = (sin(frequency*i + 4)*(127) + 128) / 255.0;
		TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD  * portion1;
		TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->MOD  * portion2;
		TPM0_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->MOD  * portion3;

	}

	return 0;
}

//extern void TPM2_IRQHandler(){
//	__disable_irq();
//	count ++;
//	//toggle the PTB18 pin each time the timer generates an interrupt
//	GPIOB_PTOR |= ( 1 << 18 );
//	TPM2_BASE_PTR->SC |= TPM_SC_TOF_MASK; // clear Timer Overflow bit
//
//	__enable_irq();
//}
