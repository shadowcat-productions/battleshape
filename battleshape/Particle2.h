/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Particle2 class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Particle2 class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>
#include "Vector.h"

#ifndef Particle2_H
#define Particle2_H


class Particle2{
public:
     /*
     -------------------- Constructor for the Particle2 class --------------------
     */
     Particle2();

     /*
     -------------------- Destructor for the Particle2 class --------------------
     */
	~Particle2();

     /*
     -------------------- Accessors for the Particle2 class --------------------
     */
     const Vector getPosition( void ) const;
     const Vector getTravelVector( void ) const;
     const GLfloat getRed( void ) const;
     const GLfloat getGreen( void ) const;
     const GLfloat getBlue( void ) const;
     const GLfloat getAlpha( void ) const;
     const GLfloat getSize( void ) const;
     const float getTime( void ) const;
     const float getDuration( void ) const;

     /*
     -------------------- Modifiers for the Particle2 class --------------------
     */
     void setPosition(GLfloat newX, GLfloat newY, GLfloat newZ);
     void setTravelVector(GLfloat newX, GLfloat newY, GLfloat newZ);
     void normalizeTravelVector();
     void multiplyTravelVector(float a);
     void setRed( GLfloat newRed );
     void setGreen( GLfloat newGreen );
     void setBlue( GLfloat newBlue );
     void setAlpha( GLfloat newAlpha );
     void setColor(GLfloat newRed, GLfloat newGreen, GLfloat newBlue, GLfloat newAlpha);
     void setSize( GLfloat newSize );
     void setTime( float newTime );
     void setDuration( float newDuration );

     /*
     -------------------- Methods for the Particle2 class --------------------
     */

     void drawParticle( void );

    bool active;

     Vector position;
     Vector travelVector; // Slightly re-purposing in the spawning debris in Drone to store it's location in a circle around the drone

     private:
     /*
     -------------------- Variables for the Particle2 class --------------------
     */

     GLfloat red;
     GLfloat green;
     GLfloat blue;
     GLfloat alpha;
     GLfloat size;
     float time;
     float duration;

};
#endif
