/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the FragBoss class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the FragBoss class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Vector.h"
#include "Drone.h"
#include "Factory.h"
#include "Torus.h"
#include "Healthbar.h"
#include "Explosion.h"

#define round(x) (x-floor(x))>=0.5 ? ceil(x):floor(x)
//#define round(x) if(x-floor(x)>=0.5){ceil(x)}else{floor(x)}

#ifndef FragBoss_H
#define FragBoss_H


class FragBoss{
public:
     /*
     -------------------- Constructor for the FragBoss class --------------------
     */
	FragBoss(GLfloat newHealth, GLint newPointValue);
     FragBoss();
     /*
     -------------------- Destructor for the FragBoss class --------------------
     */
	~FragBoss();
     
     /*
     -------------------- Accessors for the FragBoss class --------------------
     */
     const GLfloat getHealth() const;      //must return the health of the FragBoss
     const GLfloat getSize() const;        //must return the size of the FragBoss
     const GLint getType() const;          //must return the type of the FragBoss
    GLint getPointValue();    //must return the point value of the FragBoss
     void draw(const GLuint& sparkTexture, float timer, float explosionTimer ); // draws the FragBoss in question
     /*
     -------------------- Modifiers for the FragBoss class --------------------
     */
     void reverseSpin(); // reverses the spin direction for the Boss
     void setHealth(GLfloat newHealth); //must set the health of the FragBoss
     void damageShields(GLfloat damage); //must set the health of the FragBoss
     void regenShields(GLfloat damage); //must set the health of the FragBoss
     void setPointValue(GLint newPointValue); //must set the point value of the FragBoss

     /*
     -------------------- Methods for the FragBoss class --------------------
     */
     void initialize(int newType); // initializes all the values to the FragBoss type in question
     void initialize(int newType, float x, float y); // initializes all the values to the FragBoss type in question, at the specified location
     bool updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ, bool playerDeath);
     bool hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat=0);
     GLboolean takeDamage(GLfloat damage);
     GLboolean damageChild(int child,GLfloat damage);
     void explode( float explosionTimer );
     void fire(GLfloat playerX, GLfloat playerY, bool playerDeath);
     void updateStatus();

     /*
     -------------------- Variables for the FragBoss class --------------------
     */
     Drone children[400];
     Factory factories[8];
     Particle2 portal;
     bool spinReversed;
     bool topside;
     bool wasHit;
     bool hasFactories;
     
     int numberOfDrones;
     int currentDrone;
     int numberOfFactories;
     int type;
     int mode;
    Explosion explosion;
    Explosion explosion2;
    Explosion explosion3;
    bool wasDestroyed;
    bool didExplode;
    bool lostFactories;
    Torus torus;
    GLfloat rollRotation;
     GLfloat size;
     GLfloat speed;
     GLfloat reloadTimer;
     GLfloat maxReloadTimer;     
     GLfloat shieldR;
     GLfloat shieldG;
     GLfloat shieldB;
     GLfloat shields;
     GLfloat maxShields;
     GLfloat transTimer;
     GLfloat spinSpeed;
     GLfloat spawnTimer;
     GLfloat maxSpawnTimer;
     GLfloat health; // store the health of the FragBoss
     GLfloat maxHealth; // store the maximum health of the FragBoss
     GLint pointValue; // store the point value of the FragBoss
     Particle2 spawnDebris[150]; // Slightly re-purposing the travel vector in Particle2 to store it's location in a circle around the drone
     float spawnDebrisLifeMax;
     GLboolean isAlive, isShrapnel, isComplete;
//     Explosion explosion;
     GLfloat orbitRadius;
     GLfloat orbitRotation;
     GLfloat currentRotation; // this is used for the rotation of the square in tracker, and for the rotation of the cube in
                              // the roller, so it's also a timer so to speak
     GLfloat maxRotTime; // this is the timer value for the roller, so every time it starts rolling, this is what it's set to
     GLfloat hangTime;   // this variable controls how long the roller FragBosss hold their location before continuing to roll
     GLfloat red,green,blue,opacity;
     Healthbar healthbar;
     Vector position;
     Vector direction; //direction currently facing, ie. player.
     Vector movement;
     Vector appliedForce;
     

};
#endif

