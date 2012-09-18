/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the MouseHandler class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the MouseHandler class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#ifndef MouseHandler_H
#define MouseHandler_H


class MouseHandler {
public:
    /*
    -------------------- Constructor for the MouseHandler class --------------------
    */
    MouseHandler();

    /*
    -------------------- Destructor for the MouseHandler class --------------------
    */
    ~MouseHandler();

    /*
    -------------------- Accessors for the MouseHandler class --------------------
    */
    const double getMouseGridX() const;
    const double getMouseGridY() const;
    const double getMouseX() const;
    const double getMouseY() const;
    /*
    -------------------- Modifiers for the MouseHandler class --------------------
    */
    void setMouseGridX(double newMouseGridX);
    void setMouseGridY(double newMouseGridY);
    void setMouseX(double newMouseX);
    void setMouseY(double newMouseY);
    /*
    -------------------- Methods for the MouseHandler class --------------------
    */
    void drawMouse(float t);
    void updateMouse(GLfloat cameraPositionX, GLfloat cameraPositionY, GLfloat cameraPositionZ, GLfloat playerPositionX, GLfloat playerPositionY, GLint windowHeight, GLint windowWidth, GLfloat viewingAngle);

private:
    /*
    -------------------- Variables for the MouseHandler class --------------------
    */

    double mouseGridX;
    double mouseGridY;
    double mouseX;
    double mouseY;

};


#endif
