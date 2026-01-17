#ifndef WORLD_H
#define WORLD_H

#include "Shared.h" // Just include Shared!

// Functions
void generateTerrain();
void generateClouds();
void drawTerrain();
void drawClouds();
float getTerrainHeight(float x, float z);
bool isTreeAt(int x, int y, int z);
RaycastResult castRay(float startX, float startY, float startZ, float angleX, float angleY);

#endif