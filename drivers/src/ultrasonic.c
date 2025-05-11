

#include "../includes/ultrasonic.h"

volatile uint32_t pulse_start = 0;
volatile uint32_t pulse_end = 0;
volatile uint8_t measurement_ready = 0;

void ultrasonic_init(void){
	// i'll work with timer1 to read the input from the sensor
	TCCR1B |= (1 << ICNC1) | (1 << ICES1) | (1 << CS11); // Noise cancel, rising edge, prescaler 8 (2MHz clk)
	// enabling the input capture interrupt
	TIMSK1 |= (1 << ICIE1);
	
	//configure GPIO
	TRIG_DDR |= (1 << TRIG_PIN);  // Trigger as output
	ECHO_DDR &= ~(1 << ECHO_PIN); // Echo as input
}

ISR(TIMER1_CAPT_vect) {
	if (TCCR1B & (1 << ICES1)) { // Rising edge
		pulse_start = ICR1;
		TCCR1B &= ~(1 << ICES1); // Switch to falling edge
		} else { // Falling edge
		pulse_end = ICR1;
		measurement_ready = 1;
		TCCR1B |= (1 << ICES1); // Switch back to rising edge
	}
}

float get_water_level_cm() {
	// Trigger pulse
	TRIG_PORT |= (1 << TRIG_PIN);
	_delay_us(10);
	TRIG_PORT &= ~(1 << TRIG_PIN);

	// Wait for measurement
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(!measurement_ready) {
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
	}
	
	// Calculate distance
	uint32_t pulse_duration = pulse_end - pulse_start;
	measurement_ready = 0;
	return (pulse_duration * 0.034) / 2; // cm
}