/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about Upgrades.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Upgrade class --------------------
*/

#include "Upgrade.h"

/*
 -------------------- Constructors for the Upgrade class --------------------
*/
Upgrade::Upgrade() {

}

/*
 -------------------- Destructor for the Upgrade class --------------------
*/
Upgrade::~Upgrade() {
}

/*
 -------------------- Modifiers for the Upgrade class --------------------
*/

int Upgrade::initialize(int t) {
     srand(time(0)); // Seed the random numbers to time
     position.set(float((rand() % 1500))/10.0 + 25, float((rand() % 1000))/10.0 + 25,1);
     type = t;
     isActive = true;
     isShrapnel = false;
     size = 3;
     currentRotation = 0;
}

int Upgrade::updatePosition(float timer, GLfloat playerX, GLfloat playerY, GLfloat playerZ) {

     if (isActive && (position.getX() >= playerX - size && position.getX() <= playerX + size && position.getY() >= playerY - size && position.getY() <= playerY + size))
     {
          isActive = false;
          isShrapnel = true;
          return type;
     }
     return 0;
}

void Upgrade::collect() {}

void Upgrade::draw(const GLuint& sparkTexture, float t, float lastT, int shipType) {
     currentRotation += t;
     if(isActive==true && isShrapnel==false)
     {
          glPushMatrix();
             glTranslatef(position.getX(), position.getY(), position.getZ());
             glColor4f(0,0,1,0.25);
             glutSolidSphere(2,7,7);

             // electrons
             glColor3f(1,0,0);
             glPushMatrix();
             glRotatef(currentRotation*4,0,1,0);
             glTranslatef(4,0,0);
             glutSolidSphere(0.5,7,7);
             glPopMatrix();
             glPushMatrix();
             glRotatef((currentRotation+100)*6,1,0,0);
             glTranslatef(0,0,-4);
             glutSolidSphere(0.5,7,7);
             glPopMatrix();
             glPushMatrix();
             glRotatef((currentRotation+400)*5,1,0,1);
             glTranslatef(0,4,0);
             glutSolidSphere(0.5,7,7);
             glPopMatrix();
             glPushMatrix();
             glRotatef((currentRotation)*5,1,1,0);
             glTranslatef(0,0,4);
             glutSolidSphere(0.5,7,7);
             glPopMatrix();
             glPushMatrix();
             glRotatef((currentRotation+350)*5,0.1,1,0);
             glTranslatef(-4,0,0);
             glutSolidSphere(0.5,7,7);
             glPopMatrix();
             glPushMatrix();
             glRotatef((currentRotation)*5.5,1,0,0);
             glTranslatef(0,0,4);
             glutSolidSphere(0.5,7,7);
             glPopMatrix();
             
             // Spread shot
             if (type == 1)
             {
               glColor4f(1,0,0,1);
               glLineWidth(1);
               glScalef(0.75,0.75,0.75);
               glRotatef(90.0,0,1,0);
               glTranslatef(0,1,-1);
               glRotatef(-30.0,1,0,0);
               if (shipType == 3) glutWireCone( 1, 2, 4, 1 );
               if (shipType == 4) { glColor4f(1,1,0,0.9); glutSolidSphere(0.75,7,7); }

               glRotatef(60.0,1,0,0);
               glTranslatef(0,-2.5,1.5);
               if (shipType == 3) glutWireCone( 1, 2, 4, 1 );
               if (shipType == 4) { glColor4f(1,1,0,0.9); glutSolidSphere(0.75,7,7); }

               glRotatef(-30.0,1,0,0);
               glTranslatef(0,1.5,2);
               if (shipType == 3) glutWireCone( 1, 2, 4, 1 );
               if (shipType == 4) { glColor4f(1,1,0,0.9); glutSolidSphere(0.75,7,7); }
             }
             // Rail gun
             else if (type == 2)
             {
                glColor3f(1,1,1);
                glTranslatef(-2,0,0);
                glRotatef(90,0,1,0);
                glutSolidCone(1,4,4,4); 
             }
             // Bouncing shot
             else if (type == 3)
             {
                glRotatef(currentRotation*4,1,1,0);
                glScalef(0.75,0.75,0.75);
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
             }
             // Shooting stars
             else if (type == 4)
             {
                    glRotatef(currentRotation*2,0,0,1);
                    glTranslatef(0,0.6,0);
                    glLineWidth(2);
                    glScalef(1.5,2,1);
                    glColor4f(1,1,0,1);
                    glBegin(GL_LINE_LOOP);
                    glVertex3f(0,0.618,0);
                    glVertex3f(0.618,-1,0);
                    glVertex3f(-1,0,0);
                    glVertex3f(1,0,0);
                    glVertex3f(-0.618,-1,0);
                    glEnd();
               }

          glPopMatrix();
          
          // Draw tori
          glColor4f(1,1,1,0.5);
          glPushMatrix();
               glTranslatef(position.getX(), position.getY(), position.getZ());
               glScalef(1.1,1.1,1.1);
               glRotatef(currentRotation*2,1,1,0);
               glutSolidTorus(0.3,2,20,20);
          glPopMatrix();
          
          // Draw signal
          if (signal.isActive != true)
          {
               signal.set(position.getX(),position.getY(),position.getZ(), 7, 0.3, 1);
               signal.color(0,0,1,0.5);
               signal.detail(20);
          }
          else
          {
              if (signal.y == position.getX() && signal.x == position.getY()) signal.draw(t);
              explosion.setNumberParticles(75);
              explosion.setPosition(position.getX(), position.getY(), position.getZ());
              explosion.setParticleSize(3.0);
              explosion.setDuration(100);
              explosion.setRed(0.1);
              explosion.setGreen(0);
              explosion.setBlue(1);
              explosion.setSize(10);
              explosion.setDrawLightFlare(true);
              explosion.initializeExplosion(lastT);
          }
     }
     if (isActive == false && isShrapnel == true)
     {
          explosion.drawExplosion(lastT);
          glColor3f(0,1,0);
     }
}
