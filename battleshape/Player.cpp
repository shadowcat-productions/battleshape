/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Player.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Player class --------------------
*/
#include "Player.h"
#include "SoundManager.h"
#include "Sounds.h"


/*
-------------------- Constructor for the Player class --------------------
*/
Player::Player() : sphereRoll(0), acceleration(0), maxVelocity(0), dampening(0), upgradeLevel(0),
 boolTurningLeft(false), boolTurningRight(false), boolAccelerating(false),boolAcceleratingBack(false),
 shotCounter(0), shootingNow(false), reloadTimer(0), reloadTime(13), rof(2),
  shields(3), nukes(150), maxShields(40.0), cameraShake(false), turnSpeed(0.08)
{
     position.set ( 100.0, 75.0, 1.0 );
     movement.set ( 0, 0, 0 );
     direction.set ( 0, 1, 0 );
     currentRotation.set( 0, 0, 0);
     currentBounceRotation = 0;
}


/*
-------------------- Destructor for the Player class --------------------
*/
Player::~Player() {

}

/*
-------------------- Accessors for the Player class --------------------
*/

GLfloat Player::getAcceleration() {
     return acceleration;
}

/*
-------------------- Modifiers for the Player class --------------------
*/

void Player::getUpgrade(int type) {

     upgradeLevel = type;
     specialShots = 0;

     SoundManager::playSoundEffect( SOUND_EFFECT::UPGRADE_COLLECTION );

     if (type == 1) // spread shot
     {
          specialShots = 20;
     }
     if (type == 2) // railgun
     {
          specialShots = 20;
     }
     if (type == 3) // bouncing
     {
          specialShots = 20;
     } 
     if (type == 4)// shooting stars
     {
          specialShots = 5;
     }
}

void Player::setColour(int p, int s)
{
     if (p == 1) {primaryColour[0] = 1; primaryColour[1] = 1; primaryColour[2] = 1;}
     else if (p == 2) {primaryColour[0] = 1; primaryColour[1] = 1; primaryColour[2] = 0;}
     else if (p == 3) {primaryColour[0] = 1; primaryColour[1] = 0; primaryColour[2] = 0;}
     else if (p == 4) {primaryColour[0] = 0; primaryColour[1] = 1; primaryColour[2] = 1;}
     
     if (s == 1) {secondaryColour[0] = 1; secondaryColour[1] = 1; secondaryColour[2] = 1;}
     else if (s == 2) {secondaryColour[0] = 1; secondaryColour[1] = 1; secondaryColour[2] = 0;}
     else if (s == 3) {secondaryColour[0] = 1; secondaryColour[1] = 0; secondaryColour[2] = 0;}
     else if (s == 4) {secondaryColour[0] = 0; secondaryColour[1] = 1; secondaryColour[2] = 1;}
}

void Player::setROF(float x) {
     rof = x;
}

void Player::accelerating( bool a ) {
     boolAccelerating = a;
     boolAcceleratingBack = false;
}

void Player::acceleratingBack( bool a ) {
     boolAcceleratingBack = a;
     boolAccelerating = false;
}

void Player::turningLeft( bool a ) {
     boolTurningLeft = a;
     boolTurningRight = false;
}

void Player::turningRight( bool a ) {
     boolTurningRight = a;
     boolTurningLeft = false;
}

void Player::shooting( bool a ) {
     shootingNow = a;
}

void Player::setAcceleration( GLfloat a ) {
     acceleration = a;
}

void Player::movePlayer( float t ) {
     // Set the position to be incremented by the movement vector
     position.set( position.getX() + t*( float )( movement.getX() ), position.getY() + t*( float )( movement.getY() ), 1 );
     currentRotation.set(currentRotation.getX() + t*movement.getX(), currentRotation.getY() + t*movement.getY(), currentRotation.getZ() + t*movement.getZ());
     if (shipType == 4) direction.set(0,0,0);
     dampenMovement( t );
     reloadTimer -= t;
     if ( boolTurningLeft ) {

          if (shipType != 4) rotateLeft( t );
          else direction.set(direction.getX()-1,direction.getY(),0);
     }
     if ( boolTurningRight ) {
          if (shipType != 4) rotateRight( t );
          else  direction.set(direction.getX()+1,direction.getY(),0);
     }
     if ( boolAccelerating ) {
          if (shipType == 4) direction.set(direction.getX(),direction.getY()+1,0);
          else acceleratePlayer( t );
     }
     if ( boolAcceleratingBack ) {
          if (shipType == 4) direction.set(direction.getX(),direction.getY()-1,0);
          else acceleratePlayerBack( t );
     }

     if (shipType == 4)
     {
          if (direction.getLength() > 0)
          {
               direction.normalize();
               acceleratePlayer(t);
          }
          direction.set(0,1,0);
     }
     


     // If the player hits a wall, don't go out of the bounds of the grid.
     if ( position.getX() < 2.5 ) {
          position.set( 2.5, position.getY(), position.getZ() );
          movement.set ( 0, movement.getY(), 0 );
     }
     if ( position.getX() > 197.5 ) {
          position.set( 197.5, position.getY(), position.getZ() );
          movement.set ( 0, movement.getY(), 0 );
     }
     if ( position.getY() < 2.5 ) {
          position.set( position.getX(), 2.5, position.getZ() );
          movement.set ( movement.getX(), 0, 0 );
     }
     if ( position.getY() > 147.5 ) {
          position.set( position.getX(), 147.5, position.getZ() );
          movement.set ( movement.getX(), 0, 0 );
     }
}


