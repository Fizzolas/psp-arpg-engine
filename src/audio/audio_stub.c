#include "audio/audio_stub.h"
#include "core/logging.h"

// Audio stub - to be implemented later

void audioInit(void) {
    logInfo("Audio system initialized (stub)");
}

void audioShutdown(void) {
    logInfo("Audio system shutdown (stub)");
}

void audioPlayMusic(const char* filename) {
    // TODO: Implement music playback
}

void audioPlaySound(const char* filename) {
    // TODO: Implement sound playback
}

void audioSetMusicVolume(float volume) {
    // TODO: Implement volume control
}

void audioSetSoundVolume(float volume) {
    // TODO: Implement volume control
}
