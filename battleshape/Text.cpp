/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Text.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Text class --------------------
*/

#include "Text.h"

/*
-------------------- Constructor for the Text class --------------------
*/
Text::Text() {

}

/*
-------------------- Destructor for the Text class --------------------
*/
Text::~Text() {

}

bool Text::drawText(char text[], int numberOfCharacters, float x, float y, float z, float size, float spacer)
{
     int i;
     glLineWidth(size+1);
     glPushMatrix();
     glTranslatef(x,y,z);
     glScalef(size,size,size);

     for (i = 0; i < numberOfCharacters; i ++)
     {
          if (text[i] == 'a')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0, 0, 0);
               glVertex3f(0, 7.5, 0);
               glVertex3f(5, 7.5, 0);
               glVertex3f(5, 0, 0);
               glVertex3f(3.5, 0, 0);
               glVertex3f(3.5, 3, 0);
               glVertex3f(1.5, 3, 0);
               glVertex3f(1.5, 0, 0);
               glEnd();
               
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5,4.5,0);
               glVertex3f(1.5,6,0);
               glVertex3f(3.5,6,0);
               glVertex3f(3.5,4.5,0);
               glEnd();
          }
          else if (text[i] == 'b')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(4.5,7.5,0);
               glVertex3f(5,7,0);
               glVertex3f(5,4,0);
               glVertex3f(4.5,3.5,0);
               glVertex3f(5,3,0);
               glVertex3f(5,0.5,0);
               glVertex3f(4.5,0,0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5,1.5,0);
               glVertex3f(1.5,3,0);
               glVertex3f(3.5, 3, 0);
               glVertex3f(3.5, 1.5, 0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5,4,0);
               glVertex3f(1.5,5.5,0);
               glVertex3f(3.5, 5.5, 0);
               glVertex3f(3.5, 4, 0);
               glEnd();
          }
          else if (text[i] == 'c')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,5.5,0);
               glVertex3f(2,5.5,0);
               glVertex3f(2,2,0);
               glVertex3f(5,2,0);
               glVertex3f(5,0,0);
               glEnd();
          }
          else if (text[i] == 'd')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(5,0,0);
               glVertex3f(5,7.5,0);
               glVertex3f(0,7.5,0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 1.5, 0);
               glVertex3f(3.5, 1.5, 0);
               glVertex3f(3.5, 6, 0);
               glVertex3f(1.5, 6, 0);
               glEnd();
          }
          else if (text[i] == 'e')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0, 0, 0);
               glVertex3f(0, 7.5, 0);
               glVertex3f(5, 7.5, 0);
               glVertex3f(5, 6, 0);
               glVertex3f(2, 6, 0);
               glVertex3f(2, 4.5, 0);
               glVertex3f(3, 4.5, 0);
               glVertex3f(3, 3, 0);
               glVertex3f(2, 3, 0);
               glVertex3f(2, 1.5, 0);
               glVertex3f(5, 1.5, 0);
               glVertex3f(5, 0, 0);
               glEnd();
          }
          else if (text[i] == 'f')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0, 0, 0);
               glVertex3f(0, 7.5, 0);
               glVertex3f(5, 7.5, 0);
               glVertex3f(5, 6, 0);
               glVertex3f(2, 6, 0);
               glVertex3f(2, 4.5, 0);
               glVertex3f(3, 4.5, 0);
               glVertex3f(3, 3, 0);
               glVertex3f(2, 3, 0);
               glVertex3f(2,0,0);
               glEnd();
          }
          else if (text[i] == 'g')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0, 0, 0);
               glVertex3f(0, 7.5, 0);
               glVertex3f(5, 7.5, 0);
               glVertex3f(5, 5.5, 0);
               glVertex3f(2, 5.5, 0);
               glVertex3f(2, 2, 0);
               glVertex3f(3.5, 2, 0);
               glVertex3f(3.5, 3, 0);
               glVertex3f(2.5, 3, 0);
               glVertex3f(2.5, 4, 0);
               glVertex3f(5,4,0);
               glVertex3f(5,0,0);
               glEnd();
          }
          else if (text[i] == 'h')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(1.5,7.5,0);
               glVertex3f(1.5,4.5,0);
               glVertex3f(3.5,4.5,0);
               glVertex3f(3.5,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,0,0);
               glVertex3f(3.5,0,0);
               glVertex3f(3.5,3,0);
               glVertex3f(1.5,3,0);
               glVertex3f(1.5,0,0);
               glEnd();
          }
          else if (text[i] == 'i')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 0, 0);
               glVertex3f(1.5, 7.5, 0);
               glVertex3f(3.5, 7.5, 0);
               glVertex3f(3.5, 0, 0);
               glEnd();
          }
          else if (text[i] == 'j')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(1,0,0);
               glVertex3f(5,0,0);
               glVertex3f(5,7.5,0);
               glVertex3f(3.5,7.5,0);
               glVertex3f(3.5,2,0);
               glVertex3f(2.5,2,0);
               glVertex3f(2.5,3.5,0);
               glVertex3f(1,3.5,0);
               glEnd();
          }
          else if (text[i] == 'k') 
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(2,7.5,0);
               glVertex3f(2,4.5,0);
               glVertex3f(4,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(3,4.5,0);
               glVertex3f(5,0,0);
               glVertex3f(4,0,0);
               glVertex3f(2,3.5,0);
               glVertex3f(2,0,0);
               glEnd();          
          }
          else if (text[i] == 'l') 
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(2,7.5,0);
               glVertex3f(2,2,0);
               glVertex3f(5,2,0);
               glVertex3f(5,0,0);
               glEnd();                 
          }
          else if (text[i] == 'm') 
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,0,0);
               glVertex3f(3.5,0,0);
               glVertex3f(3.5,5,0);
               glVertex3f(2.5,4,0);
               glVertex3f(1.5,5,0);
               glVertex3f(1.5,0,0);
               glEnd();                         
          }
          else if (text[i] == 'n') 
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(2,7.5,0);
               glVertex3f(3.5,3,0);
               glVertex3f(3.5,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,0,0);
               glVertex3f(2.5,0,0);
               glVertex3f(1,5,0);
               glVertex3f(1,0,0);
               glEnd();            
          }
          else if (text[i] == 'o') 
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,0,0);
               glEnd();    
               
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5,2,0);
               glVertex3f(1.5,5.5,0);
               glVertex3f(3.5,5.5,0);
               glVertex3f(3.5,2,0);
               glEnd();            
        
          }
          else if (text[i] == 'p') 
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,3,0);
               glVertex3f(2,3,0);
               glVertex3f(2,0,0);
               glEnd();    
               
               glBegin(GL_LINE_LOOP);
               glVertex3f(2,4.5,0);
               glVertex3f(2,6,0);
               glVertex3f(4,6,0);
               glVertex3f(4,4.5,0);
               glEnd();           
          }
          else if (text[i] == 'q') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(0,0,0);
              glVertex3f(0,7.5,0);
              glVertex3f(4,7.5,0);
              glVertex3f(4,2,0);
              glVertex3f(5,0,0);
              glVertex3f(4,-2,0);
              glVertex3f(3,0,0);
              glEnd();   
              
              glBegin(GL_LINE_LOOP);
              glVertex3f(1.5,2,0);
              glVertex3f(1.5,5,0);
              glVertex3f(2.5,5,0);
              glVertex3f(2.5,2,0);
              glEnd();              
          }
          else if (text[i] == 'r') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(0, 0,0);
              glVertex3f(0, 7.5,0);
              glVertex3f(5, 7.5,0);
              glVertex3f(5, 3.5,0);
              glVertex3f(3.5, 3.5,0);
              glVertex3f(5, 0,0);
              glVertex3f(3.5, 0, 0);
              glVertex3f(2, 3.5, 0);
              glVertex3f(2, 0, 0);
              glEnd();
              
              glBegin(GL_LINE_LOOP);
              glVertex3f(1.5, 4.5, 0);
              glVertex3f(1.5, 6, 0);
              glVertex3f(3.5, 6, 0);
              glVertex3f(3.5, 4.5, 0);
              glEnd();               
          }
          else if (text[i] == 's') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(0, 0, 0);
              glVertex3f(0, 1.5, 0);
              glVertex3f(3, 1.5, 0);
              glVertex3f(3, 3, 0);
              glVertex3f(0, 3, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(5, 5.5, 0);
              glVertex3f(2, 5.5, 0);
              glVertex3f(2, 4, 0);
              glVertex3f(5, 4, 0);
              glVertex3f(5, 0, 0);
              glEnd();               
          }
          else if (text[i] == 't') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(1.5, 0, 0);
              glVertex3f(1.5, 5, 0);
              glVertex3f(0, 5, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(5, 5, 0);
              glVertex3f(3.5, 5, 0);
              glVertex3f(3.5, 0, 0);
              glEnd();                
          }
          else if (text[i] == 'u') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(0, 0, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(1.5, 7.5, 0);
              glVertex3f(1.5, 2.5, 0);
              glVertex3f(3.5, 2.5, 0);
              glVertex3f(3.5, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(5, 0, 0);
              glEnd();                
          }
          else if (text[i] == 'v') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(2, 0, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(2, 7.5, 0);
              glVertex3f(2.5, 4, 0);
              glVertex3f(3, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(3, 0, 0);
              glEnd();           
          }
          else if (text[i] == 'w') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(0, 0, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(1.5, 7.5, 0);
              glVertex3f(1.5, 3, 0);
              glVertex3f(2.5, 4, 0);
              glVertex3f(3.5, 3, 0);
              glVertex3f(3.5, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(5, 0, 0);
              glVertex3f(3.5,0,0);
              glVertex3f(2.5,1.5,0);
              glVertex3f(1.5,0,0);
              glEnd();           
          }
          else if (text[i] == 'x') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(0, 0, 0);
              glVertex3f(1.5, 3.75, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(1.5, 7.5, 0);
              glVertex3f(2.5, 4.5, 0);
              glVertex3f(3.5, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(3.5, 3.75, 0);
              glVertex3f(5, 0, 0);
              glVertex3f(3.5, 0, 0);
              glVertex3f(2.5, 2.5, 0);
              glVertex3f(1.5, 0, 0);
              glEnd();           
          }
          else if (text[i] == 'y') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(2, 0, 0);
              glVertex3f(2, 3.75, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(2, 7.5, 0);
              glVertex3f(2.5, 5.5, 0);
              glVertex3f(3, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(3, 3.75, 0);
              glVertex3f(3, 0, 0);
              glEnd();           
          }
          else if (text[i] == 'z') 
          {
              glBegin(GL_LINE_LOOP);
              glVertex3f(5, 0, 0);
              glVertex3f(0, 0, 0);
              glVertex3f(3, 6, 0);
              glVertex3f(0, 6, 0);
              glVertex3f(0, 7.5, 0);
              glVertex3f(5, 7.5, 0);
              glVertex3f(2, 2, 0);
              glVertex3f(5, 2, 0);
              glEnd();           
          }
          else if (text[i] == '0')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(5,0,0);
               glVertex3f(5,7.5,0);
               glVertex3f(0,7.5,0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 1.5, 0);
               glVertex3f(3.5, 1.5, 0);
               glVertex3f(3.5, 6, 0);
               glVertex3f(1.5, 6, 0);
               glEnd();
          }
          else if (text[i] == '1')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(2.5, 0 ,0);
               glVertex3f(2.5, 5, 0);
               glVertex3f(1.5, 5, 0);
               glVertex3f(1.5, 7.5, 0);
               glVertex3f(4, 7.5, 0);
               glVertex3f(4, 0, 0);
               glEnd();
          }
          else if (text[i] == '2')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0, 0, 0);
               glVertex3f(5, 0, 0);
               glVertex3f(5, 1.5, 0);
               glVertex3f(1.5, 1.5, 0);
               glVertex3f(1.5, 3, 0);
               glVertex3f(5, 3, 0);
               glVertex3f(5, 7.5, 0);
               glVertex3f(0, 7.5, 0);
               glVertex3f(0, 6, 0);
               glVertex3f(3.5, 6, 0);
               glVertex3f(3.5, 4.5, 0);
               glVertex3f(0, 4.5, 0);
               glEnd();
          }
          else if (text[i] == '3')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0, 0, 0);
               glVertex3f(5,0,0);
               glVertex3f(5,7.5,0);
               glVertex3f(0,7.5,0);
               glVertex3f(0,6,0);
               glVertex3f(3.5, 6,0);
               glVertex3f(3.5, 4.5, 0);
               glVertex3f(2, 4.5, 0);
               glVertex3f(2, 3, 0);
               glVertex3f(3.5,3,0);
               glVertex3f(3.5,1.5,0);
               glVertex3f(0, 1.5, 0);
               glEnd();
          }
          else if (text[i] == '4')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(3.5,0,0);
               glVertex3f(3.5,3,0);
               glVertex3f(0,3,0);
               glVertex3f(0,7.5,0);
               glVertex3f(1.5,7.5,0);
               glVertex3f(1.5,4.5,0);
               glVertex3f(3.5,4.5,0);
               glVertex3f(3.5,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,0,0);
               glEnd();
          }
          else if (text[i] == '5')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0, 0, 0);
               glVertex3f(0, 1.5, 0);
               glVertex3f(3, 1.5, 0);
               glVertex3f(3, 3, 0);
               glVertex3f(0, 3, 0);
               glVertex3f(0, 7.5, 0);
               glVertex3f(5, 7.5, 0);
               glVertex3f(5, 5.5, 0);
               glVertex3f(2, 5.5, 0);
               glVertex3f(2, 4, 0);
               glVertex3f(5, 4, 0);
               glVertex3f(5, 0, 0);
               glEnd();
          }
          else if (text[i] == '6')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5, 5.5, 0);
               glVertex3f(1.5, 5.5, 0);
               glVertex3f(1.5, 4, 0);
               glVertex3f(5, 4, 0);
               glVertex3f(5, 0, 0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 1, 0);
               glVertex3f(1.5, 2.5, 0);
               glVertex3f(3.5, 2.5, 0);
               glVertex3f(3.5, 1, 0);
               glEnd();
          }
          else if (text[i] == '7')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(2,0,0);
               glVertex3f(5, 5, 0);
               glVertex3f(5, 7.5, 0);
               glVertex3f(0, 7.5, 0);
               glVertex3f(0, 5, 0);
               glVertex3f(3, 5, 0);
               glEnd();
          }
          else if (text[i] == '8')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(0,7.5,0);
               glVertex3f(5,7.5,0);
               glVertex3f(5,0,0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5,1.5,0);
               glVertex3f(1.5,3,0);
               glVertex3f(3.5, 3, 0);
               glVertex3f(3.5, 1.5, 0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5,4,0);
               glVertex3f(1.5,5.5,0);
               glVertex3f(3.5, 5.5, 0);
               glVertex3f(3.5, 4, 0);
               glEnd();
          }
          else if (text[i] == '9')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(0,0,0);
               glVertex3f(5,0,0);
               glVertex3f(5,7.5,0);
               glVertex3f(0,7.5,0);
               glVertex3f(0,3.5,0);
               glVertex3f(3.5,3.5,0);
               glVertex3f(3.5,1.5,0);
               glVertex3f(0, 1.5,0);
               glEnd();
               glBegin(GL_LINE_LOOP);
               glVertex3f(1,4.5,0);
               glVertex3f(1,6,0);
               glVertex3f(3.5, 6, 0);
               glVertex3f(3.5, 4.5, 0);
               glEnd();
          }
          else if (text[i] == ':')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 4, 0);
               glVertex3f(1.5, 6, 0);
               glVertex3f(3.5, 6, 0);
               glVertex3f(3.5, 4, 0);
               glEnd();

               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 1, 0);
               glVertex3f(1.5, 3, 0);
               glVertex3f(3.5, 3, 0);
               glVertex3f(3.5, 1, 0);
               glEnd();
          }
          else if (text[i] == '!')
          {
               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 3, 0);
               glVertex3f(1.5, 7, 0);
               glVertex3f(3.5, 7, 0);
               glVertex3f(3.5, 3, 0);
               glEnd();

               glBegin(GL_LINE_LOOP);
               glVertex3f(1.5, 0, 0);
               glVertex3f(1.5, 2, 0);
               glVertex3f(3.5, 2, 0);
               glVertex3f(3.5, 0, 0);
               glEnd();
          }
          
          else if (text[i] == ' ')
          {
           //    glTranslatef(spacer,0,0);
          }
          glTranslatef(spacer,0,0);
          
     }
     glPopMatrix();
}

bool Text::drawNumber(int number, float x, float y, float z, float size, float spacer)
{
    int numberOfCharacters;
    
    if (number < 10) numberOfCharacters = 1;
    else if (number < 100) numberOfCharacters = 2;
    else if (number < 1000) numberOfCharacters = 3;
    else if (number < 10000) numberOfCharacters = 4;
    else if (number < 100000) numberOfCharacters = 5;

    char toText[numberOfCharacters];
    sprintf( toText,"%d", number);
    drawText(toText,numberOfCharacters, x, y, z, size, spacer);
}

