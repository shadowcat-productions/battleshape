/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Shot class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Shot class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Nuke.h"
#include "Explosion.h"
#include "Drone.h"
#include "FragMine.h"
#include "FragBoss.h"
#include "Factory.h"

#ifndef Shot_H
#define Shot_H


class Shot {
public:
    /*
    -------------------- Constructor for the Shot class --------------------
    */

    Shot();

    /*
    -------------------- Destructor for the Shot class --------------------
    */
    ~Shot();

    /*
    -------------------- Accessors for the Shot class --------------------
    */
    Vector position;
    Vector movement;
    GLfloat speed;
    float damage;
    bool isActive;
    bool isShrap;
    bool isPenetrating;
    bool isBounce;
    bool isStar;
    bool hasExploded;
    int bounceCount;
    int upgradeLevel;
    Explosion explosion;
    Torus ripple[5];
    int newestRipple;
    float currentExpansion;
    bool anyActive;
    
    Vector starPosition;
    float starTimer;


    /*
    -------------------- Modifiers for the Shot class --------------------
    */
    void setShot(GLfloat posx, GLfloat posy, GLfloat movx, GLfloat movy);
    int updateShot(float t, float explosionTimer, Drone enemies[], FragMine mines[], Factory factories[], FragBoss fragBosses[], int numberOfEnemies, int numberOfMines, int numberOfFactories, int numberOfFragBosses);
    void hitSides();
    int hitEnemy(Drone enemies[], int numberOfEnemies, bool isPenetrating);
    int hitMine(FragMine mines[], int numberOfMines, bool isPenetrating);
    int hitFactory(Factory mines[], int numberOfMines, bool isPenetrating);
    int hitFragBoss(FragBoss fragBosses[], int numberOfFragBosses, bool isPenetrating);
};
#endif
