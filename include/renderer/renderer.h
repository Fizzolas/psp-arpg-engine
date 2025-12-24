#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H

void rendererInit(void);
void rendererShutdown(void);
void rendererClearScreen(unsigned int color);
void rendererSwapBuffers(void);
void rendererDrawText(int x, int y, const char* text, unsigned int color);
void rendererDrawRect(int x, int y, int width, int height, unsigned int color);
void rendererDrawSprite(int x, int y, int width, int height, unsigned int* pixels);

#endif
