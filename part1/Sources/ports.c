#include "ports.h"
#include "MKL25Z4.h"

void portb_setup(){
	// Enable the PortB and PortD clock
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	// Configure Mode of port to be GPIO use
	//PORTB_PCR18 = PORT_PCR_MUX(1);

//	// Set Direction of port to output PB.18
//	GPIOB_PDDR |= (1<<18);
//
//	// Start Pin LED
//	GPIOB_PDOR |= (1<<18);

	PORTB_PCR18 = PORTB_PCR19 = PORT_PCR_MUX(3); //TPM2_CHANNEL0 port 18 TPM output instead of GPIO
	PORTD_PCR1 = PORT_PCR_MUX(4);  //TPM0_CHANNEL0 port 1 TPM output
}
