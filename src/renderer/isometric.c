#include "renderer/isometric.h"
#include "renderer/renderer.h"
#include <math.h>

#define TILE_WIDTH 32
#define TILE_HEIGHT 16

static float cameraX = 0.0f;
static float cameraY = 0.0f;

void isometricInit(void) {
    cameraX = 0.0f;
    cameraY = 0.0f;
}

void isometricSetCameraPos(float x, float y) {
    cameraX = x;
    cameraY = y;
}

ScreenCoord isometricWorldToScreen(WorldCoord world) {
    ScreenCoord screen;
    
    // Classic isometric projection (2:1 ratio)
    float adjX = world.worldX - cameraX;
    float adjY = world.worldY - cameraY;
    
    screen.screenX = (int)((adjX - adjY) * (TILE_WIDTH / 2.0f)) + 240;
    screen.screenY = (int)((adjX + adjY) * (TILE_HEIGHT / 2.0f)) - (int)(world.worldZ * TILE_HEIGHT) + 136;
    
    return screen;
}

WorldCoord isometricScreenToWorld(ScreenCoord screen) {
    WorldCoord world;
    
    // Inverse isometric projection
    float screenX = (float)(screen.screenX - 240);
    float screenY = (float)(screen.screenY - 136);
    
    world.worldX = (screenX / (TILE_WIDTH / 2.0f) + screenY / (TILE_HEIGHT / 2.0f)) / 2.0f + cameraX;
    world.worldY = (screenY / (TILE_HEIGHT / 2.0f) - screenX / (TILE_WIDTH / 2.0f)) / 2.0f + cameraY;
    world.worldZ = 0.0f;
    
    return world;
}

void isometricDrawTile(int tileX, int tileY, unsigned int color) {
    WorldCoord corners[4] = {
        {(float)tileX, (float)tileY, 0.0f},
        {(float)(tileX + 1), (float)tileY, 0.0f},
        {(float)(tileX + 1), (float)(tileY + 1), 0.0f},
        {(float)tileX, (float)(tileY + 1), 0.0f}
    };
    
    ScreenCoord screenCorners[4];
    for (int i = 0; i < 4; i++) {
        screenCorners[i] = isometricWorldToScreen(corners[i]);
    }
    
    // Draw tile outline (simplified - full implementation would fill polygon)
    for (int i = 0; i < 4; i++) {
        int next = (i + 1) % 4;
        // Draw line approximation
        rendererDrawRect(screenCorners[i].screenX, screenCorners[i].screenY, 2, 2, color);
    }
}
