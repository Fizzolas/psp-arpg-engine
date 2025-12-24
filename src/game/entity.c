#include "game/entity.h"
#include "core/logging.h"
#include <stdlib.h>

#define MAX_ENTITIES 256

struct Entity {
    int active;
    float x, y;
    int type;
    // TODO: Add sprite, animation, stats, inventory, etc.
};

static Entity entities[MAX_ENTITIES];

void entitySystemInit(void) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entities[i].active = 0;
    }
    logInfo("Entity system initialized");
}

void entitySystemShutdown(void) {
    logInfo("Entity system shutdown");
}

void entitySystemUpdate(float deltaTime) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (entities[i].active) {
            // TODO: Update entity logic
        }
    }
}

void entitySystemRender(void) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (entities[i].active) {
            // TODO: Render entity sprite at position
        }
    }
}

Entity* entityCreate(float x, float y) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (!entities[i].active) {
            entities[i].active = 1;
            entities[i].x = x;
            entities[i].y = y;
            return &entities[i];
        }
    }
    return NULL;
}

void entityDestroy(Entity* entity) {
    if (entity) {
        entity->active = 0;
    }
}

void entitySetPosition(Entity* entity, float x, float y) {
    if (entity && entity->active) {
        entity->x = x;
        entity->y = y;
    }
}

void entityGetPosition(Entity* entity, float* x, float* y) {
    if (entity && entity->active) {
        if (x) *x = entity->x;
        if (y) *y = entity->y;
    }
}