void Player::acceleratePlayer( float t ) {
     // Set the movement to be incremented by the direction vector
     movement.set( direction.getX()*acceleration*t + movement.getX(), direction.getY()*acceleration*t + movement.getY(), 0 );

     // If the player hits max speed, stop accelerating
     if ( movement.getLength() > maxVelocity ) {
          GLfloat nx, ny, nz;
          nx = movement.getX() / movement.getLength() * maxVelocity;
          ny = movement.getY() / movement.getLength() * maxVelocity;
          nz = movement.getZ() / movement.getLength() * maxVelocity;
          movement.set( nx, ny, nz );
     }
}

void Player::acceleratePlayerBack( float t ) {
     // Set the movement to be incremented by the direction vector
     movement.set( -direction.getX()*acceleration*t + movement.getX(), -direction.getY()*acceleration*t + movement.getY(), 0 );

     // If the player hits max speed, stop accelerating
     if ( movement.getLength() > maxVelocity ) {
          GLfloat nx, ny, nz;
          nx = movement.getX() / movement.getLength() * maxVelocity;
          ny = movement.getY() / movement.getLength() * maxVelocity;
          nz = movement.getZ() / movement.getLength() * maxVelocity;
          movement.set( nx, ny, nz );
     }
}

void Player::dampenMovement( float t ) {
     // Reduce the speed by a constant.
     movement.set( movement.getX()*pow(dampening,t/2.0), movement.getY()*pow(dampening,t/2.0), 0 );
}
/*
-------------------- Methods for the Player class --------------------
*/

