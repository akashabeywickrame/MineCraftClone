#ifndef TEXTURES_H
#define TEXTURES_H

#include "Shared.h"

// Texture IDs
extern GLuint grassTexture;
extern GLuint dirtTexture;
extern GLuint stoneTexture;
extern GLuint waterTexture;
extern GLuint cloudBlockTexture;
extern GLuint treeTrunkTexture;
extern GLuint treeLeafTexture;
extern GLuint soilFloorTexture;

// Steve Textures
extern GLuint steveHeadFrontTexture;
extern GLuint steveHeadSideBackTexture;
extern GLuint steveBodyFrontTexture;
extern GLuint steveBodyBackTexture;
extern GLuint steveBodySideTexture;
extern GLuint steveArmTexture;
extern GLuint steveLegTexture;
extern GLuint steveShoeTexture;
extern GLuint steveHeadBackTexture;

// --- NEW ANIMAL TEXTURES (SEPARATED) ---
extern GLuint pigFaceTexture;
extern GLuint pigBodyTexture;
extern GLuint turtleFaceTexture;
extern GLuint turtleShellTexture;
extern GLuint turtleSkinTexture;

extern GLuint menuBackgroundTexture; // <--- NEW

void loadAllTextures();
void loadTexture(GLuint* textureID, const char* filename);

#endif
