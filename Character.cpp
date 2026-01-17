#include "Character.h"
#include "Textures.h"

// Helper functions internal to this file
void drawHead(float x, float y, float z, float pitch) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Rotate the head based on the camera's X-angle (looking up/down)
    glRotatef(pitch, 1.0f, 0.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, steveHeadFrontTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Top
    glBindTexture(GL_TEXTURE_2D, steveHeadBackTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Back
    glBindTexture(GL_TEXTURE_2D, steveHeadBackTexture); // FIXED
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Left
    glBindTexture(GL_TEXTURE_2D, steveHeadSideBackTexture);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    // Right
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glEnd();
    // Bottom
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glPopMatrix();
}

void drawBody(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBindTexture(GL_TEXTURE_2D, steveBodyFrontTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.75, 0.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.75, 0.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.75, 0.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.75, 0.25);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, steveBodyBackTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.75, -0.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.75, -0.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.75, -0.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.75, -0.25);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, steveBodySideTexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.75, -0.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.75, -0.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.75, 0.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.75, 0.25);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.75, -0.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.75, -0.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.75, 0.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.75, 0.25);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.75, -0.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.75, 0.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.75, 0.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.75, -0.25);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.75, -0.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.75, 0.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.75, 0.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.75, -0.25);
    glEnd();

    glPopMatrix();
}

void drawCharacter(float lookPitch) {
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);

    // Head
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    drawHead(0.0f, 0.0f, 0.0f, lookPitch);
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    drawBody(0.0f, 0.0f, 0.0f);
    glPopMatrix();

    // --- Right Arm ---
    glPushMatrix();
    glTranslatef(-0.9f, 0.5f, 0.0f);
    glRotatef(-90.0f + sin(animationAngle) * 20.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 1.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, steveArmTexture); // Front
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, steveArmTexture); // Back
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, steveBodySideTexture); // Skin
    glBegin(GL_QUADS); // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glBegin(GL_QUADS); // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
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
    glPopMatrix(); //End Right Arm

    // --- Left Arm ---
    glPushMatrix();
    glTranslatef(0.9f, 0.5f, 0.0f);
    glRotatef(-90.0f - sin(animationAngle) * 20.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 1.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, steveArmTexture); // Front
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, steveArmTexture); // Back
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, steveBodySideTexture); // Skin
    glBegin(GL_QUADS); // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glBegin(GL_QUADS); // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
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
    glPopMatrix(); //End Left Arm

    // --- Right Leg ---
    glPushMatrix();
    glTranslatef(-0.3f, -0.75f, 0.0f);
    glRotatef(sin(animationAngle) * 20.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 1.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, steveLegTexture); // Jeans
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
    glBegin(GL_QUADS); // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
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
    glBindTexture(GL_TEXTURE_2D, steveShoeTexture); // Shoe
    glBegin(GL_QUADS); // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    glPopMatrix(); // End Right Leg

    // --- Left Leg ---
    glPushMatrix();
    glTranslatef(0.3f, -0.75f, 0.0f);
    glRotatef(-sin(animationAngle) * 20.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 1.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, steveLegTexture); // Jeans
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
    glBegin(GL_QUADS); // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
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
    glBindTexture(GL_TEXTURE_2D, steveShoeTexture); // Shoe
    glBegin(GL_QUADS); // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    glPopMatrix(); // End Left Leg

    glPopMatrix(); //End Character

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}


void drawFirstPersonViewArm() {
    glClear(GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float armBobY = isCharacterMoving ? sin(animationAngle * 2.0f) * 0.02f : 0.0f;
    float armBobX = isCharacterMoving ? cos(animationAngle) * 0.01f : 0.0f;
    float angleBob = isCharacterMoving ? sin(animationAngle) * 5.0f : 0.0f;

    glTranslatef(0.3f + armBobX, -0.25f + armBobY, -0.5f);

    glRotatef(-10.0f + angleBob, 1.0f, 0.0f, 0.0f);
    glRotatef(10.0f, 0.0f, 1.0f, 0.0f);

    glScalef(0.25f, 0.75f, 0.25f);

    glBindTexture(GL_TEXTURE_2D, steveArmTexture); // Front
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, steveArmTexture); // Back
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, steveBodySideTexture); // Skin
    glBegin(GL_QUADS); // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glBegin(GL_QUADS); // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
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

    glPopMatrix();

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}
