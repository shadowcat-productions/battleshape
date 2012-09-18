/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Menus.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Menus class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "Menus.h"

/*
-------------------- Constructor for the Menus class --------------------
*/
Menus::Menus() {
     iT = 0;
     initializeCoords();
}

/*
-------------------- Destructor for the Menus class --------------------
*/
Menus::~Menus() {

}

/*
-------------------- Methods for the Menus class --------------------
*/
void Menus::initializeCoords()
{
     float rot = 3.14*2/360;
     int i;
     Vector v;
     v.set(-70,0,0);
     v.rotate('z',3.141/8);
     

     for (i = 0; i < 45; i ++)
     {
          leftCoords[i][0] = v.getX();
          leftCoords[i][1] = v.getY();
          v.rotate('z',-rot);
     }

     v.multiply(1.1);
     v.rotate('z',rot);
          
     for (i = 45; i < 90; i ++)
     {
          leftCoords[i][0] = v.getX();
          leftCoords[i][1] = v.getY();
          v.rotate('z',rot);
     }
     
}

void Menus::drawPause()
{
     glColor4f(1,1,1,0.7);
     text.drawText("paused",6,-35,0,0,2,6);
}

void Menus::drawMenu(float t, int mouseOverValue)
{
          glColor3f(0,0,0);
          glDisable(GL_BLEND);
          glBegin(GL_QUADS);
          glVertex3f(-26,25,0);
          glVertex3f(26,25,0);
          glVertex3f(26,-10,0);
          glVertex3f(-26,-10,0);
          glEnd();
          glColor3f(0,1,0);
          glBegin(GL_LINE_LOOP);
          glVertex3f(-26,25,0);
          glVertex3f(26,25,0);
          glVertex3f(26,-10,0);
          glVertex3f(-26,-10,0);
          glEnd();
          glEnable(GL_BLEND);

          if (mouseOverValue != 0)
          {
          glColor4f(0,1,0,0.2);
          glPushMatrix();
          glTranslatef(0,-(mouseOverValue-1)*10,0);
          glBegin(GL_QUADS);
          glVertex3f(-26,21,0);
          glVertex3f(26,21,0);
          glVertex3f(26,13,0);
          glVertex3f(-26,13,0);
          glEnd();
          glPopMatrix();
          }

          glColor3f(0,1,0);
          text.drawText("continue",8,-12,15,1,0.5,6);
          text.drawText("abandon mission",15,-22,5,1,0.5,6);
          text.drawText("quit",4,-7,-5,1,0.5,6);

}

