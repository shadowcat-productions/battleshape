/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about Particles.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Particle class --------------------
*/

#include "Particle.h"

/*
 -------------------- Constructors for the Particle class --------------------
*/

Particle::Particle(){
     setXBegin( 0.0 );
     setYBegin( 0.0 );
     setZBegin( 0.0 );
     setXEnd( 0.0 );
     setYEnd( 0.0 );
     setZEnd( 0.0 );
     setRed( 0.0 );
     setGreen( 0.0 );
     setBlue( 0.0 );
     setType( 0 );
     setTime( 0.0 );
     setTotalTime( 0.0 );
}

/*
 -------------------- Destructor for the Particle class --------------------
*/
Particle::~Particle(){
}

/*
 -------------------- Accessors for the Particle class --------------------
*/

const float Particle::getXBegin( void ) const{ //returns the beginning x coordinate
      return xBegin;
}

const float Particle::getYBegin( void ) const{ //returns the beginning y coordinate
      return yBegin;
}

const float Particle::getZBegin( void ) const{ //returns the beginning z coordinate
      return zBegin;
}

const float Particle::getXEnd( void ) const{ //returns the end x coordinate
      return xEnd;
}

const float Particle::getYEnd( void ) const{ //returns the end y coordinate
      return yEnd;
}

const float Particle::getZEnd( void ) const{ //returns the end z coordinate

}

const float Particle::getRed( void ) const{ //returns the red colour value
      return red;
}

const float Particle::getGreen( void ) const{ //returns the green colour value
      return green;
}

const float Particle::getBlue( void ) const{ //returns the blue colour value
      return blue;
}

const int Particle::getType( void ) const{ //returns the particle type
    return type;
}

const float Particle::getTime( void ) const{ //returns the time
      return time;
}

const float Particle::getTotalTime( void ) const{ //returns the total time
      return totalTime;
}

const float Particle::getRatio( void ) const{ //returns the ratio
      return ratio;
}

     
/*
 -------------------- Modifiers for the Particle class --------------------
*/

void Particle::setXBegin( float newXBegin ){ //sets the beginning x coordinate
     xBegin = newXBegin;
}

void Particle::setYBegin( float newYBegin ){ //sets the beginning y coordinate
     yBegin = newYBegin;
}

void Particle::setZBegin( float newZBegin ){ //sets the beginning z coordinate
     zBegin = newZBegin;
}

void Particle::setXEnd( float newXEnd ){ //sets the end x coordinate
     xEnd = newXEnd;
}

void Particle::setYEnd( float newYEnd ){ //sets the end y coordinate
     yEnd = newYEnd;
}

void Particle::setZEnd( float newZEnd ){ //sets the end z coordinate
     zEnd = newZEnd;
}

void Particle::setRed( float newRed ){ //sets the new red colour value
     red = newRed;
}

void Particle::setGreen( float newGreen ){ //sets the new green colour value
     green = newGreen;
}

void Particle::setBlue( float newBlue ){ //sets the new blue colour value
     blue = newBlue;
}

void Particle::setType( int newType ){ //sets the new type
     type = newType;
}

void Particle::setTime( float newTime ){ //sets the new time
     time = newTime;
}

void Particle::setTotalTime( float newTotalTime ){ //sets the new total time
     totalTime = newTotalTime;
}

void Particle::setRatio( float newRatio ){ //sets the new ratio
     ratio = newRatio;
}  
     
/*
 -------------------- Methods for the Particle class --------------------
*/

void Particle::setData( float newXBegin, float newYBegin, float newZBegin, float newXEnd, float newYEnd, float newZEnd, int newType, float newTime){ //sets particle data all in one function
     setXBegin( newXBegin );
     setYBegin( newYBegin );
     setZBegin( newZBegin );
     setXEnd( newXEnd );
     setYEnd( newYEnd );
     setZEnd( newZEnd );
     setType( newType );
     setTime( newTime );
     setRatio( 1.0 );

     if (newType == 1) {
           //something if particle is type 1
     }else if (newType == 0) {
           //something if particle is type 0
     }
}

bool Particle::updateParticle( float newTime ){ //updates the particle based on time
     setTime(getTime() - newTime );
     if(getType() == 0){
        xBegin += (2 * xEnd * newTime) / 1000.0;
        yBegin += (2 * yEnd * newTime) / 1000.0;
        zBegin += (2 * zEnd * newTime) / 1000.0;
     }
     
     if(getType() == 1){
        xBegin += (2 * xEnd * newTime) / 500.0;
        yBegin += (2 * yEnd * newTime) / 500.0;
        zBegin += (2 * zEnd * newTime) / 500.0;
        xEnd = 0.98 * xEnd;
        yEnd = 0.98 * yEnd;
        zEnd = 0.98 * zEnd;
    }else{
        zBegin += 1 * newTime;
    }
    ratio = time / totalTime;
    if (time < 0) return false;
    else return true;
}

void Particle::drawParticle( float particleSize ){ //draws a given particle
     glEnable(GL_TEXTURE_2D);
     glColor4f(getRed(), getGreen(), getBlue(), getRatio());
     
     glPushMatrix();
     
     glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
          glTexCoord2d(1,1); glVertex3f(getXBegin() + particleSize, getYBegin() + particleSize, 1); // Top Right
          glTexCoord2d(0,1); glVertex3f(getXBegin() - particleSize, getYBegin() + particleSize, 1); // Top Left
          glTexCoord2d(1,0); glVertex3f(getXBegin() + particleSize, getYBegin() - particleSize, 1); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(getXBegin() - particleSize, getYBegin() - particleSize, 1); // Bottom Left
     glEnd();
    			
     glPopMatrix();
    			
     glDisable(GL_TEXTURE_2D);
}