//draws the player
void Player::drawPlayer(float t, GLint x, GLint y) { // x and y are the direction of the gun
         Vector origin;  origin.set( 0, 1, 0 );
         Vector dir = direction.getNormal();
         shipLeftSide = false;
         float dot = ( float )direction.getY();
         if ( direction.getX() < 0 ) {
              shipLeftSide = true;
         }
         shipTheta = acos( dot );

          // Translate and rotate the ship to the correct position
         glPushMatrix();
         glColor4f( 1.0, 1.0, 1.0, 0.8 );
         glLineWidth( 1 );
         glTranslatef( position.getX(), position.getY(), position.getZ() );
         if ( shipLeftSide )
              glRotatef( shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );
         else
              glRotatef( -shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );

         if (shipType < 4)
         {
             glTranslatef( 0, -1.5, 0 );
             glRotatef( -90.0, 1.0, 0.0, 0.0 );
             glTranslatef( 0, 2, 0 );
         }

         // Cone ship
         if(shipType==0){
             glutWireCone( 2, 4, 7, 3 );
         }
         // Cradle ship
         else if(shipType==1){
             drawShip1();
         }
         // 2D cradle
         else if(shipType==2){
             drawShip2();
         }
         // Sexy ship
         else if(shipType==3){
              drawShip3();
         }
         // UFO. Note, the UFO uses weird translations so it will have to have its own dots for shields/nukes and its own shield drawing
         else if(shipType==4){
              drawShip4(t);
             // Draw the firing box
             glPushMatrix();
             glColor4f( 1, 0, 0, 1 );
             // Unrotate the direction
             if ( shipLeftSide )
                  glRotatef( -shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );
             else
                  glRotatef( shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );

             if(x>=0&&y>=0)
                 glRotatef(270+180*atan((float)y/(float)x)/3.14159, 0.0, 0.0, 1.0 );
             else if(x>=0&&y<0)
                 glRotatef(270-atan(-(float)y/(float)x)*180/3.14159, 0.0, 0.0, 1.0 );
             else if(x<0&&y<=0)
                 glRotatef(90+atan((float)y/(float)x)*180/3.14159, 0.0, 0.0, 1.0 );
             else if(x<0&&y>0)
                 glRotatef(90-atan(-(float)y/(float)x)*180/3.14159, 0.0, 0.0, 1.0 );
             glTranslatef(0,2.2,0);
             glutSolidCube(0.9);
             glPopMatrix();
             glTranslatef( 0, -1.5, 0 );
             glRotatef( -90.0, 1.0, 0.0, 0.0 );
             glTranslatef( 0, 2, 0 );
         }

         // draw nukes and shields meters for ships
         
         glPushMatrix();
         glScalef(0.8,1,1);
         glColor3f(0,0,1);
         glTranslatef(-2.7,-1,0);

         // Draw first icons
         if(shields>0){   glutSolidSphere(0.4,3,3);   }
         if(nukes>0)
         {
             glColor3f(1,0,0);
             glTranslatef(5.4,0,0);
             glutSolidSphere(0.4,3,3);
             glTranslatef(-5.4,0,0);
             glColor3f(0,0,1);
         }
         glTranslatef(-0.5,0,1.5);

         // Draw second icons
         if(shields>1) {  glutSolidSphere(0.4,3,3);   }
         if(nukes>1)
         {
             glColor3f(1,0,0);
             glTranslatef(6.3,0,0);
             glutSolidSphere(0.4,3,3);
             glTranslatef(-6.3,0,0);
             glColor3f(0,0,1);
         }
         glTranslatef(0.5,0,1.5);

         // Draw third icons
         if(shields>2) {  glutSolidSphere(0.4,3,3);   }
         if(nukes>2)
         {
             glColor3f(1,0,0);
             glTranslatef(5.4,0,0);
             glutSolidSphere(0.4,3,3);
             glTranslatef(-5.4,0,0);
             glColor3f(0,0,1);
         }
         glPopMatrix();

         /* Draw remaining shields
         if(shields>3)
         {
            glTranslatef(0,0,1);
            glutSolidSphere(0.4,3,3);
         }
         if(shields>4)
         {
            glTranslatef(0.3,0,1);
            glutSolidSphere(0.4,3,3);
         }
         if(shields>5)
         {
            glTranslatef(0.4,0,0.8);
            glutSolidSphere(0.4,3,3);
         }*/
         glPopMatrix();

         // draw the active shield
         if(shieldTimer>maxShields-0.1)
         {
             glPushMatrix();

             glColor4f(1.0, 1.0, 1.0, 0.8-0.8*((shieldTimer-maxShields+0.1)/0.1) );
             glLineWidth( 1 );
             glTranslatef( position.getX(), position.getY(), position.getZ());
             float scale = 2.5;
             glScalef(scale,scale,scale);
             if ( shipLeftSide )
                  glRotatef( shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );
             else
                  glRotatef( -shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );

             glutWireSphere(3,15,15);
             glColor4f(0.0, 0.0, 1.0, 0.4-0.4*((shieldTimer-maxShields+0.1)/0.1) );
             glutSolidSphere(3,15,15);
             glPopMatrix();

             shieldTimer-=t;
         }
         // Draw depleted shield
         else if(shieldTimer>0.0)
         {
             glPushMatrix();
             if(shields>0)
                 glColor4f(-1.0 + 2.0*(shieldTimer/maxShields), -1.0 + 2.0*(shieldTimer/maxShields), 1.0, 0.8*(shieldTimer/maxShields) );
             else
                 glColor4f(1.0, -1.0 + 2.0*(shieldTimer/maxShields), -1.0 + 2.0*(shieldTimer/maxShields), 0.8*(shieldTimer/maxShields) );
             glLineWidth( 1 );
             glTranslatef( position.getX(), position.getY(), position.getZ());
             float scale = 2.5;
             glScalef(scale,scale,scale);
             if ( shipLeftSide )
                  glRotatef( shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );
             else
                  glRotatef( -shipTheta*180 / 3.14159, 0.0, 0.0, 1.0 );

             glutWireSphere(2,15,15);
             if(shields>0)
                 glColor4f(-1.0 + 2.0*(shieldTimer/maxShields), -1.0 + 2.0*(shieldTimer/maxShields), 1.0, 0.4*(shieldTimer/maxShields) );
             else
                 glColor4f(1.0, -1.0 + 2.0*(shieldTimer/maxShields), -1.0 + 2.0*(shieldTimer/maxShields), 0.4*(shieldTimer/maxShields) );

             glutSolidSphere(2,15,15);
             glPopMatrix();

             shieldTimer-=t;
         }
}

