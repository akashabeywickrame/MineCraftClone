#ifndef SHARED_H
#define SHARED_H


#define _USE_MATH_DEFINES 
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>


#define GLUT_DISABLE_ATEXIT_HACK


#include <glut.h>
#include <SOIL2.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int TERRAIN_SIZE = 32;     
const int TERRAIN_HEIGHT = 10;
const int WATER_LEVEL = 8;
const int CLOUD_COUNT = 5;
const int BLOCKS_PER_CLOUD = 15;
const float CLOUD_SPREAD = 3.0f;


struct CloudBlock {
    float x, y, z;
};

struct Cloud {
    float posX, posY, posZ;
    std::vector<CloudBlock> blocks;
    float individualCloudMovementX;
    float individualCloudMovementZ;
};


struct RaycastResult {
    bool hit;       
    int x, y, z;   
    int faceX, faceY, faceZ; 
};


extern int windowWidth;
extern int windowHeight;

extern float characterX, characterY, characterZ;
extern float verticalVelocity;
extern bool isGrounded;
extern bool isCharacterMoving;
extern float animationAngle;
extern bool isFirstPersonView;
extern float viewAngleX, viewAngleY;
extern float zoom;


// Day/Night Cycle
extern float dayTime;

// World Data
extern int terrain[TERRAIN_SIZE][TERRAIN_SIZE];
extern int treeHeight[TERRAIN_SIZE][TERRAIN_SIZE];

extern int worldBlockType[TERRAIN_SIZE][TERRAIN_SIZE];
extern int selectedBlockType;

extern std::vector<Cloud> clouds;

#endif 