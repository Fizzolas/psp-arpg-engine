#include "core/logging.h"
#include "core/platform.h"
#include <pspkernel.h>
#include <stdio.h>
#include <string.h>

static int logFile = -1;

void loggingInit(void) {
    // Create userdata directory first
    const char* userDir = platformGetUserDataDir();
    sceIoMkdir(userDir, 0777);
    
    // Open log file on Memory Stick
    char logPath[256];
    snprintf(logPath, sizeof(logPath), "%sengine.log", userDir);
    
    logFile = sceIoOpen(logPath, 
                        PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
}

void loggingShutdown(void) {
    if (logFile >= 0) {
        sceIoClose(logFile);
        logFile = -1;
    }
}

void logInfo(const char* message) {
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "[INFO] %s\n", message);
    
    if (logFile >= 0) {
        sceIoWrite(logFile, buffer, strlen(buffer));
    }
}

void logWarning(const char* message) {
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "[WARN] %s\n", message);
    
    if (logFile >= 0) {
        sceIoWrite(logFile, buffer, strlen(buffer));
    }
}

void logError(const char* message) {
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "[ERROR] %s\n", message);
    
    if (logFile >= 0) {
        sceIoWrite(logFile, buffer, strlen(buffer));
    }
}
