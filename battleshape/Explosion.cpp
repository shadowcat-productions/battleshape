/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about Explosions.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Explosion class --------------------
*/
#include "Explosion.h"

/*
 -------------------- Constructors for the Explosion class --------------------
*/

Explosion::Explosion() : lightFlareAlpha(0.3){
     setActive(false);
     setDrawLightFlare(false);
}

/*
 -------------------- Destructor for the Explosion class --------------------
*/
Explosion::~Explosion(){
}

/*
 -------------------- Accessors for the GameHandler class --------------------
*/

const Vector Explosion::getPosition( void ) const{ return position; }

const GLfloat Explosion::getRed( void ) const{ return red; }

const GLfloat Explosion::getGreen( void ) const{ return green; }

const GLfloat Explosion::getBlue( void ) const{ return blue; }

const GLfloat Explosion::getSize( void ) const{ return size; }

const GLfloat Explosion::getDuration( void ) const{ return duration; }

const GLfloat Explosion::getParticleSize( void ) const{ return particleSize; }

const GLint Explosion::getNumberParticles( void ) const{ return numberParticles; }

const float Explosion::getTimer( void ) const{ return timer; }

const bool Explosion::isActive( void ) const{ return active; }

/*
 -------------------- Modifiers for the GameHandler class --------------------
*/

void Explosion::setPosition(  GLfloat newX ,  GLfloat newY ,  GLfloat newZ  ){
     position.set(newX, newY, newZ);       
}

void Explosion::setRed(  GLfloat newRed  ){
     red = newRed;       
}

void Explosion::setGreen(  GLfloat newGreen  ){
     green = newGreen;       
}

void Explosion::setBlue(  GLfloat newBlue  ){
     blue = newBlue;      
}

void Explosion::setSize(  GLfloat newSize  ){
     size = newSize;       
}

void Explosion::setDuration(  GLfloat newDuration  ){
     duration = newDuration;       
}

void Explosion::setParticleSize(  GLfloat newParticleSize  ){
     particleSize = newParticleSize;       
}

void Explosion::setNumberParticles(  GLint newNumberParticles  ){
     numberParticles = newNumberParticles;       
}

void Explosion::setTimer(  float newTimer  ){
     timer = newTimer;       
}

void Explosion::setLightFlareAlpha(  GLfloat newLightFlareAlpha  ){
     lightFlareAlpha = newLightFlareAlpha;       
}

void Explosion::setActive(  bool newActive  ){
     active = newActive;       
}

void Explosion::setDrawLightFlare(  bool newDrawLightFlare  ){
     drawLightFlare = newDrawLightFlare;       
}

/*
 -------------------- Methods for the GameHandler class --------------------
*/

