#pragma once
#ifndef CUBES_H
#define CUBES_H

#include "Shared.h"

void drawBlock(float x, float y, float z, GLuint topTexture, GLuint sideTexture, bool drawBottom = true);
void drawWaterBlock(float x, float y, float z);
void drawSun(float dayTime);
void drawText(float x, float y, const char* text);

#endif