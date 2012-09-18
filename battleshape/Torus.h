/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Torus class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Torus class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#ifndef Torus_H
#define Torus_H

class Torus {
public:
    /*
    -------------------- Constructor for the Torus class --------------------
    */
    Torus();

    /*
    -------------------- Destructor for the Torus class --------------------
    */
    ~Torus();


    /*
    -------------------- Modifiers for the Torus class --------------------
    */
    
     void set(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat width1, GLfloat speed1, GLfloat in1);
     void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
     void setWake(GLfloat theta1, bool leftSide1);
     void detail(int x);

     /*
     -------------------- Methods for the Torus class --------------------
     */
     void draw(const float t);

    GLfloat width;
    bool expanding;
    bool isActive;
    bool isWake;
    int detailLevel;
    float expander;
    float theta;
    bool leftSide;
    
    GLfloat x;
    GLfloat y;
    GLfloat z;

private:
    /*
    -------------------- Variables for the Torus class --------------------
    */

    GLfloat speed;
    GLfloat in;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;



};
#endif
