/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Nuke class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Nuke class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Particle.h"
#include "Explosion.h"
#include "Drone.h"
#include "FragMine.h"
#include "FragBoss.h"
#include "Factory.h"
#include "Propulsion.h"
#include "SoundManager.h"
#include "Sounds.h"

#ifndef Nuke_H
#define Nuke_H


class Nuke {
public:
    /*
    -------------------- Constructor for the Nuke class --------------------
    */

    Nuke();

    /*
    -------------------- Destructor for the Nuke class --------------------
    */
    ~Nuke();

    /*
    -------------------- Accessors for the Nuke class --------------------
    */
    Vector position;
    Vector movement;
    Vector direction;
    float acceleration;
    GLfloat range;
    GLfloat speed;
    GLfloat damage;
    bool isActive;
    bool isShrap;
    Explosion explosion;
    Explosion explosion2;
    Explosion explosion3;
    Particle trail[100];
    Propulsion propulsion;
    GLfloat explosionRadius;
    GLfloat pushRadius;
    GLfloat pushStrength;
    Torus torus;
    float currentRotation;

    /*
    -------------------- Modifiers for the Nuke class --------------------
    */
    void setNuke(GLfloat posx, GLfloat posy, GLfloat movx, GLfloat movy, GLfloat mov2x, GLfloat mov2y, GLfloat size);
    int updateNuke(float t, float explosionTimer, Drone enemies[], FragMine mines[], Factory factories[],FragBoss fragBosses[],int numberOfEnemies, int numberOfMines, int numberOfFactories, int numberOfFragBosses);
    int detonate(Drone enemies[], int numberOfEnemies, FragMine mines[], int numberOfMines, Factory factories[], int numberOfFactories, FragBoss fragBosses[], int numberOfFragBosses);
    bool hitSides();
    bool hitEnemy(Drone enemies[], int numberOfEnemies);
    bool hitMine(FragMine mines[], int numberOfMines);
    bool hitFactory(Factory mines[], int numberOfMines);
    bool hitFragBoss(FragBoss fragBosses[], int numberOfFragBosses);
    void drawNuke( float t );
    void drawPropulsion( float t );
    
};
#endif
