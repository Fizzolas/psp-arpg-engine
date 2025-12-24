#ifndef CORE_TIMING_H
#define CORE_TIMING_H

void timingInit(void);
void timingShutdown(void);
void timingUpdate(void);
float timingGetDeltaTime(void);
unsigned long timingGetTicks(void);

#endif