void Menus::drawHUD(float t, int upgradeLevel, int specialShots, int level, int lives, int score, int shipType, int shields, int nukes)
{
     iT += t;
     
     int i;

     glLineWidth(4);
     glColor3f(1,1,1);
     
     // Shields bar
     glPushMatrix();
     glScalef(1.1,3,1);
     glBegin(GL_LINE_LOOP);
     for (i = 0; i < 90; i ++) // outline
     {
          glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
     }
     glEnd();
     
     glBegin(GL_QUAD_STRIP); // fill
     glColor4f(0,0,1,0.2);
     for (i = 0; i < 45; i ++)
     {
          glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
          glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
     }
     glEnd();

     // shield bars
     if(shields>1000)
         glColor4f(1,1,0,1);
     else
         glColor4f(0,0,1,1);
     glBegin(GL_QUAD_STRIP);
     if (shields >= 3) 
     {
          for (i = 0; i < 15; i ++)
          {
             glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
             glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
          }
     }
     if (shields >= 2)
     {
          for (i = 14; i < 30; i ++)
          {
             glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
             glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
          }
     }
     if (shields >= 1)
     {
          for (i = 29; i < 45; i ++)
          {
             glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
             glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
          }
     }
     
     glEnd();
     glPopMatrix();
     
     
     // Nukes bar
     glColor3f(1,1,1);
     glPushMatrix();
     glScalef(-1.1,3,1);
     glBegin(GL_LINE_LOOP);
     for (i = 0; i < 90; i ++)
     {
          glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
     }
     glEnd();

     glBegin(GL_QUAD_STRIP); // fill
     glColor4f(1,0,0,0.2);
     for (i = 0; i < 45; i ++)
     {
          glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
          glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
     }
     glEnd();
     
     // nukes bars
     if(nukes>1000)
         glColor4f(1,1,0,1);
     else
         glColor4f(1,0,0,1);
     glBegin(GL_QUAD_STRIP);
     if (nukes >= 3) 
     {
          for (i = 0; i < 15; i ++)
          {
             glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
             glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
          }
     }
     if (nukes >= 2)
     {
          for (i = 14; i < 30; i ++)
          {
             glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
             glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
          }
     }
     if (nukes >= 1)
     {
          for (i = 29; i < 45; i ++)
          {
             glVertex3f(leftCoords[i][0], leftCoords[i][1], 0);
             glVertex3f(leftCoords[89-i][0], leftCoords[89-i][1], 0);
          }
     }
     
     glEnd();
     glPopMatrix();

     // Draw upgrade graphic

     glLineWidth(1);
     glPushMatrix();
     glTranslatef(-5,-70, 0);
     if (upgradeLevel == 0 || specialShots == 0)
     {
          if (shipType == 3)
          {
               glColor3f(1,0,0);
               glRotatef( -90.0, 1.0, 0.0, 0.0 );
          	glutWireCone( 1, 2, 4, 1 );
          }
          else if (shipType == 4)
          {
              glColor4f( 1.0, 1.0, 0.0, 0.3 );
              glutSolidSphere(1.25, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.4 );
              glutSolidSphere(0.75, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.6 );
              glutSolidSphere(0.5, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.8 );
              glutSolidSphere(0.25, 10, 10 );
          }
     }
     else if (upgradeLevel == 1)
     {
          if (shipType == 3)
          {
               glColor3f(1,0,0);
              	glRotatef( -90.0, 1.0, 0.0, 0.0 );
          	glutWireCone( 1, 2, 4, 1 );

               glPushMatrix();
               glTranslatef(-2,-2,0);
               glRotatef(-45,0,1,0);
              	glutWireCone( 1, 2, 4, 1 );
               glPopMatrix();

               glPushMatrix();
               glTranslatef(2,-2,0);
               glRotatef(45,0,1,0);
              	glutWireCone( 1, 2, 4, 1 );
               glPopMatrix();
          }
          else if (shipType == 4)
          {
              glColor4f( 1.0, 1.0, 0.0, 0.3 );
              glutSolidSphere(1.25, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.4 );
              glutSolidSphere(0.75, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.6 );
              glutSolidSphere(0.5, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.8 );
              glutSolidSphere(0.25, 10, 10 );

              glPushMatrix();
              glTranslatef(-2,-2,0);
              glColor4f( 1.0, 1.0, 0.0, 0.3 );
              glutSolidSphere(1.25, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.4 );
              glutSolidSphere(0.75, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.6 );
              glutSolidSphere(0.5, 10, 10 );
              glColor4f( 1.0, 1.0, 0.0, 0.8 );
              glutSolidSphere(0.25, 10, 10 );
              glPopMatrix();
              
              glPushMatrix();
              glTranslatef(2,-2,0);
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
     else if (upgradeLevel == 2)
     {
        glColor3f(1,1,1);
        glTranslatef(0,-2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(1,4,4,4);
     }
     else if (upgradeLevel == 3)
     {
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
     else if (upgradeLevel == 4)
     {
          Vector tempDir;
          tempDir.set(0,3,0);
          
          glColor3f(1,1,0);
          
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
     }
     glPopMatrix();
     
     // x

     glColor3f(1,1,1);
     glPushMatrix();
     glTranslatef(0,-70,0);
     glScalef(0.8,1,1);
     glBegin(GL_LINES);
     glVertex3f(-1,1,0);
     glVertex3f(1,-1,0);
     glEnd();
     glBegin(GL_LINES);
     glVertex3f(1,1,0);
     glVertex3f(-1,-1,0);
     glEnd();
     glPopMatrix();
     
     // number of shots left
     
     if (upgradeLevel == 0 || specialShots == 0)
     {
          glPushMatrix();
          glTranslatef(4,-70,0);
          glutSolidTorus(0.25,0.75,11,11);
          glTranslatef(1.4,0,0);
          glutSolidTorus(0.25,0.75,11,11);
          glPopMatrix();
     }
     else
     {
          text.drawNumber(specialShots,3,-71,0,0.4,6);
     }
     
}
