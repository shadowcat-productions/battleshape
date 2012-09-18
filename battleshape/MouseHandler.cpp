/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Mouse.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the MouseHandler class --------------------
*/

#include "MouseHandler.h"

/*
 -------------------- Constructors for the MouseHandler class --------------------
*/
MouseHandler::MouseHandler() {
    //initialize MouseHandler variables to default settings
}

/*
 -------------------- Destructor for the MouseHandler class --------------------
*/
MouseHandler::~MouseHandler() {
}

/*
 -------------------- Accessors for the MouseHandler class --------------------
*/
const double MouseHandler::getMouseGridX() const {
    return mouseGridX;
}

const double MouseHandler::getMouseGridY() const {
    return mouseGridY;
}

const double MouseHandler::getMouseX() const {
    return mouseX;
}

const double MouseHandler::getMouseY() const {
    return mouseY;
}
/*
 -------------------- Modifiers for the MouseHandler class --------------------
*/
void MouseHandler::setMouseGridX(double newMouseGridX) {
    mouseGridX = newMouseGridX;
}

void MouseHandler::setMouseGridY(double newMouseGridY) {
    mouseGridY = newMouseGridY;
}

void MouseHandler::setMouseX(double newMouseX) {
    mouseX = newMouseX;
}

void MouseHandler::setMouseY(double newMouseY) {
    mouseY = newMouseY;
}
/*
 -------------------- Methods for the MouseHandler class --------------------
*/
void MouseHandler::drawMouse(float t) {
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(mouseGridX, mouseGridY, 1);
    glRotatef( t, 0.0, 0.0, 1.0 );
    glutSolidTorus( 0.2, 3, 3, 15);    
    glPopMatrix();
    
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(mouseGridX, mouseGridY, 1);
    glutSolidSphere( 0.5, 10, 10);    
    glPopMatrix();    
    
    glColor4f(1.0, 1.0, 1.0, 1.0);
    int i;
    for (i=0;i<4;i++)
    {
        glPushMatrix();
        glTranslatef(mouseGridX, mouseGridY, 1);
        glRotatef( t+90*i, 0.0, 0.0, 1.0 );
        glTranslatef(4, 0, 0);    
        glRotatef( -90, 0.0, 1.0, 0.0 );
        glutSolidCone( 0.75, 3, 5, 5);        
        glPopMatrix();
    }
}

void MouseHandler::updateMouse(GLfloat cameraPositionX, GLfloat cameraPositionY, GLfloat cameraPositionZ, GLfloat playerPositionX, GLfloat playerPositionY, GLint windowHeight, GLint windowWidth, GLfloat viewingAngle) {
    float xStart = cameraPositionX - playerPositionX;
    float yStart = cameraPositionY - playerPositionY;
    float zStart = cameraPositionZ - 1;
    float rotate1 = atan(xStart/zStart);
    float rotateX = ((((float)mouseX / windowWidth) * (((float)windowHeight /(float)windowWidth) * viewingAngle)) - (((float)windowHeight /(float)windowWidth) * viewingAngle / 2.0)) * 3.14159 / 180.0;
    float rotateY = (((float)mouseY / windowHeight) * viewingAngle - (viewingAngle / 2.0)) * 3.14159 / 180.0;
    float vectorX = cos(rotate1) * xStart - sin(rotate1) * zStart;
    float vectorZ = sin(rotate1) * xStart + cos(rotate1) * zStart;
    float rotate2 = atan( - yStart / vectorZ);
    float vectorY = cos(rotate2) * yStart + sin(rotate2) * vectorZ;
    vectorZ = cos(rotate2) * vectorZ - sin(rotate2) * yStart;
    xStart = vectorX;
    yStart = vectorY;
    zStart = vectorZ;


    vectorX = cos(rotateX) * xStart - sin(rotateX) * zStart;
    vectorZ = sin(rotateX) * xStart + cos(rotateX) * zStart;

    xStart = vectorX;
    yStart = vectorY;
    zStart = vectorZ;
    vectorY = cos(rotateY) * yStart + sin(rotateY) * zStart;
    vectorZ = cos(rotateY) * zStart - sin(rotateY) * yStart;

    xStart = vectorX;
    yStart = vectorY;
    zStart = vectorZ;

    vectorY = cos( - rotate2) * yStart + sin( - rotate2) * zStart;
    vectorZ = cos( - rotate2) * zStart - sin( - rotate2) * yStart;

    vectorX = cos( - rotate1) * xStart - sin( - rotate1) * zStart;
    vectorZ = sin( - rotate1) * xStart + cos( - rotate1) * zStart;

    float temp = (1.0 - (float)cameraPositionZ) / vectorZ;

    mouseGridX = cameraPositionX + temp * vectorX;
    mouseGridY = cameraPositionY + temp * vectorY;

    double Xdistance = mouseGridX - playerPositionX;
    double Ydistance = mouseGridY - playerPositionY;

    mouseGridX = mouseGridX + 0.38*Xdistance + 0.5 / abs((GLint)playerPositionX);
    mouseGridY = mouseGridY + 120 * abs(1 / ((GLint)playerPositionY + 2)) - 120 * abs(1 / ((GLint)playerPositionY - 152));
}
