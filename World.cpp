#define _USE_MATH_DEFINES 
#include <cmath>

#include "World.h"
#include "Cubes.h"
#include "Textures.h"
#include "Perlin.h"
#include <cstdlib>
#include <iostream>

#ifndef BLOCKS_PER_CLOUD
#define BLOCKS_PER_CLOUD 20
#define CLOUD_SPREAD 4
#endif

int terrain[TERRAIN_SIZE][TERRAIN_SIZE];
int treeHeight[TERRAIN_SIZE][TERRAIN_SIZE];

int worldBlockType[TERRAIN_SIZE][TERRAIN_SIZE];
int selectedBlockType = 0;


std::vector<Cloud> clouds;


float getTerrainHeight(float x, float z) {
    int gridX = (int)floor(x + TERRAIN_SIZE / 2.0f);
    int gridZ = (int)floor(z + TERRAIN_SIZE / 2.0f);

    if (gridX < 0 || gridX >= TERRAIN_SIZE || gridZ < 0 || gridZ >= TERRAIN_SIZE) {
        return 0.0f; 
    }

    return (float)terrain[gridX][gridZ];
}

void generateTerrain() {
    PerlinNoise pn; 

    for (int x = 0; x < TERRAIN_SIZE; ++x) {
        for (int z = 0; z < TERRAIN_SIZE; ++z) {
            terrain[x][z] = TERRAIN_HEIGHT;
            treeHeight[x][z] = 0;
            
            worldBlockType[x][z] = 0;
        }
    }
   
    const double frequency = 0.03;
    const double amp = 4.0;

    for (int x = 0; x < TERRAIN_SIZE; ++x) {
        for (int z = 0; z < TERRAIN_SIZE; ++z) {
            double nx = x * frequency;
            double nz = z * frequency;
            double n = pn.noise(nx, nz, 0.0) * amp;
            int h = (int)floor((double)TERRAIN_HEIGHT + n);

            // Safety Clamps
            if (h < 1) h = 1;
            if (h > TERRAIN_HEIGHT + 5) h = TERRAIN_HEIGHT + 5; 

            terrain[x][z] = h;
        }
    }

    int riverWidth = 4;
    for (int x = 0; x < TERRAIN_SIZE; ++x) {
        for (int z = TERRAIN_SIZE / 2 - riverWidth / 2; z < TERRAIN_SIZE / 2 + riverWidth / 2; ++z) {
            if (z >= 0 && z < TERRAIN_SIZE) terrain[x][z] = WATER_LEVEL - 1;
        }
    }

    for (int x = 2; x < TERRAIN_SIZE - 2; ++x) {
        for (int z = 2; z < TERRAIN_SIZE - 2; ++z) {
            int h = terrain[x][z];

            if (h >= WATER_LEVEL) {
                double forestNoise = pn.noise(x * 0.12, z * 0.12, 0.0);

                if (forestNoise > 0.15) {
                    if ((rand() % 30) < 5) {
                        treeHeight[x][z] = (rand() % 3) + 3;
                    }
                }
                else {
                    if ((rand() % 1000) < 1) {
                        treeHeight[x][z] = (rand() % 3) + 3;
                    }
                }
            }
        }
    }

    int cx = TERRAIN_SIZE / 2;
    int cz = TERRAIN_SIZE / 2;
    for (int x = cx - 2; x <= cx + 2; ++x) {
        for (int z = cz - 2; z <= cz + 2; ++z) {
            if (x >= 0 && x < TERRAIN_SIZE && z >= 0 && z < TERRAIN_SIZE) {
                terrain[x][z] = WATER_LEVEL + 1;
                treeHeight[x][z] = 0;
            }
        }
    }
}

RaycastResult castRay(float startX, float startY, float startZ, float angleX, float angleY) {
    RaycastResult result = { false, 0, 0, 0, 0, 0, 0 };
    const float step = 0.1f;
    const float maxDist = 6.0f;

    float radY = angleY * (float)M_PI / 180.0f;
    float radX = angleX * (float)M_PI / 180.0f;

    float dirX = sinf(radY) * cosf(radX);
    float dirY = -sinf(radX);
    float dirZ = -cosf(radY) * cosf(radX);

    float currentX = startX;
    float currentY = startY;
    float currentZ = startZ;

    int prevGridX = (int)floor(startX + TERRAIN_SIZE / 2.0f);
    int prevGridY = (int)floor(startY);
    int prevGridZ = (int)floor(startZ + TERRAIN_SIZE / 2.0f);

    for (float d = 0.0f; d < maxDist; d += step) {
        currentX += dirX * step;
        currentY += dirY * step;
        currentZ += dirZ * step;

        int gridX = (int)floor(currentX + TERRAIN_SIZE / 2.0f);
        int gridZ = (int)floor(currentZ + TERRAIN_SIZE / 2.0f);
        int gridY = (int)floor(currentY);

        if (gridX < 0 || gridX >= TERRAIN_SIZE || gridZ < 0 || gridZ >= TERRAIN_SIZE) {
            prevGridX = gridX; prevGridY = gridY; prevGridZ = gridZ;
            continue;
        }

        int groundHeight = terrain[gridX][gridZ];
        if (gridY < groundHeight && gridY >= groundHeight - 1) {
            result.hit = true;
            result.x = gridX; result.y = gridY; result.z = gridZ;
            result.faceX = prevGridX; result.faceY = prevGridY; result.faceZ = prevGridZ;
            return result;
        }

        int tHeight = treeHeight[gridX][gridZ];
        if (tHeight > 0) {
            int treeTop = groundHeight + tHeight;
            if (gridY >= groundHeight && gridY < treeTop) {
                result.hit = true;
                result.x = gridX; result.y = gridY; result.z = gridZ;
                result.faceX = prevGridX; result.faceY = prevGridY; result.faceZ = prevGridZ;
                return result;
            }
        }
        prevGridX = gridX; prevGridY = gridY; prevGridZ = gridZ;
    }
    return result;
}

