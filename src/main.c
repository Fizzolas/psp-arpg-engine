#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <psppower.h>
#include <stdlib.h>
#include <string.h>

#include "core/platform.h"
#include "core/timing.h"
#include "core/logging.h"
#include "renderer/renderer.h"
#include "input/input.h"
#include "ui/menu.h"
#include "assets/dataroot.h"

PSP_MODULE_INFO("PSP_ARPG_ENGINE", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024); // Use maximum available memory

typedef enum {
    STATE_SPLASH,
    STATE_MAIN_MENU,
    STATE_DATA_CHECK,
    STATE_CONTROLS,
    STATE_TEST_SCENE,
    STATE_GAME,
    STATE_QUIT
} AppState;

static AppState currentState = STATE_SPLASH;
static int running = 1;

// Exit callback
int exitCallback(int arg1, int arg2, void *common) {
    running = 0;
    return 0;
}

// Callback thread
int callbackThread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

// Setup callbacks
int setupCallbacks(void) {
    int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}

void updateSplash(float deltaTime) {
    static float timer = 0.0f;
    timer += deltaTime;
    
    if (timer > 2.0f || inputGetActionPressed(ACTION_CONFIRM)) {
        currentState = STATE_MAIN_MENU;
    }
    
    rendererClearScreen(0xFF000000);
    rendererDrawText(120, 120, "PSP ARPG Engine", 0xFFFFFFFF);
    rendererDrawText(80, 140, "Bring Your Own Diablo II Files", 0xFFAAAAAA);
    rendererDrawText(140, 200, "Press X to continue", 0xFF888888);
}

void updateMainMenu(float deltaTime) {
    menuUpdate(deltaTime);
    
    int selection = menuGetSelection();
    if (inputGetActionPressed(ACTION_CONFIRM)) {
        switch(selection) {
            case 0: // Start Game
                currentState = STATE_DATA_CHECK;
                break;
            case 1: // Controls
                currentState = STATE_CONTROLS;
                break;
            case 2: // Data Check
                currentState = STATE_DATA_CHECK;
                break;
            case 3: // Test Scene
                currentState = STATE_TEST_SCENE;
                break;
            case 4: // Quit
                currentState = STATE_QUIT;
                running = 0;
                break;
        }
    }
    
    rendererClearScreen(0xFF000000);
    menuRender();
}

void updateDataCheck(float deltaTime) {
    if (inputGetActionPressed(ACTION_CANCEL)) {
        currentState = STATE_MAIN_MENU;
    }
    
    rendererClearScreen(0xFF000000);
    rendererDrawText(10, 10, "Data Check - Required Files", 0xFFFFFFFF);
    
    DataCheckResult result = datarootCheckFiles();
    int y = 40;
    
    for (int i = 0; i < result.fileCount; i++) {
        const char* status = result.fileStatus[i] ? "[OK]" : "[MISSING]";
        unsigned int color = result.fileStatus[i] ? 0xFF00FF00 : 0xFFFF0000;
        
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%s %s", status, result.filePaths[i]);
        rendererDrawText(10, y, buffer, color);
        y += 15;
    }
    
    y += 20;
    rendererDrawText(10, y, "Copy your Diablo II files to:", 0xFFFFFFFF);
    y += 15;
    rendererDrawText(10, y, "ms0:/PSP/GAME/psparpg/gamedata/", 0xFFFFFF00);
    y += 30;
    rendererDrawText(10, y, "Press O to return to menu", 0xFF888888);
    
    datarootFreeCheckResult(&result);
}

void updateControls(float deltaTime) {
    if (inputGetActionPressed(ACTION_CANCEL)) {
        currentState = STATE_MAIN_MENU;
    }
    
    rendererClearScreen(0xFF000000);
    rendererDrawText(10, 10, "Controls Configuration", 0xFFFFFFFF);
    
    // Display current bindings
    int y = 40;
    rendererDrawText(10, y, "Movement: Analog Stick", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "X: Primary Action (Attack/Interact)", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "O: Secondary/Cancel", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "Square: Quick Potion/Action Wheel", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "Triangle: Inventory/Character", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "L + Face: Skill Set A", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "R + Face: Skill Set B", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "L + R + Triangle: Map", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "Start: Game Menu/Pause", 0xFFCCCCCC); y += 15;
    rendererDrawText(10, y, "Select: Toggle UI Mode", 0xFFCCCCCC); y += 15;
    
    y += 30;
    rendererDrawText(10, y, "Press O to return to menu", 0xFF888888);
}

