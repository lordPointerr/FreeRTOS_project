




#include "../includes/alarms.h"
#include "../includes/pinsDef.h"
#include "FreeRTOS.h"
#include "task.h"


void alarms_init(void) {
	LED_DDR |= (1 << GREEN_PIN) | (1 << YELLOW_PIN) | (1 << RED_PIN);
	BUZZER_DDR |= (1 << BUZZER_PIN);
}

void update_alarms(WaterLevelState state) {
	static TickType_t last_toggle = 0;
	
	switch(state) {
		case LEVEL_NORMAL:
		PORTC = (1 << GREEN_PIN);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
		break;
		
		case LEVEL_WARNING:
		PORTC = (1 << YELLOW_PIN);
		if((xTaskGetTickCount() - last_toggle) > pdMS_TO_TICKS(500)) {
			BUZZER_PORT ^= (1 << BUZZER_PIN);
			last_toggle = xTaskGetTickCount();
		}
		break;
		
		case LEVEL_CRITICAL:
		PORTC = (1 << RED_PIN);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		break;
	}
}
