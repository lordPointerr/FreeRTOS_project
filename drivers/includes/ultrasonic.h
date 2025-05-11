


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pinsDef.h"


void ultrasonic_init(void);
float get_water_level_cm(void);



#endif /* ULTRASONIC_H_ */