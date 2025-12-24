#ifndef GAME_WORLD_H
#define GAME_WORLD_H

void worldInit(void);
void worldShutdown(void);
void worldUpdate(float deltaTime);
void worldRender(void);
void worldLoadLevel(const char* levelName);

#endif
