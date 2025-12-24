#include "ui/hud.h"
#include "renderer/renderer.h"
#include <stdio.h>

static int healthCurrent = 100;
static int healthMax = 100;
static int manaCurrent = 50;
static int manaMax = 50;
static int gold = 0;

void hudInit(void) {
}

void hudShutdown(void) {
}

void hudRender(void) {
    // Health bar (top-left)
    char healthText[32];
    snprintf(healthText, sizeof(healthText), "HP: %d/%d", healthCurrent, healthMax);
    rendererDrawText(10, 10, healthText, 0xFFFF0000);
    
    // Draw health bar
    int healthBarWidth = 100;
    int healthBarFilled = (healthCurrent * healthBarWidth) / healthMax;
    rendererDrawRect(10, 25, healthBarWidth, 8, 0xFF440000);
    rendererDrawRect(10, 25, healthBarFilled, 8, 0xFFFF0000);
    
    // Mana bar
    char manaText[32];
    snprintf(manaText, sizeof(manaText), "MP: %d/%d", manaCurrent, manaMax);
    rendererDrawText(10, 40, manaText, 0xFF0000FF);
    
    int manaBarWidth = 100;
    int manaBarFilled = (manaCurrent * manaBarWidth) / manaMax;
    rendererDrawRect(10, 55, manaBarWidth, 8, 0xFF000044);
    rendererDrawRect(10, 55, manaBarFilled, 8, 0xFF0000FF);
    
    // Gold (top-right)
    char goldText[32];
    snprintf(goldText, sizeof(goldText), "Gold: %d", gold);
    rendererDrawText(380, 10, goldText, 0xFFFFFF00);
}

void hudSetHealth(int current, int max) {
    healthCurrent = current;
    healthMax = max;
}

void hudSetMana(int current, int max) {
    manaCurrent = current;
    manaMax = max;
}

void hudSetGold(int amount) {
    gold = amount;
}
