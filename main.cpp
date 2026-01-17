#include "Shared.h"
#include "Textures.h"
#include "Cubes.h"
#include "Character.h"
#include "World.h"
#include "Mobs.h"
#include "HUD.h"
#include <cmath> 

// --- Global Variables ---
int windowWidth = 800;
int windowHeight = 600;

float characterX = 0.0f;
float characterY = 0.0f;
float characterZ = 0.0f;
const float MOVEMENT_SPEED = 0.15f;

float verticalVelocity = 0.0f;
bool isGrounded = true;
const float GRAVITY = -0.015f;
const float JUMP_STRENGTH = 0.25f;

float animationAngle = 0.0f;
float animationSpeed = 0.2f;
bool isCharacterMoving = false;

bool isFirstPersonView = false;
const float TPV_DISTANCE = 5.0f;
const float TPV_HEIGHT = 2.0f;

const float CLOUD_SPEED = 0.005f;

float viewAngleX = 0.0f;
float viewAngleY = 0.0f;

// Camera internals
float cameraEyeX, cameraEyeY, cameraEyeZ;

bool keyState[256];
float dayTime = 0.0f;     
const float TIME_SPEED = 0.005f;


bool isSwinging = false;
float swordSwingAngle = 0.0f;


bool isFrontView = false;
float currentBodyRotation = 0.0f;

enum GameState { MENU, PLAYING };
GameState currentState = MENU; 

int btnX, btnY, btnWidth, btnHeight;

// --- Helper Functions ---
float toRad(float deg) {
    return deg * M_PI / 180.0f;
}

void mouseMove(int x, int y) {

    if (currentState == MENU) return;

    if (x == windowWidth / 2 && y == windowHeight / 2) return;

    int deltaX = x - (windowWidth / 2);
    int deltaY = y - (windowHeight / 2);
    float mouseSensitivity = 0.15f;

    viewAngleY += deltaX * mouseSensitivity;
    viewAngleX += deltaY * mouseSensitivity;


    if (viewAngleX > 89.0f) viewAngleX = 89.0f;
    if (viewAngleX < -89.0f) viewAngleX = -89.0f;

    if (viewAngleY > 360.0f) viewAngleY -= 360.0f;
    if (viewAngleY < 0.0f) viewAngleY += 360.0f;

    glutWarpPointer(windowWidth / 2, windowHeight / 2);
    glutPostRedisplay();
}

bool isPositionBlocked(float x, float z, float feetY) {
 
    int gridX = (int)floor(x + TERRAIN_SIZE / 2.0f);
    int gridZ = (int)floor(z + TERRAIN_SIZE / 2.0f);

    if (gridX < 0 || gridX >= TERRAIN_SIZE || gridZ < 0 || gridZ >= TERRAIN_SIZE) {
        return true;
    }


    int groundHeight = terrain[gridX][gridZ];
    int treeH = treeHeight[gridX][gridZ];

    if (groundHeight > feetY + 1.1f) {
        return true;
    }

    if (treeH > 0) {
        // block movement if there's a tree at eye level
        if (feetY < groundHeight + treeH) {
            return true;
        }
    }

    return false;
}

