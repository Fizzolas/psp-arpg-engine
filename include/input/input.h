#ifndef INPUT_INPUT_H
#define INPUT_INPUT_H

typedef enum {
    // Core movement
    ACTION_MOVE_UP,
    ACTION_MOVE_DOWN,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    
    // Primary actions
    ACTION_PRIMARY,      // Attack/Interact (X)
    ACTION_SECONDARY,    // Alt skill/Cancel (O)
    ACTION_QUICK_POTION, // Potion/Action wheel (Square)
    ACTION_INVENTORY,    // Inventory/Character (Triangle)
    
    // Skill sets
    ACTION_SKILL_1,      // L+X
    ACTION_SKILL_2,      // L+O
    ACTION_SKILL_3,      // L+Square
    ACTION_SKILL_4,      // L+Triangle
    ACTION_SKILL_5,      // R+X
    ACTION_SKILL_6,      // R+O
    ACTION_SKILL_7,      // R+Square
    ACTION_SKILL_8,      // R+Triangle
    
    // UI navigation
    ACTION_MENU,         // Start (Pause/Menu)
    ACTION_MAP,          // L+R+Triangle
    ACTION_CHARACTER,    // Triangle (when no modifier)
    ACTION_SKILLS_PANEL, // L+R+Square
    ACTION_QUEST_LOG,    // L+R+O
    ACTION_TOGGLE_UI,    // Select (UI cursor mode)
    
    // Navigation
    ACTION_CONFIRM,      // X in menus
    ACTION_CANCEL,       // O in menus
    ACTION_NAV_UP,       // D-pad up
    ACTION_NAV_DOWN,     // D-pad down
    ACTION_NAV_LEFT,     // D-pad left
    ACTION_NAV_RIGHT,    // D-pad right
    
    // Belt/Quick access
    ACTION_BELT_1,       // D-pad + modifier
    ACTION_BELT_2,
    ACTION_BELT_3,
    ACTION_BELT_4,
    
    // Multiplayer/Social
    ACTION_TOWN_PORTAL,  // L+R+X
    ACTION_DROP_ITEM,    // L+R+Select
    
    // Special
    ACTION_RUN_WALK,     // Double-tap analog or R3 press if mapped
    ACTION_SHOW_ITEMS,   // Hold Select
    
    ACTION_COUNT
} GameAction;

void inputInit(void);
void inputShutdown(void);
void inputUpdate(void);

int inputGetActionPressed(GameAction action);
int inputGetActionHeld(GameAction action);
int inputGetActionReleased(GameAction action);
void inputGetAnalogStick(float* x, float* y);

// Button state queries
int inputIsButtonPressed(unsigned int button);
int inputIsButtonHeld(unsigned int button);

#endif
