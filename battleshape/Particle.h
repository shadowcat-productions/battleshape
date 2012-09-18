/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Particle class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Particle class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>

#ifndef Particle_H
#define Particle_H


class Particle{
public:
     /*
     -------------------- Constructor for the Particle class --------------------
     */
     Particle();
     
     /*
     -------------------- Destructor for the Particle class --------------------
     */
	~Particle();
     
     /*
     -------------------- Accessors for the Particle class --------------------
     */
     
     const float getXBegin( void ) const; //returns the beginning x coordinate
     const float getYBegin( void ) const; //returns the beginning y coordinate
     const float getZBegin( void ) const; //returns the beginning z coordinate
     const float getXEnd( void ) const; //returns the end x coordinate
     const float getYEnd( void ) const; //returns the end y coordinate
     const float getZEnd( void ) const; //returns the end z coordinate
     const float getRed( void ) const; //returns the red colour value
     const float getGreen( void ) const; //returns the green colour value
     const float getBlue( void ) const; //returns the blue colour value
     const int getType( void ) const; //returns the particle type
     const float getTime( void ) const; //returns the time
     const float getTotalTime( void ) const; //returns the total time
     const float getRatio( void ) const; //returns the ratio
     
     /*
     -------------------- Modifiers for the Particle class --------------------
     */
     
     void setXBegin( float newXBegin ); //sets the beginning x coordinate
     void setYBegin( float newYBegin ); //sets the beginning y coordinate
     void setZBegin( float newZBegin ); //sets the beginning z coordinate
     void setXEnd( float newXEnd ); //sets the end x coordinate
     void setYEnd( float newYEnd ); //sets the end y coordinate
     void setZEnd( float newZEnd ); //sets the end z coordinate
     void setRed( float newRed ); //sets the new red colour value
     void setGreen( float newGreen ); //sets the new green colour value
     void setBlue( float newBlue ); //sets the new blue colour value
     void setType( int newType ); //sets the new type
     void setTime( float newTime ); //sets the new time
     void setTotalTime( float newTotalTime ); //sets the new total time
     void setRatio( float newRatio ); //sets the ratio
     
     /*
     -------------------- Methods for the Particle class --------------------
     */
     
     void setData( float, float, float, float, float, float, int, float ); //sets particle data all in one function
     bool updateParticle( float ); //updates the particle based on time
     void drawParticle( float particleSize ); //draws a given particle
        
     private:
     /*
     -------------------- Variables for the GameHandler class --------------------
     */
     float xBegin;
     float yBegin;
     float zBegin;
     
     float xEnd;
     float yEnd;
     float zEnd;
     
     float red;
     float green;
     float blue;
     
     int type;
     float time;
     float totalTime;

     float ratio;
        
        
};
#endif