void updateTestScene(float deltaTime) {
    if (inputGetActionPressed(ACTION_CANCEL)) {
        currentState = STATE_MAIN_MENU;
    }
    
    rendererClearScreen(0xFF001122);
    rendererDrawText(10, 10, "Test Scene - Input Debug", 0xFFFFFFFF);
    
    // Display active actions
    int y = 40;
    
    if (inputGetActionHeld(ACTION_MOVE_UP)) {
        rendererDrawText(10, y, "MOVE_UP active", 0xFF00FF00); y += 15;
    }
    if (inputGetActionHeld(ACTION_MOVE_DOWN)) {
        rendererDrawText(10, y, "MOVE_DOWN active", 0xFF00FF00); y += 15;
    }
    if (inputGetActionHeld(ACTION_MOVE_LEFT)) {
        rendererDrawText(10, y, "MOVE_LEFT active", 0xFF00FF00); y += 15;
    }
    if (inputGetActionHeld(ACTION_MOVE_RIGHT)) {
        rendererDrawText(10, y, "MOVE_RIGHT active", 0xFF00FF00); y += 15;
    }
    if (inputGetActionPressed(ACTION_PRIMARY)) {
        rendererDrawText(10, y, "PRIMARY pressed", 0xFFFFFF00); y += 15;
    }
    if (inputGetActionPressed(ACTION_SECONDARY)) {
        rendererDrawText(10, y, "SECONDARY pressed", 0xFFFFFF00); y += 15;
    }
    if (inputGetActionPressed(ACTION_CONFIRM)) {
        rendererDrawText(10, y, "CONFIRM pressed", 0xFFFFFF00); y += 15;
    }
    if (inputGetActionPressed(ACTION_CANCEL)) {
        rendererDrawText(10, y, "CANCEL pressed", 0xFFFFFF00); y += 15;
    }
    
    // Show analog stick values
    float analogX, analogY;
    inputGetAnalogStick(&analogX, &analogY);
    char analogBuf[64];
    snprintf(analogBuf, sizeof(analogBuf), "Analog: X=%.2f Y=%.2f", analogX, analogY);
    rendererDrawText(10, 200, analogBuf, 0xFFFFFFFF);
    
    rendererDrawText(10, 250, "Press O to return to menu", 0xFF888888);
}

int main(int argc, char *argv[]) {
    setupCallbacks();
    scePowerSetClockFrequency(333, 333, 166);
    
    // Initialize subsystems
    platformInit();
    timingInit();
    loggingInit();
    rendererInit();
    inputInit();
    menuInit();
    datarootInit();
    
    logInfo("PSP ARPG Engine started");
    
    // Setup main menu items
    menuAddItem("Start Game");
    menuAddItem("Controls");
    menuAddItem("Data Check");
    menuAddItem("Test Scene");
    menuAddItem("Quit");
    
    // Main loop
    while (running) {
        float deltaTime = timingGetDeltaTime();
        timingUpdate();
        
        inputUpdate();
        
        switch (currentState) {
            case STATE_SPLASH:
                updateSplash(deltaTime);
                break;
            case STATE_MAIN_MENU:
                updateMainMenu(deltaTime);
                break;
            case STATE_DATA_CHECK:
                updateDataCheck(deltaTime);
                break;
            case STATE_CONTROLS:
                updateControls(deltaTime);
                break;
            case STATE_TEST_SCENE:
                updateTestScene(deltaTime);
                break;
            case STATE_GAME:
                // TODO: Game loop
                break;
            case STATE_QUIT:
                running = 0;
                break;
        }
        
        rendererSwapBuffers();
    }
    
    // Cleanup
    datarootShutdown();
    menuShutdown();
    inputShutdown();
    rendererShutdown();
    loggingShutdown();
    timingShutdown();
    platformShutdown();
    
    sceKernelExitGame();
    return 0;
}
