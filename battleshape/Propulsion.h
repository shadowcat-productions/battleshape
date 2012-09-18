/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Propulsion class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Propulsion class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Torus.h"
#include "Particle2.h"

#ifndef Propulsion_H
#define Propulsion_H


class Propulsion {
public:
    /*
    -------------------- Constructor for the Propulsion class --------------------
    */
    Propulsion();

    /*
    -------------------- Destructor for the Propulsion class --------------------
    */
    ~Propulsion();

    /*
    -------------------- Accessors for the Propulsion class --------------------
    */
    const Vector getPosition( void ) const;
    const bool isActive( void ) const;

    /*
    -------------------- Modifiers for the Propulsion class --------------------
    */
    void setPosition( Vector newPosition );
    void setActive( bool newActive );
    void reLoad(); // de-activates all the particle trails

    /*
    -------------------- Methods for the Propulsion class --------------------
    */
    void updatePropulsion( float timer, Vector newPosition, Vector direction, bool accelerating, bool acceleratingBack );
    void updateRipples(float t, Vector p, bool acc, float r, float g, float b);
private:
    /*
    -------------------- Variables for the Propulsion class --------------------
    */

    Vector position;
    Torus ripple[4];
    Particle2 trail[100];
    Particle2 lightFlare;
    bool active;
    float time;

};


#endif
