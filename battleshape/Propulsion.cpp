/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Propulsion.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Propulsion class --------------------
*/

#include "Propulsion.h"


/*
 -------------------- Constructors for the Propulsion class --------------------
*/
Propulsion::Propulsion() : time(0.0){
}

/*
 -------------------- Destructor for the Propulsion class --------------------
*/
Propulsion::~Propulsion() {
}
/*
-------------------- Accessors for the Propulsion class --------------------
*/
const Vector Propulsion::getPosition( void ) const {
    return position;
}

const bool Propulsion::isActive( void ) const {
    return active;
}

 /*
-------------------- Modifiers for the Propulsion class --------------------
*/
void Propulsion::setPosition( Vector newPosition ) {
    position.set(newPosition.getX(), newPosition.getY(), newPosition.getZ());
}

void Propulsion::setActive( bool newActive ) {
    active = newActive;
}

/*
-------------------- Methods for the Propulsion class --------------------
*/
void Propulsion::updateRipples(float t, Vector p, bool acc, float r, float g, float b)
{
     int i;
     int newestRipple;
     float currentExpansion = 1.0;
     bool anyActive = false;
     
     for (i = 0; i < 4; i++)
     {
          if (ripple[i].isActive == true)
          {
               anyActive = true;
               if (ripple[i].expander / ripple[i].width <= currentExpansion)
               {
                    currentExpansion = ripple[i].expander / ripple[i].width;
                    newestRipple = i;
               }
          }
     }
     if (acc)
     {
          if (anyActive == false) // set one
          {
              ripple[0].set(p.getX(), p.getY(), p.getZ(), 5, 0.2, 1);
              ripple[0].color(r,g,b,0.6);
          }
          else
          {
               if (currentExpansion > 0.25)
               {
                    if (newestRipple == 3)
                    {
                        ripple[0].set(p.getX(), p.getY(), p.getZ(), 5, 0.2, 1);
                        ripple[0].color(r,g,b,0.6);
                    }
                    else
                    {
                        ripple[newestRipple + 1].set(p.getX(), p.getY(), p.getZ(), 5, 0.2, 1);
                        ripple[newestRipple + 1].color(r,g,b,0.6);
                    }
               }
          }
     }
     for (i = 0; i < 4; i ++)
          ripple[i].draw(t);
}

void Propulsion::reLoad()
{
    for(int i = 0; i < 100; i++)
         trail[i].active = false;
}

void Propulsion::updatePropulsion( float timer, Vector newPosition, Vector direction, bool accelerating, bool acceleratingBack ) {
    float timeElapsed = 0.0;
    if(timer > time){
        timeElapsed = timer - time;
    }

    time = timer;
    for(int i = 0; i < 100; i++){

        Vector particlePosition;
        particlePosition = trail[i].getPosition();
        Vector particleTravelVector;
        particleTravelVector = trail[i].getTravelVector();

        if(trail[i].active){
            trail[i].setPosition(particlePosition.getX() + (particleTravelVector.getX() / 4.0), particlePosition.getY() + (particleTravelVector.getY() / 4.0), particlePosition.getZ());
            trail[i].setTravelVector(particleTravelVector.getX(), particleTravelVector.getY(), 0.0);

            trail[i].setAlpha(trail[i].getAlpha() - 0.03);

            if(trail[i].getAlpha() < 0.01){
                trail[i].active = false;
            }
            
            float originalAlpha = trail[i].getAlpha();
            trail[i].setSize(7.0);
            trail[i].setAlpha(originalAlpha / 12);
            trail[i].setRed(0.8f);
            trail[i].setGreen(0.0f);
            trail[i].setBlue(0.0f);
            trail[i].drawParticle();


            trail[i].setPosition(particlePosition.getX() + (particleTravelVector.getX() / 4), particlePosition.getY() + (particleTravelVector.getY() / 4), particlePosition.getZ());
            trail[i].setSize(3.0);
            trail[i].setAlpha(originalAlpha / 10);
            trail[i].setRed(0.8f);
            trail[i].setGreen(0.5f);
            trail[i].setBlue(0.0f);
            trail[i].drawParticle();

            trail[i].setAlpha(originalAlpha);

        }else{

            if(float(rand()%10)>2){
                trail[i].setRed(1.0);
                trail[i].setGreen(0.0);
                trail[i].setBlue(0.0);
            }else{
                trail[i].setRed(0.5);
                trail[i].setGreen(0.5);
                trail[i].setBlue(0.1);
            }
            if (accelerating){
                    trail[i].setTravelVector(-direction.getX(), -direction.getY(), 1.0);
                    trail[i].active = true;
            }else if(acceleratingBack){
                    trail[i].setTravelVector(direction.getX(), direction.getY(), 1.0);
                    trail[i].active = true;
            }else{

            }
            trail[i].normalizeTravelVector();
            trail[i].setPosition(newPosition.getX() - direction.getX() * 1.4, newPosition.getY() - direction.getY() * 1.4, 1.0);
            trail[i].setAlpha(float(rand()%100)/100);
            trail[i].setSize(1.0);
        }
    }
}
