/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about Particles.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Particle class --------------------
*/

#include "Particle2.h"


/*
 -------------------- Constructors for the Particle class --------------------
*/

Particle2::Particle2() : active(false){
     setPosition(0.0, 0.0, 1.0);
     setTravelVector(0.0, 0.0, 1.0);
     setRed( 1.0 );
     setGreen(0.0);
     setBlue(0.0);
     setAlpha(0.3);
     setSize(2);
     setTime(0.0);
     setDuration(0.0);
}

/*
 -------------------- Destructor for the Particle class --------------------
*/
Particle2::~Particle2(){
}

/*
 -------------------- Accessors for the Particle class --------------------
*/
const Vector Particle2::getPosition( void ) const{
     return position;
}

const Vector Particle2::getTravelVector( void ) const{
     return travelVector;
}

const GLfloat Particle2::getRed() const{
     return red;
}

const GLfloat Particle2::getGreen() const{
     return green;
}

const GLfloat Particle2::getBlue() const{
     return blue;
}

const GLfloat Particle2::getAlpha() const{
     return alpha;
}

const GLfloat Particle2::getSize() const{
     return size;
}

const float Particle2::getTime() const{
     return time;
}

const float Particle2::getDuration() const{
     return duration;
}

/*
 -------------------- Modifiers for the Particle class --------------------
*/
void Particle2::setPosition(GLfloat newX, GLfloat newY, GLfloat newZ){
     position.set(newX, newY, newZ);
}

void Particle2::setTravelVector(GLfloat newX, GLfloat newY, GLfloat newZ){
     travelVector.set(newX, newY, newZ);
}

void Particle2::normalizeTravelVector(){
     travelVector.normalize();
}

void Particle2::multiplyTravelVector(float a){
     travelVector.multiply(a);
}

void Particle2::setRed( GLfloat newRed ){
     red = newRed;
}

void Particle2::setGreen( GLfloat newGreen ){
     green = newGreen;
}

void Particle2::setBlue( GLfloat newBlue ){
     blue = newBlue;
}

void Particle2::setAlpha( GLfloat newAlpha ){
     alpha = newAlpha;
}

void Particle2::setColor( GLfloat newRed, GLfloat newGreen, GLfloat newBlue, GLfloat newAlpha ){
     red = newRed;
     green = newGreen;
     blue = newBlue;
     alpha = newAlpha;
}

void Particle2::setSize( GLfloat newSize ){
     size = newSize;
}

void Particle2::setTime( float newTime ){
     time = newTime;
}

void Particle2::setDuration( float newDuration ){
     duration = newDuration;
}

/*
 -------------------- Methods for the Particle class --------------------
*/

void Particle2::drawParticle( void ){
     glEnable(GL_TEXTURE_2D);
     glColor4f(getRed(), getGreen(), getBlue(), getAlpha());

     glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
          glTexCoord2d(1,1); glVertex3f(position.getX() + getSize(), position.getY() + getSize(), position.getZ()); // Top Right
          glTexCoord2d(0,1); glVertex3f(position.getX() - getSize(), position.getY() + getSize(), position.getZ()); // Top Left
          glTexCoord2d(1,0); glVertex3f(position.getX() + getSize(), position.getY() - getSize(), position.getZ()); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(position.getX() - getSize(), position.getY() - getSize(), position.getZ()); // Bottom Left
     glEnd();

     glDisable(GL_TEXTURE_2D);
}
