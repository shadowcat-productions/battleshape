/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the FragMine class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the FragMine class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Vector.h"
#include "Drone.h"
#include "Explosion.h"
#include "Torus.h"
#include "SoundManager.h"
#include "Sounds.h"

#define round(x) (x-floor(x))>=0.5 ? ceil(x):floor(x)
//#define round(x) if(x-floor(x)>=0.5){ceil(x)}else{floor(x)}

#ifndef FragMine_H
#define FragMine_H


class FragMine{
public:
     /*
     -------------------- Constructor for the FragMine class --------------------
     */
	FragMine(GLfloat newHealth, GLint newPointValue);
     FragMine();
     /*
     -------------------- Destructor for the FragMine class --------------------
     */
	~FragMine();

     /*
     -------------------- Accessors for the FragMine class --------------------
     */
     const GLfloat getHealth() const;      //must return the health of the FragMine
     const GLfloat getSize() const;        //must return the size of the FragMine
     const GLint getType() const;          //must return the type of the FragMine
     GLint getPointValue();    //must return the point value of the FragMine
     void draw(const GLuint& sparkTexture, float timer, float explosionTimer ); // draws the FragMine in question
     /*
     -------------------- Modifiers for the FragMine class --------------------
     */
     void reverseSpin(); // reverses the spin direction for the mine
     void setHealth(GLfloat newHealth); //must set the health of the FragMine
     void setPointValue(GLint newPointValue); //must set the point value of the FragMine

     /*
     -------------------- Methods for the FragMine class --------------------
     */
     void initialize(int newType); // initializes all the values to the FragMine type in question
     void initialize(int newType, float x, float y); // initializes all the values to the FragMine type in question, at the specified location
     void initialize(int newType, float x, float y, float xDir, float yDir); // initializes all the values to the FragMine type in question, at the specified location
     bool updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ);
     bool hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat = 0);
     GLboolean takeDamage(GLfloat damage);
     GLboolean damageChild(int child,GLfloat damage);
     void explode( float explosionTimer );
     void updateStatus();

     /*
     -------------------- Variables for the FragMine class --------------------
     */
     Drone children[8];
     Particle2 portal;
     bool spinReversed;
     int numberOfDrones;
     int type;
     int mode;
     GLfloat size;
     GLfloat speed;
     GLfloat spinSpeed;
     GLfloat spawnTimer;
     GLfloat maxSpawnTimer;
     GLfloat health; // store the health of the FragMine
     GLint pointValue; // store the point value of the FragMine
     Particle2 spawnDebris[30]; // Slightly re-purposing the travel vector in Particle2 to store it's location in a circle around the drone
     float spawnDebrisLifeMax;
     GLboolean isAlive, isShrapnel, isComplete;

    Explosion explosion;
    Explosion explosion2;
    Explosion explosion3;
    bool wasDestroyed;
    bool didExplode;
    Torus torus;

     GLfloat currentRotation; // this is used for the rotation of the square in tracker, and for the rotation of the cube in
                              // the roller, so it's also a timer so to speak
     GLfloat maxRotTime; // this is the timer value for the roller, so every time it starts rolling, this is what it's set to
     GLfloat hangTime;   // this variable controls how long the roller FragMines hold their location before continuing to roll
     GLfloat red,green,blue,opacity;

     Vector position;
     Vector direction; //could be used to track player?
     Vector movement;


};
#endif

