/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Torus.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Torus class --------------------
*/

#include "Torus.h"

/*
-------------------- Constructor for the Torus class --------------------
*/
Torus::Torus()
{
     isActive = false;
}

/*
-------------------- Destructor for the Torus class --------------------
*/
Torus::~Torus() {

}

/*
-------------------- Modifiers for the Torus class --------------------
*/

// Set a new torus with x,y,z location, final width, propogation speed and inner width
void Torus::set (GLfloat x1, GLfloat y1, GLfloat z1, GLfloat width1, GLfloat speed1, GLfloat in1)
{
     x = x1;
     y = y1;
     z = z1;
     width = width1;
     speed = speed1;
     in = in1;
     expander = 0;
     detailLevel = 15;
     isActive = true;
     isWake = false;
     expanding = true;
}

// Set angle variables for the wake of penetrating shots. Not to be used otherwise.
void Torus::setWake(GLfloat theta1, bool leftSide1)
{
     isWake = true;
     theta = theta1;
     leftSide = leftSide1;
}

// Set torus color
void Torus::color (GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
     red = r;
     green = g;
     blue = b;
     alpha = a;
}

// Set detail level
void Torus::detail(int x)
{
     detailLevel = x;
}

/*
-------------------- Methods for the Torus class --------------------
*/

void Torus::draw (const float t)
{
     // Tween the alpha of the torus based on whether it is expanding or contracting
     if (expanding) glColor4f(red, green, blue, alpha - alpha * expander / width);
     else glColor4f(red, green, blue, alpha * expander / width);

     if (isActive)
     {
          expander += t * speed;
          glPushMatrix();
          glTranslatef(x,y,z);
          
          // Rotate torus appropriately if it is the wake of a penetrating shot
          if (isWake)
          {
               if ( leftSide )
                       glRotatef( theta*180 / 3.14159, 0.0, 0.0, 1.0 );
                  else
                       glRotatef( -theta*180 / 3.14159, 0.0, 0.0, 1.0 );
                       
               glRotatef( 90, 1,0,0);
          }
          
          if (expanding)
          {
               if(in < expander)
                    glutSolidTorus(in, expander, detailLevel, detailLevel);
               else
                    glutSolidTorus(expander, expander, detailLevel, detailLevel);
          }
          else 
          {
               if(in < width - expander)
                    glutSolidTorus(in, width - expander, detailLevel, detailLevel);
               else
                    glutSolidTorus(width - expander, width - expander, detailLevel, detailLevel);
          }
          glPopMatrix();
     }
     // Once the torus has completed propogating deactive it
     if (expander > width)
     {
          isActive = false;
          expander = 0;
     }
}
