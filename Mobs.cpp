#include "Mobs.h"
#include "World.h"
#include "Textures.h" // [IMPORTANT] Include this to access texture IDs
#include <cmath>
#include <cstdlib>

std::vector<Mob> mobs;

void spawnMobs() {
    mobs.clear();
    int mobCount = 12;

    for (int i = 0; i < mobCount; i++) {
        Mob m;
        // Random Position
        m.x = (rand() % (TERRAIN_SIZE - 4)) - (TERRAIN_SIZE / 2) + 2;
        m.z = (rand() % (TERRAIN_SIZE - 4)) - (TERRAIN_SIZE / 2) + 2;
        m.y = getTerrainHeight(m.x, m.z); 

        m.rotationY = (float)(rand() % 360);
        m.type = (rand() % 2); // 0 = Pig, 1 = Turtle
        m.speed = (m.type == MOB_PIG) ? 0.03f : 0.01f;
        m.walkTimer = 0.0f;
        m.state = 0;
        m.stateTimer = rand() % 100;

        if (m.y >= WATER_LEVEL) {
            mobs.push_back(m);
        }
    }
}

void updateMobs() {
    for (auto& m : mobs) {
        m.stateTimer--;
        if (m.stateTimer <= 0) {
            m.state = rand() % 2; // 0=Idle, 1=Walk
            m.stateTimer = (rand() % 100) + 50;
            if (m.state == 1) m.rotationY = (float)(rand() % 360);
        }

        //MOVEMENT ---
        if (m.state == 1) {
            m.walkTimer += 0.2f;

            float rad = m.rotationY * 3.14159f / 180.0f;
            float nextX = m.x + sin(rad) * m.speed;
            float nextZ = m.z + cos(rad) * m.speed;

            // Boundary Check
            if (nextX > -TERRAIN_SIZE / 2 && nextX < TERRAIN_SIZE / 2 &&
                nextZ > -TERRAIN_SIZE / 2 && nextZ < TERRAIN_SIZE / 2) {
                m.x = nextX;
                m.z = nextZ;
            }
            else {
                m.rotationY += 180.0f; // Turn around at edge
            }
        }
        else {
            m.walkTimer = 0.0f;
        }

        //GRAVITY SNAP

        float groundHeight = getTerrainHeight(m.x, m.z);

        if (groundHeight < WATER_LEVEL) {
            m.y = WATER_LEVEL;
        }
        else {
            m.y = groundHeight;
        }
    }
}
void drawTexturedBox(float width, float height, float length, GLuint textureID) {
    glPushMatrix();
    glScalef(width, height, length);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    // Front
    glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5); glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5); glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5); glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    // Back
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5); glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5); glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    // Left
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5); glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5); glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5); glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    // Right
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5); glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5); glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, 0.5); glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    // Top
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5); glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, 0.5); glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    // Bottom
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5); glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, -0.5); glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5); glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glPopMatrix();
}

void drawHeadWithFace(float size, GLuint faceTex, GLuint bodyTex) {
    glPushMatrix();
    glScalef(size, size, size);

    glBindTexture(GL_TEXTURE_2D, faceTex);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, bodyTex);
    glBegin(GL_QUADS);
    // Back
    glNormal3f(0.0, 0.0, -1.0); glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5); glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5); glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    // Left
    glNormal3f(-1.0, 0.0, 0.0); glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5); glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5); glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5); glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    // Right
    glNormal3f(1.0, 0.0, 0.0); glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5); glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5); glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, 0.5); glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    // Top
    glNormal3f(0.0, 1.0, 0.0); glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5); glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, 0.5); glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    // Bottom
    glNormal3f(0.0, -1.0, 0.0); glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5); glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, -0.5); glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5); glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glPopMatrix();
}

void drawPig(const Mob &m) {
    glPushMatrix();
    glScalef(0.4f, 0.4f, 0.4f);

    glColor3f(1.0f, 1.0f, 1.0f);

    // 1. Body
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    drawTexturedBox(0.9f, 0.9f, 1.3f, pigBodyTexture);
    glPopMatrix();

    // 2. Head 
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.8f);
    drawHeadWithFace(0.7f, pigFaceTexture, pigBodyTexture);
    glPopMatrix();

    // 3. Legs
    float legAngle = sin(m.walkTimer) * 20.0f;

    glPushMatrix(); glTranslatef(-0.3f, 0.3f, 0.5f); glRotatef(legAngle, 1, 0, 0);
    drawTexturedBox(0.25f, 0.6f, 0.25f, pigBodyTexture); glPopMatrix();

    glPushMatrix(); glTranslatef(0.3f, 0.3f, 0.5f); glRotatef(-legAngle, 1, 0, 0);
    drawTexturedBox(0.25f, 0.6f, 0.25f, pigBodyTexture); glPopMatrix();

    glPushMatrix(); glTranslatef(-0.3f, 0.3f, -0.5f); glRotatef(-legAngle, 1, 0, 0);
    drawTexturedBox(0.25f, 0.6f, 0.25f, pigBodyTexture); glPopMatrix();

    glPushMatrix(); glTranslatef(0.3f, 0.3f, -0.5f); glRotatef(legAngle, 1, 0, 0);
    drawTexturedBox(0.25f, 0.6f, 0.25f, pigBodyTexture); glPopMatrix();

    glPopMatrix();
}

void drawTurtle(const Mob& m) {
    glPushMatrix();
    glScalef(0.4f, 0.4f, 0.4f);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    drawTexturedBox(0.8f, 0.4f, 1.0f, turtleShellTexture);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.6f);
    drawHeadWithFace(0.4f, turtleFaceTexture, turtleShellTexture);
    glPopMatrix();

    glPushMatrix(); glTranslatef(-0.4f, 0.1f, 0.4f);
    drawTexturedBox(0.2f, 0.2f, 0.2f, turtleSkinTexture); glPopMatrix();

    glPushMatrix(); glTranslatef(0.4f, 0.1f, 0.4f);
    drawTexturedBox(0.2f, 0.2f, 0.2f, turtleSkinTexture); glPopMatrix();

    glPushMatrix(); glTranslatef(-0.4f, 0.1f, -0.4f);
    drawTexturedBox(0.2f, 0.2f, 0.2f, turtleSkinTexture); glPopMatrix();

    glPushMatrix(); glTranslatef(0.4f, 0.1f, -0.4f);
    drawTexturedBox(0.2f, 0.2f, 0.2f, turtleSkinTexture); glPopMatrix();

    glPopMatrix();
}

void drawMobs() {
    for (const auto& m : mobs) {
        glPushMatrix();

        glTranslatef(m.x, m.y - 0.5f, m.z);

        glRotatef(m.rotationY, 0.0f, 1.0f, 0.0f);

        if (m.type == 0) {
            drawPig(m);
        }
        else if (m.type == 1) {
            drawTurtle(m);
        }

        glPopMatrix();
    }
}