


#ifndef PINSDEF_H_
#define PINSDEF_H_

#include <avr/io.h>

// ultrasonic Sensor HC-SR04
#define TRIG_PORT    PORTD
#define TRIG_DDR     DDRD
#define TRIG_PIN     PD2    // D2

#define ECHO_PORT    PIND   // for reading the echo pulse
#define ECHO_DDR     DDRD
#define ECHO_PIN     PD6    // D6

// servo Motor (Pump Control)
#define SERVO_DDR    DDRB
#define SERVO_PORT   PORTB
#define SERVO_PIN    PB3    // D11 (PWM)

// alarm System
#define BUZZER_DDR   DDRC
#define BUZZER_PORT  PORTC
#define BUZZER_PIN   PC0    // A0

#define LED_DDR      DDRC
#define GREEN_PIN    PC1     // A1
#define YELLOW_PIN   PC2     // A2
#define RED_PIN      PC3     // A3

#endif /* PINSDEF_H_ */