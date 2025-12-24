#include "core/platform.h"
#include <string.h>

static char appDir[256] = "ms0:/PSP/GAME/psparpg/";
static char userDataDir[256] = "ms0:/PSP/GAME/psparpg/userdata/";
static char gameDataDir[256] = "ms0:/PSP/GAME/psparpg/gamedata/";

void platformInit(void) {
    // Platform-specific initialization
    // Directories are predefined for PSP Memory Stick layout
}

void platformShutdown(void) {
    // Platform-specific cleanup
}

const char* platformGetAppDir(void) {
    return appDir;
}

const char* platformGetUserDataDir(void) {
    return userDataDir;
}

const char* platformGetGameDataDir(void) {
    return gameDataDir;
}
