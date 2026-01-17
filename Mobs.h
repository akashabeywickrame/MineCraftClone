#pragma once
#ifndef MOBS_H
#define MOBS_H

#include <vector>
#include <glut.h>

enum MobType {
    MOB_PIG,
    MOB_TURTLE
};

struct Mob {
    float x, y, z;
    float rotationY;   
    float walkTimer;  
    int type;          
    float speed;
    int state;         
    int stateTimer;   
};

// Global list of mobs
extern std::vector<Mob> mobs;

void spawnMobs();
void updateMobs();
void drawMobs();
void drawPig(const Mob& m);
void drawTurtle(const Mob& m);

#endif