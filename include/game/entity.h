#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

typedef struct Entity Entity;

void entitySystemInit(void);
void entitySystemShutdown(void);
void entitySystemUpdate(float deltaTime);
void entitySystemRender(void);

Entity* entityCreate(float x, float y);
void entityDestroy(Entity* entity);
void entitySetPosition(Entity* entity, float x, float y);
void entityGetPosition(Entity* entity, float* x, float* y);

#endif