void drawSword() {
    glPushMatrix();

    glRotatef(-swordSwingAngle, 1.0f, 0.0f, 0.0f);

    // Tilt the sword slightly forward normally so it looks natural
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f); 
    glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);

    //HANDLE 
    glColor3f(0.4f, 0.2f, 0.0f);
    glPushMatrix();
    glScalef(0.05f, 0.05f, 0.2f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // CROSSGUARD
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.15f);
    glScalef(0.15f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //BLADE
    glColor3f(0.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.55f);
    glScalef(0.08f, 0.02f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Reset Color
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void updateMovement() {
    bool tryingToMove = false;
    float offsetAngle = 0.0f; 

    if (keyState['w'] || keyState['W']) {
        if (keyState['a'] || keyState['A']) offsetAngle = 45.0f;       // Forward + Left
        else if (keyState['d'] || keyState['D']) offsetAngle = -45.0f; // Forward + Right
        else offsetAngle = 0.0f;                                       // Just Forward
        tryingToMove = true;
    }
    else if (keyState['s'] || keyState['S']) {
        if (keyState['a'] || keyState['A']) offsetAngle = 135.0f;      // Backward + Left
        else if (keyState['d'] || keyState['D']) offsetAngle = -135.0f;// Backward + Right
        else offsetAngle = 180.0f;                                     // Just Backward
        tryingToMove = true;
    }
    else if (keyState['a'] || keyState['A']) {
        offsetAngle = 90.0f; // Left
        tryingToMove = true;
    }
    else if (keyState['d'] || keyState['D']) {
        offsetAngle = -90.0f; // Right
        tryingToMove = true;
    }

    // Jump
    if (keyState[' '] && isGrounded) {
        verticalVelocity = JUMP_STRENGTH;
        isGrounded = false;
        keyState[' '] = false;
    }

    // Movement
    if (tryingToMove) {
        // FINAL angle the character should face
        float targetAngle = viewAngleY + offsetAngle;

        currentBodyRotation = targetAngle;

        // Convert to Radians for math
        float rad = toRad(targetAngle);

        // Calculate X and Z movement based on this direction
        float dx = sin(rad) * MOVEMENT_SPEED;
        float dz = -cos(rad) * MOVEMENT_SPEED; 

        float nextX = characterX + dx;
        float nextZ = characterZ + dz;

        // Collision Check
        if (!isPositionBlocked(nextX, nextZ, characterY)) {
            characterX = nextX;
            characterZ = nextZ;
            isCharacterMoving = true;
        }
        else {
            isCharacterMoving = false;
        }
    }
    else {
        isCharacterMoving = false;
    }
}

void drawWireframeBox(float gridX, float gridY, float gridZ) {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.0f, 0.0f); // Black Selection Line
    glLineWidth(2.0f);

    glPushMatrix();
    // Convert them to world coordinates
    float worldX = gridX - TERRAIN_SIZE / 2.0f;
    float worldZ = gridZ - TERRAIN_SIZE / 2.0f;

    glTranslatef(worldX, gridY + 0.5f, worldZ);

    glScalef(1.01f, 1.01f, 1.01f);

    glutWireCube(1.0f);
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f); // Reset color
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        // Cast ray to find what we are looking at
        if (!isSwinging) {
            isSwinging = true;
            swordSwingAngle = 0.0f;
        }

        if (currentState == MENU) {
            int glY = windowHeight - y;

            // Check if click is inside the button rectangle
            if (x >= btnX && x <= btnX + btnWidth &&
                glY >= btnY && glY <= btnY + btnHeight) {

                currentState = PLAYING;

                // Hide cursor and warp it to center for gameplay
                glutSetCursor(GLUT_CURSOR_NONE);
                glutWarpPointer(windowWidth / 2, windowHeight / 2);
            }
        }

        else if (currentState == PLAYING) {
        
            RaycastResult res = castRay(cameraEyeX, cameraEyeY, cameraEyeZ, viewAngleX, viewAngleY);

            if (res.hit) {
                if (button == GLUT_LEFT_BUTTON) {
                    // If it's a tree, cut it
                    if (isTreeAt(res.x, res.y, res.z)) {
                        treeHeight[res.x][res.z] = 0;
                    }
                    else if (terrain[res.x][res.z] > 0) {
                        terrain[res.x][res.z]--;
                        if (treeHeight[res.x][res.z] > 0) treeHeight[res.x][res.z] = 0;
                    }
                }
                else if (button == GLUT_RIGHT_BUTTON) {
                    // Safety: Don't build higher than the sky (e.g., 20 blocks)
                    if (terrain[res.x][res.z] < 20) {

                        terrain[res.x][res.z]++;

                        worldBlockType[res.x][res.z] = selectedBlockType;
                    }
                }

                glutPostRedisplay();
            }
        }

        
    }
}

void drawString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawCenteredString(float y, void* font, const char* string) {
    int stringWidthPixels = glutBitmapLength(font, (const unsigned char*)string);

    float x = (windowWidth - stringWidthPixels) / 2.0f;

    drawString(x, y, font, string);
}