void Player::drawShip1(){
         glLineWidth(1);
         glColor4d(1,1,1,1);
         glBegin(GL_LINE_STRIP);
             glVertex3f(1.5,1.5,3);
             glVertex3f(1.5,1.5,1.5);
             glVertex3f(0,0,0);
             glVertex3f(-1.5,-1.5,1.5);
             glVertex3f(-1.5,-1.5,3);
         glEnd();
         glBegin(GL_LINE_STRIP);
             glVertex3f(-1.5,1.5,3);
             glVertex3f(-1.5,1.5,1.5);
             glVertex3f(0,0,0);
             glVertex3f(1.5,-1.5,1.5);
             glVertex3f(1.5,-1.5,3);
         glEnd();
         glBegin(GL_LINE_STRIP);
             glVertex3f(0,0,0);
             glVertex3f(0,0,4);
         glEnd();
         glPointSize(4);
         glColor4d(0,0,1,1);
         glBegin(GL_POINTS);
             glVertex3f(1.5,1.5,3);
             glVertex3f(1.5,-1.5,3);
             glVertex3f(-1.5,-1.5,3);
             glVertex3f(-1.5,1.5,3);
         glEnd();
         glColor4d(1,0,0,1);
         glBegin(GL_POINTS);
             glVertex3f(0,0,4);
         glEnd();
}

void Player::drawShip2(){
         glLineWidth(1);
         glColor4d(1,1,1,1);
         glBegin(GL_LINE_STRIP);
             glVertex3f(0.75,0,3);
             glVertex3f(1.25,0,1);
             glVertex3f(0,0,0);
             glVertex3f(-1.25,0,1);
             glVertex3f(-0.75,0,3);
         glEnd();
         glBegin(GL_LINE_STRIP);
             glVertex3f(0,0,0);
             glVertex3f(0,0,2.5);
         glEnd();
}

void Player::drawShip3(){
         glLineWidth(2);
           glColor3f(secondaryColour[0],secondaryColour[1],secondaryColour[2]);
           glBegin(GL_LINE_STRIP);
               glVertex3f(1,1,0);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(1.25,1.25,2.5);
               glEnd();
               glColor3f(primaryColour[0],primaryColour[1],primaryColour[2]);
               glBegin(GL_LINE_STRIP);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(-1.25,-1.25,1.25);
               glEnd();
               glColor3f(secondaryColour[0],secondaryColour[1],secondaryColour[2]);
               glBegin(GL_LINE_STRIP);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(-1.25,-1.25,2.5);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(-1,-1,0);
           glEnd();
           glColor3f(secondaryColour[0],secondaryColour[1],secondaryColour[2]);
           glBegin(GL_LINE_STRIP);
               glVertex3f(-1,1,0);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(-1.25,1.25,2.5);
               glEnd();
               glColor3f(primaryColour[0],primaryColour[1],primaryColour[2]);
               glBegin(GL_LINE_STRIP);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(1.25,-1.25,1.25);
               glEnd();
               glColor3f(secondaryColour[0],secondaryColour[1],secondaryColour[2]);
               glBegin(GL_LINE_STRIP);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1.25,-1.25,2.5);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1,-1,0);
           glEnd();
           glColor3f(primaryColour[0],primaryColour[1],primaryColour[2]);
           glBegin(GL_LINE_STRIP);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(-1.25,1.25,1.25);
           glEnd();
           
           
           glDisable(GL_DEPTH_TEST);
                      
           glColor4f(secondaryColour[0],secondaryColour[1],secondaryColour[2],0.1);
           glBegin(GL_QUADS);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(-1.25,1.25,1.25);
           glEnd();
           glBegin(GL_QUADS);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(0,0,4);
           glEnd();
           glBegin(GL_QUADS);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(0,0,4);
           glEnd();
           glBegin(GL_QUADS);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(0,0,4);
           glEnd();
           glBegin(GL_QUADS);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(0,0,4);
           glEnd();
}

void Player::drawShip4(float t){
         glColor3f(0.1,0.1,0.1);
         sphereRoll += t*2;

          glPushMatrix();
          glRotatef(sphereRoll,0,0,1);
         glEnable(GL_DEPTH_TEST);
         glLineWidth(0.5);
         glPushMatrix();
         glutWireSphere(1.21,8,8);
         glColor4f(primaryColour[0],primaryColour[1],primaryColour[2],0.5);
         glutSolidSphere(1.2,8,8);
         glPopMatrix();

         glLineWidth(1.5);
         glColor4f(0.5,0.5,0.5,1);
         glutWireTorus( 0.6, 1.5, 10, 15);
         glColor4f(secondaryColour[0],secondaryColour[1],secondaryColour[2],0.7);
         glutSolidTorus(0.6,1.5,10,15);
         
         glPopMatrix();
         glDisable(GL_DEPTH_TEST);
}

