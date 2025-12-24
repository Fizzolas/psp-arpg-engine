#include "input/input.h"
#include "input/bindings.h"
#include <pspctrl.h>
#include <string.h>

static SceCtrlData pad;
static SceCtrlData prevPad;
static unsigned int buttonPressed;
static unsigned int buttonReleased;

// Action state tracking
static int actionState[ACTION_COUNT];
static int prevActionState[ACTION_COUNT];

void inputInit(void) {
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    
    memset(&pad, 0, sizeof(SceCtrlData));
    memset(&prevPad, 0, sizeof(SceCtrlData));
    memset(actionState, 0, sizeof(actionState));
    memset(prevActionState, 0, sizeof(prevActionState));
    
    bindingsInit();
}

void inputShutdown(void) {
    bindingsShutdown();
}

void inputUpdate(void) {
    prevPad = pad;
    sceCtrlReadBufferPositive(&pad, 1);
    
    buttonPressed = pad.Buttons & ~prevPad.Buttons;
    buttonReleased = prevPad.Buttons & ~pad.Buttons;
    
    // Update action states based on bindings
    memcpy(prevActionState, actionState, sizeof(actionState));
    
    // Check modifiers
    int lHeld = (pad.Buttons & PSP_CTRL_LTRIGGER) != 0;
    int rHeld = (pad.Buttons & PSP_CTRL_RTRIGGER) != 0;
    
    // Analog movement
    float analogX = (pad.Lx - 128) / 128.0f;
    float analogY = (pad.Ly - 128) / 128.0f;
    
    actionState[ACTION_MOVE_LEFT] = analogX < -0.3f;
    actionState[ACTION_MOVE_RIGHT] = analogX > 0.3f;
    actionState[ACTION_MOVE_UP] = analogY < -0.3f;
    actionState[ACTION_MOVE_DOWN] = analogY > 0.3f;
    
    // D-pad navigation
    actionState[ACTION_NAV_UP] = (pad.Buttons & PSP_CTRL_UP) != 0;
    actionState[ACTION_NAV_DOWN] = (pad.Buttons & PSP_CTRL_DOWN) != 0;
    actionState[ACTION_NAV_LEFT] = (pad.Buttons & PSP_CTRL_LEFT) != 0;
    actionState[ACTION_NAV_RIGHT] = (pad.Buttons & PSP_CTRL_RIGHT) != 0;
    
    // Face buttons with modifier support
    if (lHeld && rHeld) {
        // L+R+Button combos
        actionState[ACTION_MAP] = (pad.Buttons & PSP_CTRL_TRIANGLE) != 0;
        actionState[ACTION_SKILLS_PANEL] = (pad.Buttons & PSP_CTRL_SQUARE) != 0;
        actionState[ACTION_QUEST_LOG] = (pad.Buttons & PSP_CTRL_CIRCLE) != 0;
        actionState[ACTION_TOWN_PORTAL] = (pad.Buttons & PSP_CTRL_CROSS) != 0;
    } else if (lHeld) {
        // L+Button for skill set A
        actionState[ACTION_SKILL_1] = (pad.Buttons & PSP_CTRL_CROSS) != 0;
        actionState[ACTION_SKILL_2] = (pad.Buttons & PSP_CTRL_CIRCLE) != 0;
        actionState[ACTION_SKILL_3] = (pad.Buttons & PSP_CTRL_SQUARE) != 0;
        actionState[ACTION_SKILL_4] = (pad.Buttons & PSP_CTRL_TRIANGLE) != 0;
    } else if (rHeld) {
        // R+Button for skill set B
        actionState[ACTION_SKILL_5] = (pad.Buttons & PSP_CTRL_CROSS) != 0;
        actionState[ACTION_SKILL_6] = (pad.Buttons & PSP_CTRL_CIRCLE) != 0;
        actionState[ACTION_SKILL_7] = (pad.Buttons & PSP_CTRL_SQUARE) != 0;
        actionState[ACTION_SKILL_8] = (pad.Buttons & PSP_CTRL_TRIANGLE) != 0;
    } else {
        // Unmodified face buttons
        actionState[ACTION_PRIMARY] = (pad.Buttons & PSP_CTRL_CROSS) != 0;
        actionState[ACTION_SECONDARY] = (pad.Buttons & PSP_CTRL_CIRCLE) != 0;
        actionState[ACTION_QUICK_POTION] = (pad.Buttons & PSP_CTRL_SQUARE) != 0;
        actionState[ACTION_INVENTORY] = (pad.Buttons & PSP_CTRL_TRIANGLE) != 0;
        actionState[ACTION_CONFIRM] = (pad.Buttons & PSP_CTRL_CROSS) != 0;
        actionState[ACTION_CANCEL] = (pad.Buttons & PSP_CTRL_CIRCLE) != 0;
    }
    
    // Menu/System buttons
    actionState[ACTION_MENU] = (pad.Buttons & PSP_CTRL_START) != 0;
    actionState[ACTION_TOGGLE_UI] = (pad.Buttons & PSP_CTRL_SELECT) != 0;
    actionState[ACTION_SHOW_ITEMS] = (pad.Buttons & PSP_CTRL_SELECT) != 0;
}

int inputGetActionPressed(GameAction action) {
    if (action < 0 || action >= ACTION_COUNT) return 0;
    return actionState[action] && !prevActionState[action];
}

int inputGetActionHeld(GameAction action) {
    if (action < 0 || action >= ACTION_COUNT) return 0;
    return actionState[action];
}

int inputGetActionReleased(GameAction action) {
    if (action < 0 || action >= ACTION_COUNT) return 0;
    return !actionState[action] && prevActionState[action];
}

void inputGetAnalogStick(float* x, float* y) {
    if (x) *x = (pad.Lx - 128) / 128.0f;
    if (y) *y = (pad.Ly - 128) / 128.0f;
}

int inputIsButtonPressed(unsigned int button) {
    return (buttonPressed & button) != 0;
}

int inputIsButtonHeld(unsigned int button) {
    return (pad.Buttons & button) != 0;
}
