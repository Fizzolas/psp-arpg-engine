#include "core/timing.h"
#include <psprtc.h>

static u64 lastTick = 0;
static float deltaTime = 0.016f; // Start with 60 FPS default

void timingInit(void) {
    sceRtcGetCurrentTick(&lastTick);
    deltaTime = 0.016f;
}

void timingShutdown(void) {
}

void timingUpdate(void) {
    u64 currentTick;
    sceRtcGetCurrentTick(&currentTick);
    
    u64 tickDiff = currentTick - lastTick;
    deltaTime = (float)tickDiff / 1000000.0f;
    
    // Clamp delta time to prevent huge jumps
    if (deltaTime > 0.1f) deltaTime = 0.1f;
    if (deltaTime < 0.001f) deltaTime = 0.001f;
    
    lastTick = currentTick;
}

float timingGetDeltaTime(void) {
    return deltaTime;
}

unsigned long timingGetTicks(void) {
    u64 tick;
    sceRtcGetCurrentTick(&tick);
    return (unsigned long)(tick / 1000);
}
