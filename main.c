


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "../drivers/includes/pinsDef.h"
#include "../drivers/includes/alarms.h"
#include "../drivers/includes/ultrasonic.h"
#include "../drivers/includes/servo_pump.h"

QueueHandle_t xLevelQueue;//@param ubasetype_t (specify the length),ubasetype_t(specify the size of items"in bytes");
							//the handel of the queue is the return of the createqueue function




void vSensorTask(void *pvParameters);
void vPumpTask(void *pvParameters);
void vAlarmTask(void *pvParameters);


int main(void) {
	// Initialize hardware
	ultrasonic_init();
	pump_init();
	alarms_init();
	
	// Create communication queue
	xLevelQueue = xQueueCreate(5, sizeof(float));
	
	// Create tasks
	xTaskCreate(vSensorTask, "Sensor", 128, NULL, 3, NULL);
	xTaskCreate(vPumpTask, "Pump", 128, NULL, 2, NULL);
	xTaskCreate(vAlarmTask, "Alarm", 128, NULL, 1, NULL);
	
	// Start scheduler
	vTaskStartScheduler();
	//this part is never reached
	while(1);
	return 0;
}

void vSensorTask(void *pvParameters) {
	const TickType_t xDelay = pdMS_TO_TICKS(500);
	float level;
	
	while(1) {
		level = get_water_level_cm();
		if(level >= 0) {
			xQueueSend(xLevelQueue, &level, portMAX_DELAY);
		}
		vTaskDelay(xDelay);
	}
}

void vPumpTask(void *pvParameters) {
	float level;
	const float target = 30.0f;
	
	while(1) {
		if(xQueueReceive(xLevelQueue, &level, portMAX_DELAY)) {
			if(level > target + 5.0f) {
				set_pump_state(180); // Full speed
			}
			else if(level > target) {
				set_pump_state(90);  // Half speed
			}
			else {
				set_pump_state(0);   // Off
			}
		}
	}
}

void vAlarmTask(void *pvParameters) {
	float level;
	WaterLevelState state = LEVEL_NORMAL;
	
	while(1) {
		if(xQueueReceive(xLevelQueue, &level, portMAX_DELAY)) {
			if(level > 50.0f) {
				state = LEVEL_CRITICAL;
			}
			else if(level > 40.0f) {
				state = LEVEL_WARNING;
			}
			else {
				state = LEVEL_NORMAL;
			}
			update_alarms(state);
		}
	}
}

// Error handlers
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
	PORTC = (1 << RED_PIN);
	BUZZER_PORT |= (1 << BUZZER_PIN);
	while(1);
}

void vApplicationMallocFailedHook(void) {
	PORTC = (1 << YELLOW_PIN) | (1 << RED_PIN);
	while(1);
}

