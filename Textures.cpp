#include "Textures.h"
#include <stdio.h> // For printf

// --- Define Global Variables ---
GLuint grassTexture, dirtTexture, stoneTexture, waterTexture;
GLuint cloudBlockTexture, treeTrunkTexture, treeLeafTexture, soilFloorTexture;
GLuint steveHeadFrontTexture, steveHeadSideBackTexture, steveHeadBackTexture;
GLuint steveBodyFrontTexture, steveBodyBackTexture, steveBodySideTexture;
GLuint steveArmTexture, steveLegTexture, steveShoeTexture;
GLuint pigFaceTexture, pigBodyTexture;
GLuint turtleFaceTexture, turtleShellTexture, turtleSkinTexture;
GLuint menuBackgroundTexture; // <--- The Menu Texture

// Helper function to load texture
void loadTexture(GLuint* textureID, const char* filename) {
    *textureID = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (!(*textureID)) {
        printf("❌ ERROR: Texture loading failed for '%s': %s\n", filename, SOIL_last_result());
    }
    else {
        printf("✅ Loaded texture '%s' (ID: %u)\n", filename, *textureID);
    }

    glBindTexture(GL_TEXTURE_2D, *textureID);

    // Default to Pixel Art style (Sharp pixels)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Clamp edges so we don't see seams
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void loadAllTextures() {
    printf("--- Loading Textures ---\n");

    loadTexture(&grassTexture, "grass.jpg");
    loadTexture(&dirtTexture, "soil1.jpg");
    loadTexture(&stoneTexture, "stone.jpg");
    loadTexture(&waterTexture, "water.jpg");

    // Steve Parts
    loadTexture(&steveHeadFrontTexture, "steve_head.jpg");
    loadTexture(&steveHeadSideBackTexture, "head_side.png");
    loadTexture(&steveHeadBackTexture, "black-hair.jpg");
    loadTexture(&steveBodyFrontTexture, "front_body.png");
    loadTexture(&steveBodyBackTexture, "body_back.png");
    loadTexture(&steveBodySideTexture, "side.png");
    loadTexture(&steveArmTexture, "hand.png");
    loadTexture(&steveLegTexture, "leg.png");
    loadTexture(&steveShoeTexture, "shoe.png");

    // Environment
    loadTexture(&cloudBlockTexture, "clouds.png");
    loadTexture(&treeTrunkTexture, "xa40ixptjv761.jpg");
    loadTexture(&treeLeafTexture, "tree.jpg");
    loadTexture(&soilFloorTexture, "soil_floor.jpg");

    // Mobs
    loadTexture(&pigFaceTexture, "pig_face.jpeg");
    loadTexture(&pigBodyTexture, "pig_body.jpg");
    loadTexture(&turtleFaceTexture, "turtle_face.jpg");
    loadTexture(&turtleShellTexture, "turtle_shell.png");

    // --- LOAD MENU BACKGROUND ---
    loadTexture(&menuBackgroundTexture, "bg1.jpg");
    
    if (menuBackgroundTexture) {
        glBindTexture(GL_TEXTURE_2D, menuBackgroundTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    printf("------------------------\n");
}