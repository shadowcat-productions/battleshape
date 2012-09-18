/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Healthbar class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Healthbar class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#ifndef Healthbar_H
#define Healthbar_H

class Healthbar {
public:
    /*
    -------------------- Constructor for the Healthbar class --------------------
    */
    Healthbar();

    /*
    -------------------- Destructor for the Healthbar class --------------------
    */
    ~Healthbar();

    /*
     -------------------- Accessors for the Healthbar class --------------------
     */


    /*
    -------------------- Modifiers for the Healthbar class --------------------
    */

    /*
     -------------------- Methods for the Healthbar class --------------------
     */
     void draw(float currentHP, float maxHP, float width);

private:
    /*
    -------------------- Variables for the Healthbar class --------------------
    */

};
#endif