bool Player::ram() {
     if(shields>0)
     {
         SoundManager::playSoundEffect( SOUND_EFFECT::SHIELD_HIT );
         if(shields<10)
             shields--;
         shieldTimer=maxShields;
     }
     else
         return true;
     return false;
}

void Player::drawShots(float t)
{
     int i = 0;
     Vector origin;
     origin.set( 0, 1, 0 );
     bool leftSide = false;
     float dot;
     float theta;
     currentBounceRotation += t*100;
     
     int j;

     for ( i = 0; i < 100; i ++ )
     {
          // set the leftside theta stuff
          leftSide = false;
     	dot = ( float )shots[i].movement.getY() / shots[i].speed;
     	theta = acos( dot );
     	if ( shots[i].movement.getX() < 0 ) leftSide = true;

          if (shots[i].upgradeLevel != 3) shots[i].isBounce = false;
          
          if (shots[i].anyActive && shots[i].isActive == false &&shots[i].isStar == false)
          {
               for (j = 0; j < 4; j ++)
                    shots[i].ripple[j].draw(t);
          }
          
          if (shots[i].isActive && shots[i].position.getX() != 0 && shots[i].position.getY() != 0)
          {
               if (shots[i].upgradeLevel == 2)
               {
                    glPushMatrix();
               	glColor4f( 1.0, 1.0, 1.0, 1 );
               	glLineWidth( 1 );
               	glTranslatef( shots[i].position.getX(), shots[i].position.getY(), 1 );
                    
                    if ( leftSide )
               		glRotatef( theta*180 / 3.14159, 0.0, 0.0, 1.0 );
               	else
               	    glRotatef( -theta*180 / 3.14159, 0.0, 0.0, 1.0 );

                    glRotatef( -90.0, 1.0, 0.0, 0.0 );

                    glutSolidCone(1,4,4,4);
                    glPopMatrix();

                    // set ripples
                    shots[i].anyActive = false;
                    shots[i].currentExpansion = 1;
                    for (j = 0; j < 4; j++)
                    {
                         if (shots[i].ripple[j].isActive == true)
                         {
                              shots[i].anyActive = true;
                              if (shots[i].ripple[j].expander / shots[i].ripple[j].width <= shots[i].currentExpansion)
                              {
                                   shots[i].currentExpansion = shots[i].ripple[j].expander / shots[i].ripple[j].width;
                                   shots[i].newestRipple = j;
                              }
                         }
                    }
                    if (shots[i].anyActive == false) // set one
                    {
                        shots[i].ripple[0].set(shots[i].position.getX(), shots[i].position.getY(), 1, 5, 0.2, 1);
                        shots[i].ripple[0].setWake(theta, leftSide);
                        shots[i].ripple[0].color(1,1,1,0.6);
                        shots[i].anyActive = true;
                    }
                    else
                    {
                         if (shots[i].currentExpansion > 0.25)
                         {
                              if (shots[i].newestRipple == 3)
                              {
                                  shots[i].ripple[0].set(shots[i].position.getX(), shots[i].position.getY(), 1, 5, 0.2, 1);
                                  shots[i].ripple[0].setWake(theta, leftSide);
                                  shots[i].ripple[0].color(1,1,1,0.6);
                              }
                              else
                              {
                                  shots[i].ripple[shots[i].newestRipple + 1].set(shots[i].position.getX(), shots[i].position.getY(), 1, 5, 0.2, 1);
                                  shots[i].ripple[shots[i].newestRipple + 1].color(1,1,1,0.6);
                                  shots[i].ripple[shots[i].newestRipple + 1].setWake(theta, leftSide);
                              }
                         }
                    }
                    for (j = 0; j < 4; j ++)
                         shots[i].ripple[j].draw(t);
               }

               else if (shots[i].upgradeLevel == 3)
               {
                    shots[i].isBounce = true;
                    
               	glPushMatrix();
               	glTranslatef(shots[i].position.getX(), shots[i].position.getY(), 1);

                    glRotatef(currentBounceRotation/5, 1, 1, 0);

               	glColor3f(1,0,0);
               	glTranslatef(-1,0,0);
               	glutSolidSphere(1,8,8);

               	glColor3f(0,1,0);
               	glTranslatef(1,1,0);
               	glutSolidSphere(1,8,8);

               	glColor3f(0,0,1);
               	glTranslatef(1,-1,0);
               	glutSolidSphere(1,8,8);

               	glColor3f(1,0,1);
               	glTranslatef(-1,-1,0);
               	glutSolidSphere(1,8,8);

               	glColor3f(0,1,1);
               	glTranslatef(0,1,-1);
               	glutSolidSphere(1,8,8);

               	glColor3f(1,1,0);
               	glTranslatef(0,0,2);
               	glutSolidSphere(1,8,8);

                	glPopMatrix();
               }
               
               else if (shots[i].upgradeLevel == 4) // Shooting star
               {
                    shots[i].starTimer += t;

                    // set the falling star

                    glColor4f(0.9,0.9,0.2,shots[i].starTimer/15);

                    Vector tempDir;
                    tempDir.set(0,30,0);
                    glPushMatrix();
                    glLineWidth(3);
                    glTranslatef(shots[i].starPosition.getX(), shots[i].starPosition.getY(),1);
                    if (shots[i].starTimer < 30)
                    {
                         glPushMatrix();
                              tempDir.multiply(1-(shots[i].starTimer/30));
                              glRotatef(-shots[i].starTimer*4,0,0,1);
                              glBegin(GL_LINE_LOOP);
                              glVertex3f(tempDir.getX(),tempDir.getY(),0);
                              tempDir.rotate('z',3.142*4/5);
                              glVertex3f(tempDir.getX(),tempDir.getY(),0);
                              tempDir.rotate('z',3.142*4/5);
                              glVertex3f(tempDir.getX(),tempDir.getY(),0);
                              tempDir.rotate('z',3.142*4/5);
                              glVertex3f(tempDir.getX(),tempDir.getY(),0);
                              tempDir.rotate('z',3.142*4/5);
                              glVertex3f(tempDir.getX(),tempDir.getY(),0);
                              tempDir.rotate('z',3.142*4/5);
                              glVertex3f(tempDir.getX(),tempDir.getY(),0);
                              tempDir.rotate('z',3.142*4/5);
                              glEnd();

                         glPopMatrix();
                    }
                    glPopMatrix();

                    if (shots[i].starPosition.getZ() > 1) // neeeeeeeeeeeeeeeeeeeeeeeer
                    {
                         glColor3f(0.9,0.9,0.2);
                         shots[i].starPosition.set(shots[i].starPosition.getX(),shots[i].starPosition.getY(), 600-shots[i].starTimer*25);
                         glPushMatrix();
                         glTranslatef(shots[i].starPosition.getX(), shots[i].starPosition.getY(), shots[i].starPosition.getZ());
                         glutSolidSphere(4,15,15);
                         glutSolidCone(4,75,7,7);
                         glPopMatrix();
                    }
                    else if (shots[i].starPosition.getZ() <= 1 && shots[i].isShrap == false)  // Kaboom!
                    {
                         shots[i].ripple[0].set(shots[i].starPosition.getX(), shots[i].starPosition.getY(), 1, 40, 1.5, 15);
                         shots[i].ripple[0].color( 1, 1, 1, 0.4 );
                         shots[i].ripple[0].detail(30);

                         shots[i].explosion.setNumberParticles(20);
                         shots[i].explosion.setPosition(shots[i].starPosition.getX(), shots[i].starPosition.getY(), 1);
                         shots[i].explosion.setParticleSize(4.0);
                         shots[i].explosion.setDuration(50);
                         shots[i].explosion.setRed(1);
                         shots[i].explosion.setGreen(1);
                         shots[i].explosion.setBlue(1);
                         shots[i].explosion.setSize(40);
                         shots[i].explosion.setDrawLightFlare(true);
                         shots[i].explosion.setLightFlareAlpha(0.5);
                         shots[i].explosion.initializeExplosion(shots[i].starTimer);
                         shots[i].isShrap = true;
                    }
                    else if (shots[i].isShrap)
                    {
                        shots[i].ripple[0].draw(t);
                        shots[i].explosion.drawExplosion(shots[i].starTimer);
                    }
                    else if (shots[i].explosion.isActive() == false)
                    {
                         shots[i].isActive=false;
                         shots[i].isShrap = false;
                    }
                    
               }

               else if(shipType == 3 && shots[i].upgradeLevel <= 1)
               {
                    glPushMatrix();
               	glColor4f( 1.0, 0.0, 0.0, 0.8 );
               	glLineWidth( 1 );
               	glTranslatef( shots[i].position.getX(), shots[i].position.getY(), 1 );
               	if ( leftSide )
               	    glRotatef( theta*180 / 3.14159, 0.0, 0.0, 1.0 );
               	else
               	    glRotatef( -theta*180 / 3.14159, 0.0, 0.0, 1.0 );
               	glRotatef( -90.0, 1.0, 0.0, 0.0 );
               	glutWireCone( 1, 2, 4, 1 );
               	glPopMatrix();
               }
               else if(shipType == 4 && shots[i].upgradeLevel <= 1)
               {
                   glPushMatrix();
                   glLineWidth( 1 );
                   glTranslatef( shots[i].position.getX(), shots[i].position.getY(), 1 );
                   glColor4f( 1.0, 1.0, 0.0, 0.3 );
                   glutSolidSphere(1.25, 10, 10 );
                   glColor4f( 1.0, 1.0, 0.0, 0.4 );
                   glutSolidSphere(0.75, 10, 10 );
                   glColor4f( 1.0, 1.0, 0.0, 0.6 );
                   glutSolidSphere(0.5, 10, 10 );
                   glColor4f( 1.0, 1.0, 0.0, 0.8 );
                   glutSolidSphere(0.25, 10, 10 );
                   glPopMatrix();
               }
          }
     }
}