void drawTree(float x, float y, float z, int trunkHeight) {
    for (int i = 0; i < trunkHeight; ++i) {
        drawBlock(x, y + i, z, treeTrunkTexture, treeTrunkTexture, true);
    }
    float leafBaseY = y + trunkHeight;
    for (int lx = -1; lx <= 1; ++lx) {
        for (int lz = -1; lz <= 1; ++lz) {
            drawBlock(x + lx, leafBaseY, z + lz, treeLeafTexture, treeLeafTexture, true);
        }
    }
    drawBlock(x, leafBaseY + 1, z, treeLeafTexture, treeLeafTexture, true);
}

void drawTerrain() {
    for (int x = 0; x < TERRAIN_SIZE; ++x) {
        for (int z = 0; z < TERRAIN_SIZE; ++z) {
            int height = terrain[x][z];
            
            int type = worldBlockType[x][z];

            for (int y = 0; y < height; ++y) {
                if (y == height - 1) {
                    // Default to Grass
                    GLuint topTex = grassTexture;
                    GLuint sideTex = dirtTexture;

                    if (type == 1) { topTex = dirtTexture; sideTex = dirtTexture; }       // Dirt
                    else if (type == 2) { topTex = stoneTexture; sideTex = stoneTexture; } // Stone
                    else if (type == 3) { topTex = pigBodyTexture; sideTex = pigBodyTexture; } // Brick (Placeholder)
                    else if (type == 4) { topTex = treeTrunkTexture; sideTex = treeTrunkTexture; } // Wood

                    drawBlock(x - TERRAIN_SIZE / 2, y, z - TERRAIN_SIZE / 2, topTex, sideTex, true);
                }
                else if (y > height - 4) {
                    drawBlock(x - TERRAIN_SIZE / 2, y, z - TERRAIN_SIZE / 2, dirtTexture, dirtTexture, true);
                }
                else {
                    drawBlock(x - TERRAIN_SIZE / 2, y, z - TERRAIN_SIZE / 2, stoneTexture, stoneTexture, true);
                }
            }

            if (height < WATER_LEVEL) {
                for (int y = height; y < WATER_LEVEL; ++y) {
                    drawWaterBlock(x - TERRAIN_SIZE / 2, y, z - TERRAIN_SIZE / 2);
                }
            }

            if (treeHeight[x][z] > 0) {
                drawTree(x - TERRAIN_SIZE / 2, height, z - TERRAIN_SIZE / 2, treeHeight[x][z]);
            }
        }
    }
}

void generateClouds() {
    clouds.clear();
    for (int i = 0; i < CLOUD_COUNT; ++i) {
        Cloud newCloud;
        newCloud.posX = (float)(rand() % (TERRAIN_SIZE * 3)) - TERRAIN_SIZE * 1.5f;
        newCloud.posY = (float)(rand() % 5) + TERRAIN_HEIGHT + 10.0f;
        newCloud.posZ = (float)(rand() % (TERRAIN_SIZE * 3)) - TERRAIN_SIZE * 1.5f;
        newCloud.individualCloudMovementX = (float)(rand() % 100) / 100.0f * 50.0f;
        newCloud.individualCloudMovementZ = (float)(rand() % 100) / 100.0f * 50.0f;

        for (int j = 0; j < BLOCKS_PER_CLOUD; ++j) {
            CloudBlock block;
            block.x = (float)(rand() % ((int)(CLOUD_SPREAD * 2))) - CLOUD_SPREAD;
            block.y = 0.0f;
            block.z = (float)(rand() % ((int)(CLOUD_SPREAD * 2))) - CLOUD_SPREAD;
            newCloud.blocks.push_back(block);
        }
        clouds.push_back(newCloud);
    }
    std::cout << "Generated " << clouds.size() << " cloud clusters." << std::endl;
}

bool isTreeAt(int gridX, int gridY, int gridZ) {
    if (gridX < 0 || gridX >= TERRAIN_SIZE || gridZ < 0 || gridZ >= TERRAIN_SIZE) return false;
    if (treeHeight[gridX][gridZ] <= 0) return false;
    int groundHeight = terrain[gridX][gridZ];
    int treeTop = groundHeight + treeHeight[gridX][gridZ];
    return (gridY >= groundHeight && gridY < treeTop);
}

void drawClouds() {
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    for (const auto& cloud : clouds) {
        glPushMatrix();
        glTranslatef(cloud.posX + cloud.individualCloudMovementX, cloud.posY, cloud.posZ + cloud.individualCloudMovementZ);
        for (const auto& block : cloud.blocks) {
            drawBlock(block.x, block.y, block.z, cloudBlockTexture, cloudBlockTexture, true);
        }
        glPopMatrix();
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}