
#include <avr/io.h>
#include "../includes/servo_pump.h"

void pump_init(void){
	//configuring timer2
	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);  // Non-inverting mode (OC2A) + fast PWM + top=0xFF
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024
}

void set_pump_state(uint8_t state){ //0:off 1:on
	if(state) {
		OCR2A = 31; // ~2ms pulse (31/255 * 16.4ms ? 2ms)
	}
	else {
		OCR2A = 16; // ~1ms pulse (16/255 * 16.4ms ? 1ms)
	}
}