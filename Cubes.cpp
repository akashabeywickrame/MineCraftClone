#include "Cubes.h"
#include "Textures.h"
#include "World.h"
#include <cmath>

void drawBlock(float x, float y, float z, GLuint topTexture, GLuint sideTexture, bool drawBottom) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBindTexture(GL_TEXTURE_2D, topTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, sideTexture);
   
    glBegin(GL_QUADS); // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    glBegin(GL_QUADS); // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    glBegin(GL_QUADS); // Left
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    glBegin(GL_QUADS); // Right
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    if (drawBottom) {
        glBegin(GL_QUADS);
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
        glEnd();
    }
    glPopMatrix();
}

void drawWaterBlock(float x, float y, float z) {
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glColor4f(0.2f, 0.5f, 1.0f, 0.7f);

    glPushMatrix();
    glTranslatef(x, y, z);
    glBindTexture(GL_TEXTURE_2D, waterTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.45, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.45, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.45, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.45, 0.5);
    glEnd();
    glPopMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void drawSun(float dayTime) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    float orbitRadius = TERRAIN_SIZE * 2.0f;

    // Calculate Sun Position (Orbiting around Z-axis)
    float sunX = 0.0f;
    float sunY = sin(dayTime) * orbitRadius;
    float sunZ = cos(dayTime) * orbitRadius;

    // --- DRAW SUN ---
    glPushMatrix();
    glTranslatef(sunX, sunY, sunZ);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow Sun
    glutSolidSphere(3.0, 10, 10);
    glPopMatrix();

    // --- DRAW MOON (Opposite to Sun) ---
    glPushMatrix();
    glTranslatef(-sunX, -sunY, -sunZ); // Negative coordinates = opposite side
    glColor3f(0.9f, 0.9f, 0.9f); // White Moon
    glutSolidSphere(2.0, 10, 10);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f); // Reset color
}

void drawText(float x, float y, const char* text) {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(x, y);

    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}