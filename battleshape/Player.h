/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Player class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Player class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>
#include "FragMine.h"
#include "FragBoss.h"
#include "Vector.h"
#include "Shot.h"
#include "Nuke.h"
#include "Drone.h"
#include "Particle.h"
#include "Propulsion.h"
#include "Torus.h"
#include "SoundManager.h"
#include "Sounds.h"

#ifndef Player_H
#define Player_H

class Player{
public:
     /*
     -------------------- Constructor for the Player class --------------------
     */
	Player();

     /*
     -------------------- Destructor for the Player class --------------------
     */
	~Player();

	/*
     -------------------- Accessors for the Player class --------------------
     */
     Shot shots[100];
     Nuke nuke[100];
     GLint shotCounter;
     GLint nukeCounter;
     Vector position;
     Vector movement;
     Vector direction;
     Vector currentRotation;  // This is only applicable to ship type 4, the Torus/Sphere one, although we may retrofit it for another ship later
     GLfloat acceleration;
     GLfloat maxVelocity;
     GLfloat reloadTime, reloadTimer;
     bool shootingNow;
     bool shootingSpec;
     bool cameraShake;
     float shipTheta;
     bool shipLeftSide;
     float primaryColour[3];
     float secondaryColour[3];
     GLfloat dampening;
     float turnSpeed;
     

     /*
     -------------------- Methods for the Player class --------------------
     */
     void shoot(GLint x, GLint y); // shoots a projectile from the ship along a vector toward a mouse location
     GLfloat getAcceleration();
     void setAcceleration(GLfloat a);
	 void drawPlayer(float t, GLint x, GLint y); //must draw the player
	 void drawShip1();
	 void drawShip2();
	 void drawShip3();
	 void drawShip4(float t);
	 void drawShots(float t);
	 int moveShots(float t, float explosionTimer, Drone enemies[], FragMine parents[], Factory factories[], FragBoss fragBosses[], int numberOfEnemies, int numberOfParents, int numberOfFactories, int numberOfFragBosses);

	 void shootNuke( GLint x, GLint y );
	 int moveNuke(float t, float explosionTimer, Drone enemies[], FragMine parents[], Factory factories[], FragBoss fragBosses[], int numberOfEnemies, int numberOfParents, int numberOfFactories, int numberOfFragBosses);
	 void drawNuke(float t);


     void movePlayer(float t); // move the player location based on the movement vector
     void accelerating(bool a); // set the player to be accelerating
     void acceleratingBack(bool a); // set the player to be accelerating backwards
     void turningLeft(bool a); // set the player to be turning left
     void turningRight(bool a); // set the player to be turning right
   	void shooting(bool a); // set the player to be shooting
   	void setROF(float x); // set the rate of fire of the shots
   	void getUpgrade(int type);
   	void setColour(int p, int s);
     bool ram(void); // updates the shields, returns true if there are no shields, then gameHandler figures out where to go
     void drawPropulsion(const GLuint& texture, float t, float t2, bool playerDeath);
     void gameOver(); // resets all variables to original state
     int nukes;
     int specialShots;
     float currentBounceRotation;
     int shipType;
     int shields;
     Propulsion propulsion;
     int upgradeLevel;
     

private:
     bool boolTurningLeft;
     bool boolTurningRight;
     bool boolAccelerating;
     bool boolAcceleratingBack;
     float shieldTimer;
     float maxShields;

     bool backShot;
     float rof;

     float sphereRoll;

     void acceleratePlayer(float t); // change the player movement vector based upon the direction
     void acceleratePlayerBack(float t); // change the player movement vector based upon the direction
     void rotateLeft(float t);
     void rotateRight(float t);
     void dampenMovement(float t);

     /*
     -------------------- Variables for the Player class --------------------
     */

     Particle trail[100];
};
#endif
