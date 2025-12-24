#ifndef UI_HUD_H
#define UI_HUD_H

void hudInit(void);
void hudShutdown(void);
void hudRender(void);
void hudSetHealth(int current, int max);
void hudSetMana(int current, int max);
void hudSetGold(int amount);

#endif
