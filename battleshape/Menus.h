/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Menus class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Menus class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Text.h"
#include "Vector.h"

#ifndef Menus_H
#define Menus_H

class Menus {
public:
    /*
    -------------------- Constructor for the Menus class --------------------
    */
    Menus();

    /*
    -------------------- Destructor for the Menus class --------------------
    */
    ~Menus();

	void drawMenu(float t, int mouseOverValue);
	void drawHUD(float t, int upgradeLevel, int specialShots, int level, int lives, int score, int shipType, int shields, int nukes);
	void drawPause();
	void initializeCoords();
	
     float iT; // incremented timer for use in rotations, movements, etc
     float leftCoords[100][2]; // 100 verticies for the torus section, x/y coordinates
	
    /*
     -------------------- Methods for the Menus class --------------------
     */
     
     Text text;
     
private:
    /*
    -------------------- Variables for the Menus class --------------------
    */
    
};
#endif
