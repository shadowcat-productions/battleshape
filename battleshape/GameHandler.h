/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the GameHandler class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the GameHandler class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Drone.h"
#include "FragMine.h"
#include "FragBoss.h"
#include "Factory.h"
#include "Upgrade.h"
#include "SoundManager.h"
#include "Sounds.h"

#ifndef GameHandler_H
#define GameHandler_H


class GameHandler{
public:
     /*
     -------------------- Constructor for the GameHandler class --------------------
     */
     GameHandler();
     /*
     -------------------- Destructor for the GameHandler class --------------------
     */
	~GameHandler();

     /*
     -------------------- Accessors for the GameHandler class --------------------
     */

     /*
     -------------------- Modifiers for the GameHandler class --------------------
     */
     void ReInitialize(void);
     /*
     -------------------- Methods for the GameHandler class --------------------
     */
     bool drawEnemies(const GLuint& sparkTexture, float timer, float explosionTimer, GLfloat playerX, GLfloat playerY, GLfloat playerZ); // returns true if an enemy hits the player
     int drawUpgrades(const GLuint& sparkTexture, float timer, float lastT, GLfloat playerX, GLfloat playerY, GLfloat playerZ, int shipType);
     void killPlayer(float explosionTimer, Vector position);
     bool newLifeSequence(float t,float explosionTimer);
     int updateScore();
     void newLevel ();
     void newPhase ();
     void checkPhase ();
     void clearEnemies ();
     void gameOver();
     /*
     -------------------- Variables for the GameHandler class --------------------
     */
     int numberOfDrones;
     int numberOfMines;
     int numberOfFactories;
     int numberOfFragBosses;
     int level;
     int nextLevel;
     long int score;
     int lives;
     int phase;
     float phaseCoolDown, phaseTimer;
     Drone drones[600];
     FragMine mines[140];
     FragBoss fragBosses[2];
     Factory factories[30];
     bool cameraShake;
     bool playerDeath;
     bool cheatActive;
     bool upgradeCollected;
     float newLifeTimer;
     float playerInvinceTimer;
     float maxInvince;
     Upgrade upgrade;
     bool gridFlashing;
     Drone test;
     Vector pushCenter;
     Vector playerDeathLoc;
     Vector spawnPath;
     float pushStrength;
     bool checkpoint;
     bool checkpointLevel;

    Explosion explosion1a;
    Explosion explosion2a;
    Explosion explosion3a;
    Explosion explosion1b;
    Explosion explosion2b;
    Explosion explosion3b;
    Explosion explosion1c;
    Explosion explosion2c;
    Explosion explosion3c;
    Torus torus;
    Torus torus2;
    Torus smallTorii[10];
    int numTorii;
    Particle2 playerDebris[100];
};
#endif

