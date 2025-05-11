


#ifndef ALARMS_H_
#define ALARMS_H_

typedef enum {
	LEVEL_NORMAL,
	LEVEL_WARNING,
	LEVEL_CRITICAL
} WaterLevelState;

void alarms_init(void); //configuring I/Os
void update_alarms(WaterLevelState state);


#endif /* ALARMS_H_ */