void drawMenu() {
    // 1. Switch to 2D Mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, menuBackgroundTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glTexCoord2f(1, 0); glVertex2f(windowWidth, 0);
    glTexCoord2f(1, 1); glVertex2f(windowWidth, windowHeight);
    glTexCoord2f(0, 1); glVertex2f(0, windowHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D); 


    float centerX = windowWidth / 2.0f;
    float centerY = windowHeight / 2.0f;

    
    btnWidth = 220;
    btnHeight = 60;
    btnX = centerX - (btnWidth / 2.0f);
    btnY = centerY - (btnHeight / 2.0f);

    glColor3f(0.2f, 0.7f, 0.2f);
    glRectf(btnX, btnY, btnX + btnWidth, btnY + btnHeight);

    glColor3f(0.3f, 0.9f, 0.3f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(btnX, btnY);
    glVertex2f(btnX + btnWidth, btnY);
    glVertex2f(btnX + btnWidth, btnY + btnHeight);
    glVertex2f(btnX, btnY + btnHeight);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    float textY = btnY + (btnHeight / 2.0f) - 8.0f;
    drawCenteredString(textY, GLUT_BITMAP_HELVETICA_18, "START GAME");

    glColor3f(0.9f, 0.9f, 0.9f); // Light grey
    drawCenteredString(centerY - 80, GLUT_BITMAP_HELVETICA_12, "Use W,A,S,D and Mouse. Left Click to start.");

    // Restore 3D State
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void updateLighting() {
    float brightness = sin(dayTime);

    if (brightness < 0.2f) brightness = 0.2f;

    GLfloat skyRed = 0.6f * brightness;
    GLfloat skyGreen = 0.8f * brightness;
    GLfloat skyBlue = 1.0f * brightness;

    if (brightness > 0.2f && brightness < 0.5f) {
        skyRed = 0.8f; skyGreen = 0.5f; skyBlue = 0.2f;
    }

    glClearColor(skyRed, skyGreen, skyBlue, 1.0f);

    GLfloat fogColor[] = { skyRed, skyGreen, skyBlue, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);

    GLfloat lightPos[] = { 0.0f, sin(dayTime), cos(dayTime), 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat lightColor[] = { brightness, brightness, brightness, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
}

void init(void) {
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // --- FOG ---
    glEnable(GL_FOG);
    GLfloat fogColor[] = { 0.6f, 0.8f, 1.0f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 20.0f);
    glFogf(GL_FOG_END, 60.0f);

    GLfloat light_position[] = { 0.5f, 1.0f, 0.5f, 0.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < 256; i++) keyState[i] = false;

    loadAllTextures();
    generateTerrain();
    generateClouds();
    spawnMobs();

    characterY = getTerrainHeight(characterX, characterZ);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (currentState == MENU) {
        drawMenu();
        glutSwapBuffers();
        return;
    }

    if (characterY < -20.0f) {
        characterX = 0.0f; characterZ = 0.0f;
        characterY = getTerrainHeight(0.0f, 0.0f);
        verticalVelocity = 0.0f; isGrounded = true;
    }

    if (isFirstPersonView) {
        float headBob = (isGrounded && isCharacterMoving) ? sin(animationAngle * 2.0f) * 0.05f : 0.0f;
        cameraEyeX = characterX;
        cameraEyeY = characterY + 1.25f + headBob; 
        cameraEyeZ = characterZ;

        glTranslatef(0.3f, -0.3f, -0.5f);

        glDisable(GL_TEXTURE_2D); 
        drawSword();
        glEnable(GL_TEXTURE_2D);

        gluLookAt(cameraEyeX, cameraEyeY, cameraEyeZ,
            cameraEyeX + sin(toRad(viewAngleY)),
            cameraEyeY + sin(toRad(viewAngleX)),
            cameraEyeZ - cos(toRad(viewAngleY)),
            0.0, 1.0, 0.0);
    }else {

        glPushMatrix();

        glTranslatef(0.35f, 0.75f, 0.20f);

        glScalef(0.6f, 0.6f, 0.6f);

        glDisable(GL_TEXTURE_2D);

        drawSword();

        glEnable(GL_TEXTURE_2D);

        glPopMatrix();

        float yawRad = toRad(viewAngleY);  
        float pitchRad = toRad(viewAngleX);

        float horizontalDist = TPV_DISTANCE * cos(pitchRad); // Closer when looking down
        float verticalDist = TPV_DISTANCE * sin(pitchRad); // Higher when looking down

        // 3. Calculate Position
        if (!isFrontView) {
            cameraEyeX = characterX - sin(yawRad) * horizontalDist;
            cameraEyeZ = characterZ + cos(yawRad) * horizontalDist;
        }
        else {
           
            cameraEyeX = characterX + sin(yawRad) * horizontalDist;
            cameraEyeZ = characterZ - cos(yawRad) * horizontalDist;
        }

        // Pivot around the character's head height 
        cameraEyeY = (characterY + 1.5f) + verticalDist;

        // Always look exactly at the player's head/chest area
        gluLookAt(cameraEyeX, cameraEyeY, cameraEyeZ,
            characterX, characterY + 1.5f, characterZ,
            0.0, 1.0, 0.0);
    }

    updateLighting();

    // Draw Sky elements
    drawClouds();
    drawSun(dayTime);
    drawClouds();

    // Draw World
    glPushMatrix();
    drawTerrain();
    glPopMatrix();

    // Draw Selection Box
    RaycastResult ray = castRay(cameraEyeX, cameraEyeY, cameraEyeZ, viewAngleX, viewAngleY);
    if (ray.hit) {
        drawWireframeBox((float)ray.x, (float)ray.y, (float)ray.z);
    }

    drawMobs();

    // --- CHARACTER DRAWING ---
    if (!isFirstPersonView) {
        glPushMatrix();
        glTranslatef(characterX, characterY + 0.2f, characterZ);

        
        glRotatef(currentBodyRotation + 180.0f, 0.0, 1.0, 0.0);

        drawCharacter(0.0f);

        glPopMatrix();
    }


    // 1. Crosshair
    drawText(windowWidth / 2 - 5, windowHeight / 2, "+");

    // 2. Inventory Bar
    drawHUD();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    drawString(10, windowHeight - 20, GLUT_BITMAP_HELVETICA_18, "Controls:");
    drawString(10, windowHeight - 40, GLUT_BITMAP_HELVETICA_12, "W,A,S,D - Move");
    drawString(10, windowHeight - 55, GLUT_BITMAP_HELVETICA_12, "Space - Jump");
    drawString(10, windowHeight - 70, GLUT_BITMAP_HELVETICA_12, "Mouse - Look");
    drawString(10, windowHeight - 85, GLUT_BITMAP_HELVETICA_12, "Left Click - Break");
    drawString(10, windowHeight - 100, GLUT_BITMAP_HELVETICA_12, "Right Click - Build");
    drawString(10, windowHeight - 115, GLUT_BITMAP_HELVETICA_12, "1-5 - Select Block");
    drawString(10, windowHeight - 130, GLUT_BITMAP_HELVETICA_12, "C - Toggle Camera");

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w; windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 0.1, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
    keyState[key] = true; // Mark key as pressed
    if (key == 'c' || key == 'C') isFirstPersonView = !isFirstPersonView;
    if (key == 'v' || key == 'V') isFrontView = !isFrontView; // Toggle front-view camera
    if (key == 27) exit(0);
    if (key == 'r' || key == 'R') {
        characterX = 0; characterZ = 0;
        characterY = getTerrainHeight(0, 0);
        generateTerrain();
    }

    // Inventory Selection
    if (key == '1') selectedBlockType = 0; // Grass
    if (key == '2') selectedBlockType = 1; // Dirt
    if (key == '3') selectedBlockType = 2; // Stone
    if (key == '4') selectedBlockType = 3; // Brick (Pig Texture)
    if (key == '5') selectedBlockType = 4; // Wood

}

void keyboardUp(unsigned char key, int x, int y) {
    keyState[key] = false; // Mark key as released
}

void animate(void) {
    updateMovement();

    //height of the ground directly below us
    float groundHeight = getTerrainHeight(characterX, characterZ);

    if (isSwinging) {
        swordSwingAngle += 15.0f;
        if (swordSwingAngle > 80.0f) { 
            swordSwingAngle = 0.0f;  
            isSwinging = false;   
        }
    }

    if (characterY > groundHeight + 0.1f) {
        isGrounded = false;
    }

    // 3. Apply Gravity if falling
    if (!isGrounded) {
        characterY += verticalVelocity;
        verticalVelocity += GRAVITY;
    }

    // 4. Landing Logic
    if (characterY <= groundHeight) {
        characterY = groundHeight;
        verticalVelocity = 0.0f;
        isGrounded = true;
    }

    if (isCharacterMoving) animationAngle += animationSpeed;
    else animationAngle = 0.0f;

    for (auto& cloud : clouds) {
        cloud.individualCloudMovementX += CLOUD_SPEED;
    }
    updateMobs();

    dayTime += TIME_SPEED;
    if (dayTime > 6.283f) dayTime -= 6.283f;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Minecraft Clone");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(animate);
    glutPassiveMotionFunc(mouseMove);
    //glutSetCursor(GLUT_CURSOR_NONE);
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    glutMouseFunc(mouseClick);

    glutMainLoop();
    return 0;
}