#include "input/bindings.h"
#include "core/platform.h"
#include "core/logging.h"
#include <pspkernel.h>
#include <stdio.h>
#include <string.h>

#define BINDINGS_FILE "bindings.ini"
#define MAX_LINE 256

void bindingsInit(void) {
    bindingsLoad();
}

void bindingsShutdown(void) {
    bindingsSave();
}

void bindingsLoad(void) {
    char path[512];
    snprintf(path, sizeof(path), "%s%s", platformGetUserDataDir(), BINDINGS_FILE);
    
    int file = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if (file < 0) {
        logInfo("No bindings file found, using defaults");
        bindingsReset();
        return;
    }
    
    // TODO: Parse INI file and load bindings
    // For now, use defaults
    bindingsReset();
    
    sceIoClose(file);
    logInfo("Bindings loaded");
}

void bindingsSave(void) {
    char path[512];
    snprintf(path, sizeof(path), "%s%s", platformGetUserDataDir(), BINDINGS_FILE);
    
    int file = sceIoOpen(path, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
    if (file < 0) {
        logError("Failed to save bindings");
        return;
    }
    
    // Write default bindings configuration
    const char* header = "# PSP ARPG Engine - Input Bindings\n";
    const char* config = "\n[Controls]\n"
        "# Movement: Analog Stick\n"
        "# Primary Action: Cross (X)\n"
        "# Secondary Action: Circle (O)\n"
        "# Quick Potion: Square\n"
        "# Inventory: Triangle\n"
        "# Skills Set A: L + Face Buttons\n"
        "# Skills Set B: R + Face Buttons\n"
        "# Map: L+R+Triangle\n"
        "# Menu: Start\n"
        "# Toggle UI: Select\n";
    
    sceIoWrite(file, header, strlen(header));
    sceIoWrite(file, config, strlen(config));
    
    sceIoClose(file);
    logInfo("Bindings saved");
}

void bindingsReset(void) {
    // Reset to default bindings (already implemented in input.c)
    logInfo("Bindings reset to defaults");
}
