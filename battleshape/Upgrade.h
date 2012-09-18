/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Upgrade class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Upgrade class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Particle.h"
#include "Drone.h"
#include "Torus.h"
#include "Text.h"
#ifndef Upgrade_H
#define Upgrade_H


class Upgrade {
public:
    /*
    -------------------- Constructor for the Upgrade class --------------------
    */

    Upgrade();

    /*
    -------------------- Destructor for the Upgrade class --------------------
    */
    ~Upgrade();

    /*
    -------------------- Accessors for the Upgrade class --------------------
    */
    Vector position;
    Vector movement;
    int type;
    int size;
    float currentRotation;
    GLfloat speed;
    bool isActive;
    bool isShrapnel;
    Particle shrapnel[15]; // used for a pretty pick-up graphic animation
    float red,green,blue; // different colours for different upgrade types?
    Particle2 underglow;
    Torus signal;
    Explosion explosion;
    Text message;

    /*
    -------------------- Modifiers for the Upgrade class --------------------
    */
    int initialize(int t);
    void draw(const GLuint& sparkTexture, float timer, float lastT, int shipType ); // draws the Upgrade
    int updatePosition(float timer, GLfloat playerX, GLfloat playerY, GLfloat playerZ);
    void collect(); // what happens when its collected?
};
#endif
