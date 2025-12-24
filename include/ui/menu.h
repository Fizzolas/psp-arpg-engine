#ifndef UI_MENU_H
#define UI_MENU_H

void menuInit(void);
void menuShutdown(void);
void menuUpdate(float deltaTime);
void menuRender(void);
void menuAddItem(const char* text);
int menuGetSelection(void);
void menuSetSelection(int index);

#endif
