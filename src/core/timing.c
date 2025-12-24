#include "core/timing.h"
#include <psprtc.h>

static u64 lastTick = 0;
static float deltaTime = 0.0f;

void timingInit(void) {
    sceRtcGetCurrentTick(&lastTick);
}

void timingShutdown(void) {
}

void timingUpdate(void) {
    u64 currentTick;
    sceRtcGetCurrentTick(&currentTick);
    
    u64 tickDiff = currentTick - lastTick;
    deltaTime = (float)tickDiff / 1000000.0f; // Convert to seconds
    
    lastTick = currentTick;
}

float timingGetDeltaTime(void) {
    return deltaTime;
}

unsigned long timingGetTicks(void) {
    u64 tick;
    sceRtcGetCurrentTick(&tick);
    return (unsigned long)(tick / 1000); // Return milliseconds
}