// Shoots weapon from ship to mouse x/y coordinate
void Player::shoot( GLint x, GLint y ) {
     if ( shootingNow && reloadTimer <= 0.0 ) {

          shots[shotCounter].setShot( position.getX(), position.getY(), x, y );
          shots[shotCounter].upgradeLevel = 0;
          shotCounter ++;

          if ( shotCounter == 100 )
               shotCounter = 0;

           SoundManager::playSoundEffect( SOUND_EFFECT::SHOT );

          reloadTimer = reloadTime/rof;
     }
     
     
     else if ( shootingSpec && reloadTimer <= 0.0 )
     {
          if (upgradeLevel > 0)  
              if(specialShots<1000)
                  specialShots --;
          
          if (specialShots == -1)
          {
               getUpgrade(0);
          }

          shots[shotCounter].setShot( position.getX(), position.getY(), x, y );
          shots[shotCounter].upgradeLevel = upgradeLevel;
          
          if (upgradeLevel == 4)
          {
               shots[shotCounter].isStar = true;
               shots[shotCounter].position.set(-1,-1,-1);
               shots[shotCounter].movement.set(0,0,0);
                SoundManager::playSoundEffect( SOUND_EFFECT::NUKE );
          }
          else if (upgradeLevel == 2){
             shots[shotCounter].isPenetrating = true;
             SoundManager::playSoundEffect( SOUND_EFFECT::PENETRATING_SHOT );
            }
          shotCounter ++;

          
          if ( shotCounter == 100 )
               shotCounter = 0;

          

          if(upgradeLevel==1) // spread shot
          {
              SoundManager::playSoundEffect( SOUND_EFFECT::SHOT );
              float angle=15.0*3.14159/180.0;
              shots[shotCounter].setShot( position.getX(), position.getY(), cos(angle)*x - sin(angle)*y, sin(angle)*x+cos(angle)*y );
              shotCounter ++;
              if ( shotCounter == 100 )
                   shotCounter = 0;
              angle = -angle;
              shots[shotCounter].setShot( position.getX(), position.getY(),  cos(angle)*x - sin(angle)*y, sin(angle)*x+cos(angle)*y );
              shotCounter ++;
              if ( shotCounter == 100 )
                   shotCounter = 0;
          }
    

          if(upgradeLevel==0){
            SoundManager::playSoundEffect( SOUND_EFFECT::SHOT );
          }
          if(upgradeLevel==3){
            SoundManager::playSoundEffect( SOUND_EFFECT::SHOT );
          }
          
          reloadTimer = reloadTime/rof;
     }
}

