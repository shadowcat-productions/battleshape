/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Healthbar.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Healthbar class --------------------
*/

#include "Healthbar.h"

/*
-------------------- Constructor for the Healthbar class --------------------
*/
Healthbar::Healthbar() {

}

/*
-------------------- Destructor for the Healthbar class --------------------
*/
Healthbar::~Healthbar() {

}

void Healthbar::draw(float currentHP, float maxHP, float width)
{
     glColor4f(1- currentHP/maxHP, currentHP/maxHP, 0,1);
     glBegin(GL_QUADS);
     glVertex3f(-width/2,2,1);
     glVertex3f(-width/2+(currentHP/maxHP)*width,2,1);
     glVertex3f(-width/2+(currentHP/maxHP)*width,0,1);
     glVertex3f(-width/2,0,1);
     glEnd();
}
