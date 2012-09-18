/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Factory class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Factory class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Vector.h"
#include "Drone.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "Sounds.h"
#define round(x) (x-floor(x))>=0.5 ? ceil(x):floor(x)
//#define round(x) if(x-floor(x)>=0.5){ceil(x)}else{floor(x)}

#ifndef Factory_H
#define Factory_H


class Factory{
public:
     /*
     -------------------- Constructor for the Factory class --------------------
     */
	Factory(GLfloat newHealth, GLint newPointValue);
     Factory();
     /*
     -------------------- Destructor for the Factory class --------------------
     */
	~Factory();
     
     /*
     -------------------- Accessors for the Factory class --------------------
     */
     const GLfloat getHealth() const;      //must return the health of the Factory
     const GLfloat getSize() const;        //must return the size of the Factory
     const GLint getType() const;          //must return the type of the Factory
     GLint getPointValue();    //must return the point value of the Factory
     void draw(const GLuint& sparkTexture, float timer, float explosionTimer ); // draws the Factory in question
     void drawShots(const GLuint& sparkTexture, float timer, float explosionTimer ); // draws the Factory's shots
     /*
     -------------------- Modifiers for the Factory class --------------------
     */
     void setHealth(GLfloat newHealth); //must set the health of the Factory
     void setPointValue(GLint newPointValue); //must set the point value of the Factory

     /*
     -------------------- Methods for the Factory class --------------------
     */
     void fire(); // fires a Drone
     void initialize(int newType); // initializes all the values to the Factory type in question
     void initialize(int newType, float x, float y); // initializes all the values to the Factory type in question, at the given location
     bool updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ, bool playerDeath);
     bool hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat = 0);
     GLboolean takeDamage(GLfloat damage);
     GLboolean damageChild(int child,GLfloat damage);
     void explode( float explosionTimer );
     void updateStatus();

     /*
     -------------------- Variables for the Factory class --------------------
     */
     Particle2 portal;
     GLfloat spawnTimer;
     GLfloat maxSpawnTimer;
     Particle2 spawnDebris[30]; // Slightly re-purposing the travel vector in Particle2 to store it's location in a circle around the drone
     float spawnDebrisLifeMax;
     
     Drone children[20];
     int numberOfDrones;
     int type;
     int mode;
     GLfloat size;
     GLfloat speed;
     GLfloat spinSpeed;
     GLfloat reloadTimer, maxReloadTimer;
     GLfloat health; // store the health of the Factory
     GLfloat maxHealth; // store the health of the Factory
     GLint pointValue; // store the point value of the Factory
     GLboolean isAlive, isShrapnel, isComplete;
     Explosion explosion;
     GLfloat currentRotation; // this is used for the rotation of the square in tracker, and for the rotation of the cube in
                              // the roller, so it's also a timer so to speak
     GLfloat orbitRotation;
     GLfloat orbitDistance;
     GLfloat downAngle;
     GLfloat maxRotTime; // this is the timer value for the roller, so every time it starts rolling, this is what it's set to
     GLfloat hangTime;   // this variable controls how long the roller Factorys hold their location before continuing to roll
     GLfloat red,green,blue,opacity;
     
     Vector position;
     Vector direction; //could be used to track player? For type 0, used to store the vector between the boss and the factory
     Vector movement;
     

};
#endif

