/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Explosion class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Explosion class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Vector.h"
#include "Particle2.h"

#ifndef Explosion_H
#define Explosion_H


class Explosion {
public:
    /*
    -------------------- Constructor for the Explosion class --------------------
    */
    Explosion();

    /*
    -------------------- Destructor for the Explosion class --------------------
    */
    ~Explosion();

    /*
    -------------------- Accessors for the Explosion class --------------------
    */
    const Vector getPosition( void ) const;
    const GLfloat getRed( void ) const;
    const GLfloat getGreen( void ) const;
    const GLfloat getBlue( void ) const;
    const GLfloat getSize( void ) const;
    const GLfloat getDuration( void ) const;
    const GLint getNumberParticles( void ) const;
    const GLfloat getParticleSize( void ) const;
    const float getTimer( void ) const;
    const bool isActive( void ) const;

    /*
    -------------------- Modifiers for the Explosion class --------------------
    */
    
    void setPosition(  GLfloat newX ,  GLfloat newY ,  GLfloat newZ  );
    void setRed(  GLfloat newRed  );
    void setGreen(  GLfloat newGreen  );
    void setBlue(  GLfloat newBlue  );
    void setSize(  GLfloat newSize  );
    void setDuration(  GLfloat newDuration  );
    void setNumberParticles( GLint newNumberParticles );
    void setParticleSize( GLfloat newParticleSize );
    void setActive( bool newActive );
    void setTimer( float newTimer );
    void setDrawLightFlare( bool newDrawLightFlare );
    void setLightFlareAlpha( GLfloat newLightFlareAlpha );
    
    /*
    -------------------- Methods for the Explosion class --------------------
    */
    
    void initializeExplosion( float );
    void updateExplosion( float );
    void drawExplosion( float );
    
private:
    /*
    -------------------- Variables for the Explosion class --------------------
    */
    Vector position;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat size;
    GLfloat duration;
    bool active;
    GLint numberParticles;
    GLfloat particleSize;
    float timer;
    Particle2 shrapnel[1000];
    Particle2 lightFlare;
    GLfloat totalTime;
    bool drawLightFlare;
    GLfloat lightFlareAlpha;
    

};


#endif
