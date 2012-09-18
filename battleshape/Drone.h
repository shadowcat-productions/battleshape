/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Drone class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Drone class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Vector.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "Sounds.h"

#ifndef Drone_H
#define Drone_H

#define round(x) (x-floor(x))>=0.5 ? ceil(x):floor(x)
//#define round(x) if(x-floor(x)>=0.5){ceil(x)}else{floor(x)}

class Drone{
public:
     /*
     -------------------- Constructor for the Drone class --------------------
     */
	Drone(GLfloat newHealth, GLint newPointValue);
     Drone();
     /*
     -------------------- Destructor for the Drone class --------------------
     */
	~Drone();

     /*
     -------------------- Accessors for the Drone class --------------------
     */
     const GLfloat getHealth() const;      //must return the health of the Drone
     const GLfloat getSize() const;        //must return the size of the Drone
     const GLint getType() const;          //must return the type of the Drone
     GLint getPointValue();    //must return the point value of the Drone
     void draw(const GLuint& sparkTexture, float timer, float explosionTimer ); // draws the Drone in question
     /*
     -------------------- Modifiers for the Drone class --------------------
     */
     void setHealth(GLfloat newHealth); //must set the health of the drone
     void setPointValue(GLint newPointValue); //must set the point value of the Drone

     /*
     -------------------- Methods for the Drone class --------------------
     */
     void initialize(int newType); // initializes all the values to the Drone type in question
     void initialize(int newType, float x, float y, float xDir, float yDir); // initializes all the values to the Drone type in question
     bool updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ);
     bool hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat = 0);

     GLboolean takeDamage(GLfloat damage);
     void explode( float explosionTimer );

     /*
     -------------------- Variables for the Drone class --------------------
     */
     int type;
     int mode;
     Particle2 portal, glow;
     GLfloat size;
     GLfloat spawnTimer;
     GLfloat maxSpawnTimer;
     GLfloat speed;
     GLfloat maxSpeed;
     GLfloat spinSpeed;
     GLfloat health; // store the health of the Drone
     GLint pointValue; // store the point value of the Drone
     GLboolean isAlive, isShrapnel;
     Particle2 spawnDebris[30]; // Slightly re-purposing the travel vector in Particle2 to store it's location in a circle around the drone
     float spawnDebrisLifeMax;
     Explosion explosion;
     GLfloat currentRotation; // this is used for the rotation of the square in tracker, and for the rotation of the cube in
                              // the roller, so it's also a timer so to speak
     GLfloat maxRotTime; // this is the timer value for the roller, so every time it starts rolling, this is what it's set to
     GLfloat hangTime;   // this variable controls how long the roller Drones hold their location before continuing to roll
     GLfloat red,green,blue,opacity;

     Vector position;
     Vector direction; //could be used to track player?
     Vector movement;
     Vector appliedForce;


};
#endif
