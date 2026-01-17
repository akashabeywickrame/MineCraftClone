#include "HUD.h"
#include "Textures.h"

// Helper to draw a single 2D textured square
void drawIcon(float x, float y, float size, GLuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f); // Ensure icon is bright white

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(1, 0); glVertex2f(x + size, y);
    glTexCoord2f(1, 1); glVertex2f(x + size, y + size);
    glTexCoord2f(0, 1); glVertex2f(x, y + size);
    glEnd();
}

void drawHUD() {
    glDisable(GL_DEPTH_TEST); 
    glDisable(GL_LIGHTING); 

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float iconSize = 50.0f;
    float padding = 10.0f;
    int numSlots = 5;

    float totalWidth = (iconSize * numSlots) + (padding * (numSlots - 1));
    float startX = (windowWidth - totalWidth) / 2.0f;
    float startY = 20.0f; // 20 pixels from bottom

    // 0:Grass, 1:Dirt, 2:Stone, 3:Brick(Pig), 4:Wood(Trunk)
    GLuint icons[] = { grassTexture, dirtTexture, stoneTexture, pigBodyTexture, treeTrunkTexture };

    // 4. Draw the Slots
    for (int i = 0; i < numSlots; i++) {
        float x = startX + i * (iconSize + padding);

        // Draw the Block Icon
        drawIcon(x, startY, iconSize, icons[i]);

        // Draw Selection Border (if this slot is selected)
        if (i == selectedBlockType) {
            glDisable(GL_TEXTURE_2D);
            glColor3f(1.0f, 1.0f, 1.0f); // White border
            glLineWidth(4.0f);

            glBegin(GL_LINE_LOOP);
            glVertex2f(x - 3, startY - 3);
            glVertex2f(x + iconSize + 3, startY - 3);
            glVertex2f(x + iconSize + 3, startY + iconSize + 3);
            glVertex2f(x - 3, startY + iconSize + 3);
            glEnd();

            glEnable(GL_TEXTURE_2D);
        }
    }

    // 5. Restore 3D Perspective
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}