// Shoots nuke from ship to mouse x/y coordinate
void Player::shootNuke( GLint x, GLint y ) {
     if (nukes > 0){
             if(shipType==3){
                 nuke[nukeCounter].setNuke( position.getX(), position.getY(), direction.getX(), direction.getY(), movement.getX(),movement.getY(), 0);
                 SoundManager::playSoundEffect(SOUND_EFFECT::NUKE);
            }else if(shipType==4){
                 nuke[nukeCounter].setNuke( position.getX(), position.getY(), 0, 0, 0,0, 5);
                 SoundManager::playSoundEffect(SOUND_EFFECT::LAY_MINE);
            }
             if(nukes<1000)
                 nukes--;
             nuke[nukeCounter].isActive = true;
             nukeCounter++;
             if(nukeCounter==100)
                 nukeCounter=0;
     }
}

// Shoot the shots
int Player::moveShots(float t, float explosionTimer, Drone enemies[], FragMine parents[], Factory factories[], FragBoss fragBosses[], int numberOfEnemies, int numberOfParents, int numberOfFactories, int numberOfFragBosses) {
     int i;
     int score=0;
     for ( i = 0; i < 100; i ++ )
     {
         score+=shots[i].updateShot(t, explosionTimer, enemies, parents, factories, fragBosses, numberOfEnemies, numberOfParents, numberOfFactories, numberOfFragBosses);
     }
     return score;
}

