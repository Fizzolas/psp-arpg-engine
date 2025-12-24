#include "ui/menu.h"
#include "renderer/renderer.h"
#include "input/input.h"
#include <string.h>
#include <stdio.h>

#define MAX_MENU_ITEMS 16
#define MAX_ITEM_TEXT 64

static char menuItems[MAX_MENU_ITEMS][MAX_ITEM_TEXT];
static int menuItemCount = 0;
static int currentSelection = 0;

void menuInit(void) {
    menuItemCount = 0;
    currentSelection = 0;
}

void menuShutdown(void) {
}

void menuUpdate(float deltaTime) {
    if (inputGetActionPressed(ACTION_NAV_UP)) {
        currentSelection--;
        if (currentSelection < 0) currentSelection = menuItemCount - 1;
    }
    
    if (inputGetActionPressed(ACTION_NAV_DOWN)) {
        currentSelection++;
        if (currentSelection >= menuItemCount) currentSelection = 0;
    }
}

void menuRender(void) {
    rendererDrawText(180, 50, "PSP ARPG Engine", 0xFFFFFFFF);
    rendererDrawText(160, 70, "Diablo II (BYO Files)", 0xFFAAAAAA);
    
    int y = 110;
    for (int i = 0; i < menuItemCount; i++) {
        unsigned int color = (i == currentSelection) ? 0xFFFFFF00 : 0xFFCCCCCC;
        const char* prefix = (i == currentSelection) ? "> " : "  ";
        
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%s%s", prefix, menuItems[i]);
        rendererDrawText(200, y, buffer, color);
        y += 20;
    }
}

void menuAddItem(const char* text) {
    if (menuItemCount < MAX_MENU_ITEMS && text) {
        strncpy(menuItems[menuItemCount], text, MAX_ITEM_TEXT - 1);
        menuItems[menuItemCount][MAX_ITEM_TEXT - 1] = '\0';
        menuItemCount++;
    }
}

int menuGetSelection(void) {
    return currentSelection;
}

void menuSetSelection(int index) {
    if (index >= 0 && index < menuItemCount) {
        currentSelection = index;
    }
}
