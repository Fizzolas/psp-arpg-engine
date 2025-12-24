#ifndef RENDERER_ISOMETRIC_H
#define RENDERER_ISOMETRIC_H

// Isometric projection utilities
typedef struct {
    int screenX;
    int screenY;
} ScreenCoord;

typedef struct {
    float worldX;
    float worldY;
    float worldZ;
} WorldCoord;

void isometricInit(void);
void isometricSetCameraPos(float x, float y);
ScreenCoord isometricWorldToScreen(WorldCoord world);
WorldCoord isometricScreenToWorld(ScreenCoord screen);
void isometricDrawTile(int tileX, int tileY, unsigned int color);

#endif