void Explosion::initializeExplosion(float t){

     setActive(true);
     setTimer(t);
     totalTime = getDuration();
     
//     srand(t);
     
     if (drawLightFlare){
        lightFlare.setRed(1.0);
        lightFlare.setGreen(1.0);
        lightFlare.setBlue(1.0);
        lightFlare.setAlpha(lightFlareAlpha);
        lightFlare.setSize(70);
        lightFlare.setPosition(position.getX(), position.getY(), position.getZ());
     }
     
     int numberLargeParticles = (int) getNumberParticles() / 3;
     int numberMediumParticles = (int) getNumberParticles() / 3;
     int numberSmallParticles = (int) getNumberParticles() / 3;
     
     
     for(int i = 0; i < numberLargeParticles; i++){
             shrapnel[i].setPosition(position.getX(), position.getY(), position.getZ());
             shrapnel[i].setTravelVector(float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize(), float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize(), float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize());
             shrapnel[i].normalizeTravelVector();
//             shrapnel[i].setTravelVector(( 200.0 * rand() /( RAND_MAX + 1.0 ))*shrapnel[i].getTravelVector().getX()*getSize()/10,( 200.0 * rand() /( RAND_MAX + 1.0 ))*shrapnel[i].getTravelVector().getY()*getSize()/10, 1.0);  
             shrapnel[i].multiplyTravelVector(( 200.0 * rand() /( RAND_MAX + 1.0 ))*getSize()/10);
             shrapnel[i].setSize((GLint)getParticleSize());
     }
     
     for(int i = numberLargeParticles; i < numberLargeParticles + numberMediumParticles; i++){
             shrapnel[i].setPosition(position.getX(), position.getY(), position.getZ());
             shrapnel[i].setTravelVector(float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize()*1.5, float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize()*4, float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize()*4);
             shrapnel[i].normalizeTravelVector();
//             shrapnel[i].setTravelVector(( 200.0 * rand() /( RAND_MAX + 1.0 ))*shrapnel[i].getTravelVector().getX()*getSize()/8,( 200.0 * rand() /( RAND_MAX + 1.0 ))*shrapnel[i].getTravelVector().getY()*getSize()/8, 1.0);  
             shrapnel[i].multiplyTravelVector(( 200.0 * rand() /( RAND_MAX + 1.0 ))*getSize()/8);
             shrapnel[i].setSize((GLint)(getParticleSize() * 0.5));
     }
     
     for(int i = numberLargeParticles + numberMediumParticles; i < numberLargeParticles + numberMediumParticles + numberSmallParticles; i++){
             shrapnel[i].setPosition(position.getX(), position.getY(), position.getZ());
             shrapnel[i].setTravelVector(float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize()*1.9, float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize()*8, float((1 + (int)( 2000.0 * rand() / ( RAND_MAX + 1.0 ) )) / 30 - 32.0f)*getSize()*8);
             shrapnel[i].normalizeTravelVector();
//             shrapnel[i].setTravelVector(( 200.0 * rand() /( RAND_MAX + 1.0 ))*shrapnel[i].getTravelVector().getX()*getSize()/7,( 200.0 * rand() /( RAND_MAX + 1.0 ))*shrapnel[i].getTravelVector().getY()*getSize()/7, 1.0);  
             shrapnel[i].multiplyTravelVector(( 200.0 * rand() /( RAND_MAX + 1.0 ))*getSize()/7);  
             shrapnel[i].setSize((GLint)(getParticleSize() * 0.25));
     }

     for(int i = 0; i < getNumberParticles(); i++){
          int shrapColour = rand() % 6;
          if (shrapColour == 0) {
               shrapnel[i].setRed(1.0);
               shrapnel[i].setGreen(1.0);
               shrapnel[i].setBlue(1.0);
          }else if (shrapColour == 1) {
               shrapnel[i].setRed(0.6 * red);
               shrapnel[i].setGreen(0.6 * green);
               shrapnel[i].setBlue(0.6 * blue);
          }else if (shrapColour == 2) {
               shrapnel[i].setRed(0.4 * red);
               shrapnel[i].setGreen(0.4 * green);
               shrapnel[i].setBlue(0.4 * blue);
          }else if (shrapColour == 3) {
               shrapnel[i].setRed(0.2 * red);
               shrapnel[i].setGreen(0.2 * green);
               shrapnel[i].setBlue(0.2 * blue);
          }else{
               shrapnel[i].setRed(0.2 * red);
               shrapnel[i].setGreen(0.2 * green);
               shrapnel[i].setBlue(0.2 * blue);
          }
          if(shrapnel[i].getPosition().getX() < 1 && shrapnel[i].getPosition().getY() < 1){
               shrapnel[i].setPosition(-100, -100, 1.0);
          }
     }
}

void Explosion::updateExplosion( float t ){
     float timeElapsed = t - getTimer();
     duration -= timeElapsed;
     setTimer(t);
     
     lightFlare.setAlpha(lightFlare.getAlpha() - 0.01 * timeElapsed); 
          
     for(int i = 0; i < getNumberParticles(); i++){
     
          shrapnel[i].setAlpha(duration / totalTime);

          GLfloat xValue = (GLfloat)(shrapnel[i].getPosition().getX() + (getSize() * shrapnel[i].getTravelVector().getX() * timeElapsed) / 1000.0);
          GLfloat yValue = (GLfloat)(shrapnel[i].getPosition().getY() + (getSize() * shrapnel[i].getTravelVector().getY() * timeElapsed) / 1000.0);
          GLfloat zValue = (GLfloat)(shrapnel[i].getPosition().getZ() + (getSize() * shrapnel[i].getTravelVector().getZ() * timeElapsed) / 1000.0);
          shrapnel[i].setPosition(xValue, yValue, zValue);
     
          shrapnel[i].setTravelVector(0.98 * shrapnel[i].getTravelVector().getX(),
                                      0.98 * shrapnel[i].getTravelVector().getY(),
                                      0.98 * shrapnel[i].getTravelVector().getZ());
     }
     if(duration < 0){
          setActive(false);
     }
}

void Explosion::drawExplosion( float t ){
     if(isActive()){
          updateExplosion( t );
          if (drawLightFlare){
             lightFlare.drawParticle();
          }
          for(int i = 0; i < getNumberParticles(); i++){
               shrapnel[i].drawParticle();
          }   
     }       
}