// Move the nukes
int Player::moveNuke(float t, float explosionTimer, Drone enemies[], FragMine parents[], Factory factories[], FragBoss fragBosses[], int numberOfEnemies, int numberOfParents, int numberOfFactories, int numberOfFragBosses) {
     int i;
     int score=0;
     int lastScore=0;
     for ( i = 0; i < 100; i ++ ) {
         score+=nuke[i].updateNuke(t, explosionTimer, enemies, parents, factories, fragBosses, numberOfEnemies, numberOfParents, numberOfFactories, numberOfFragBosses);
         if (score>lastScore)
         {
             cameraShake = true;
             lastScore=score;
             Vector push;

             push.set(position.getX()-nuke[i].position.getX(),position.getY()-nuke[i].position.getY(),0.0);
             push.normalize();

             float distance=pow(pow(position.getX()-nuke[i].position.getX(),2.0)+pow(position.getY()-nuke[i].position.getY(),2.0),0.5);

             if(distance<75.0)
             {
                  push.multiply(1-(distance/75.0));
                  movement.add(push);
             }
         }
     }
/*
       if (score>0)
          nukeCounter--;
*/
     return score;
}

// Shoot the shots
void Player::drawNuke( float t ) {
     int i;
     for ( i = 0; i < 100; i ++ ) {
         nuke[i].drawNuke(t);
     }
}

//rotates the player to the left using direction vector
void Player::rotateLeft( float t ) {
     float spinAngle = turnSpeed * t;
     float newX = cos( spinAngle ) * direction.getX() - sin( spinAngle ) * direction.getY();
     float newY = sin( spinAngle ) * direction.getX() + cos( spinAngle ) * direction.getY();
     direction.set( newX, newY, direction.getZ() );
}

//rotates the player to the right using direction vector
void Player::rotateRight( float t ) {
     float spinAngle = -turnSpeed * t;
     float newX = cos( spinAngle ) * direction.getX() - sin( spinAngle ) * direction.getY();
     float newY = sin( spinAngle ) * direction.getX() + cos( spinAngle ) * direction.getY();
     direction.set( newX, newY, direction.getZ() );

}

void Player::drawPropulsion(const GLuint& texture, float t, float t2, bool playerDeath){
    if(!playerDeath)
    {
        if (shipType == 3) propulsion.updatePropulsion(t, position, direction, boolAccelerating, boolAcceleratingBack);
        if (shipType == 4) propulsion.updateRipples(t, position, boolAccelerating || boolAcceleratingBack || boolTurningLeft || boolTurningRight, 0.8, 0.8, 0.8);
    }
    else
    {
        if (shipType == 3) propulsion.updatePropulsion(t, position, direction, false, false);
        if (shipType == 4) propulsion.updateRipples(t, position, false, 0.8, 0.8, 0.8);
    }
}

void Player::gameOver(){
     position.set ( 100.0, 75.0, 1.0 );
     movement.set ( 0, 0, 0 );
     direction.set ( 0, 1, 0 );
     currentRotation.set( 0, 0, 0);
     sphereRoll = 0;
     acceleration = 0.03;
     maxVelocity = 3;
     dampening = 0.97; // this is a great tool for modifying gameplay
     upgradeLevel=0;
     boolTurningLeft = false;
     boolTurningRight = false;
     boolAccelerating = false;
     boolAcceleratingBack = false;
     shotCounter = 0;
     shootingNow = false;
     reloadTimer = 0;
     reloadTime = 13;
     rof = 2;
     shields = 3;
     nukes = 3;
     maxShields=40.0;
     cameraShake = false;
     int i;
     for ( i = 0; i < 100; i ++ ) {
         nuke[i].isActive=false;
         nuke[i].isShrap=false;
         shots[i].isActive=false;
         shots[i].isShrap=false;
     }
}
