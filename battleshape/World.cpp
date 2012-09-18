/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the World.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the World class --------------------
*/

#include "World.h"
#include "SoundManager.h"

/*
-------------------- Constructor for the World class --------------------
*/
World::World()
{
     // Initialize World variables

     numberOfStars = 5000;
     startTime = 0;
     newTime = 0;
     gridAlphaValue = 0.1;
     gridFadeUp = true;
     currentShipRotation = 0.0;
     earthRotation = rand() % 100+100; 
     earthSize = 20;
     earthDistance = 350;
     lightTween = 0;

     // Planet texture attributes:
     mat_specular[0] = 1;
     mat_specular[1] = 1;
     mat_specular[2] = 1;
     mat_specular[3] = 1;
     mat_shininess[0] = 30.0;
     light_position[0] = -250;
     light_position[1] = 60;
     light_position[2] = -300;
     light_position[3] = 1.0;


     // Initialize the locations of regular and twinkling stars
     initializeStars();

    randomNebula1 = rand()%7+1;
    while (randomNebula1 == 3)
    {
       srand(time(0));
       randomNebula1 = rand()%7 + 1;
    }
    randomNebula2 = rand()%7 + 1; 
    while (randomNebula2 == 3 || randomNebula2 == randomNebula1)
    {
        srand(time(0));
        randomNebula2 = rand()%7 + 1;
    }

        
    nebula1Origin[0] = 400 + rand() % 20;
    nebula1Origin[1] = 60 + rand() % 15;
    nebula1Origin[2] = -1000;

    nebula2Origin[0] = -270 + rand() % 20;
    nebula2Origin[1] = 60 + rand() % 20;
    nebula2Origin[2] = -1000;
    
    nebula1Size = 250;
    nebula2Size = 250;
}

/*
-------------------- Destructor for the World class --------------------
*/
World::~World() {

}

/*
-------------------- Methods for the World class --------------------
*/

// Draw the random nebula texture at the back of the clipping pane
void World::drawNebulas(const GLuint& texture1, const GLuint& texture2, const GLuint& texture3, const GLuint& texture4, const GLuint& texture5, const GLuint& texture6, const GLuint& texture7,  float t)
{
//     printf("%d",randomNebula1);
     
     glColor3f(1,1,1);

     // Nebula 1
     glEnable(GL_TEXTURE_2D);
     if (randomNebula1 == 1) glBindTexture(GL_TEXTURE_2D, texture1);
     else if (randomNebula1 == 2) glBindTexture(GL_TEXTURE_2D, texture2);
     else if (randomNebula1 == 3) glBindTexture(GL_TEXTURE_2D, texture3);
     else if (randomNebula1 == 4) glBindTexture(GL_TEXTURE_2D, texture4);
     else if (randomNebula1 == 5) glBindTexture(GL_TEXTURE_2D, texture5);
     else if (randomNebula1 == 6) glBindTexture(GL_TEXTURE_2D, texture6);
     else if (randomNebula1 == 7) glBindTexture(GL_TEXTURE_2D, texture7);
     glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
          printf("%.2f ",nebula1Origin[0]); 
          printf("\n");
          printf("%.2f   ",nebula1Origin[1]);
          printf("\n");
          printf("%.2f   ",nebula1Origin[2]);
          printf("\n");
          printf("%.2f   ",nebula1Size);
          printf("\n");
          printf("\n");
          glTexCoord2d(1,1); glVertex3f(nebula1Origin[0] + nebula1Size, nebula1Origin[1] + nebula1Size, nebula1Origin[2]); // Top Right
          glTexCoord2d(0,1); glVertex3f(nebula1Origin[0] - nebula1Size, nebula1Origin[1] + nebula1Size, nebula1Origin[2]); // Top Left
          glTexCoord2d(1,0); glVertex3f(nebula1Origin[0] + nebula1Size, nebula1Origin[1] - nebula1Size, nebula1Origin[2]); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(nebula1Origin[0] - nebula1Size, nebula1Origin[1] - nebula1Size, nebula1Origin[2]); // Bottom Left
     glEnd();
     

     // Nebula2
     if (randomNebula2 == 1) glBindTexture(GL_TEXTURE_2D, texture1);
     else if (randomNebula2 == 2) glBindTexture(GL_TEXTURE_2D, texture2);
     else if (randomNebula2 == 3) glBindTexture(GL_TEXTURE_2D, texture3);
     else if (randomNebula2 == 4) glBindTexture(GL_TEXTURE_2D, texture4);
     else if (randomNebula2 == 5) glBindTexture(GL_TEXTURE_2D, texture5);
     else if (randomNebula2 == 6) glBindTexture(GL_TEXTURE_2D, texture6);
     else if (randomNebula2 == 7) glBindTexture(GL_TEXTURE_2D, texture7);
     glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
          glTexCoord2d(1,1); glVertex3f(nebula2Origin[0] + nebula2Size, nebula2Origin[1] + nebula2Size, nebula2Origin[2]); // Top Right
          glTexCoord2d(0,1); glVertex3f(nebula2Origin[0] - nebula2Size, nebula2Origin[1] + nebula2Size, nebula2Origin[2]); // Top Left
          glTexCoord2d(1,0); glVertex3f(nebula2Origin[0] + nebula2Size, nebula2Origin[1] - nebula2Size, nebula2Origin[2]); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(nebula2Origin[0] - nebula2Size, nebula2Origin[1] - nebula2Size, nebula2Origin[2]); // Bottom Left
     glEnd();

     glDisable(GL_TEXTURE_2D);
}


// Draw the orbiting planets
void World::drawSolarSystem(const GLuint& EarthTexture, const GLuint& MoonTexture, const GLuint& MercuryTexture, const GLuint& VenusTexture, const GLuint& MarsTexture, float t)
{

    glColor3f(1,1,1);
    earthRotation += t/10;

    // Set and enable materials, lighting, and texture

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    // Solar system block
    glPushMatrix();
    glTranslatef(-250,60,-300);
    glRotatef(25,1,0,0);

         // Mercury block
         glPushMatrix();
         glRotatef(earthRotation/0.24,0,1,0);
         glTranslatef(earthDistance * 0.3,0,0);
         glRotatef(-earthRotation*0.16,0,1,0);
         glRotatef(92,1,0,0);
         GLUquadricObj* Mercury = gluNewQuadric ( );
         gluQuadricDrawStyle ( Mercury, GLU_FILL );
         gluQuadricNormals ( Mercury, GLU_SMOOTH );
         gluQuadricTexture ( Mercury, GL_TRUE );
         glBindTexture(GL_TEXTURE_2D, MercuryTexture);
         gluSphere ( Mercury, earthSize*0.38, 20, 20 );
         glPopMatrix();

         // Venus block
         glColor3f(1,0,0);
         glPushMatrix();
         glRotatef(earthRotation/0.62,0,1,0);
         glTranslatef(earthDistance * 0.72,0,0);
         glRotatef(earthRotation*0.68,0,1,0);
         glRotatef(177,1,0,0);
         GLUquadricObj* Venus = gluNewQuadric ( );
         gluQuadricDrawStyle ( Venus, GLU_FILL );
         gluQuadricNormals ( Venus, GLU_SMOOTH );
         gluQuadricTexture ( Venus, GL_TRUE );
         glBindTexture(GL_TEXTURE_2D, VenusTexture);
         gluSphere ( Venus, earthSize, 50, 50 );
         glPopMatrix();

         // Mars block
         glColor3f(1,1,1);
         glPushMatrix();
         glRotatef(earthRotation/3,0,1,0);
         glTranslatef(-earthDistance*1.5,0,0);
         glRotatef(-earthRotation,0,1,0);
         glRotatef(90,1,0,0);
         GLUquadricObj* Mars = gluNewQuadric ( );
         gluQuadricDrawStyle ( Mars, GLU_FILL );
         gluQuadricNormals ( Mars, GLU_SMOOTH );
         gluQuadricTexture ( Mars, GL_TRUE );
         glBindTexture(GL_TEXTURE_2D, MarsTexture);
         gluSphere ( Mars, earthSize/2, 20, 20 );
         glPopMatrix();

         // Earth block
         glColor3f(1,1,1);
         glPushMatrix();
         glRotatef(earthRotation,0,1,0);
         glTranslatef(earthDistance,0,0);
         glRotatef(-earthRotation,0,1,0);
         glRotatef(90,1,0,0);
         GLUquadricObj* Earth = gluNewQuadric ( );
         gluQuadricDrawStyle ( Earth, GLU_FILL );
         gluQuadricNormals ( Earth, GLU_SMOOTH );
         gluQuadricTexture ( Earth, GL_TRUE );
         glBindTexture(GL_TEXTURE_2D, EarthTexture);
         gluSphere ( Earth, earthSize, 20, 20 );

              // Moon block
              glPushMatrix();
              glRotatef(earthRotation*2,0,1,0);
              glTranslatef(earthSize*2,0,0);
              GLUquadricObj* Moon = gluNewQuadric ( );
              gluQuadricDrawStyle ( Moon, GLU_FILL );
              gluQuadricNormals ( Moon, GLU_SMOOTH );
              gluQuadricTexture ( Moon, GL_TRUE );
              glBindTexture(GL_TEXTURE_2D, MoonTexture);
              gluSphere( Moon, earthSize*0.27, 15, 15);
              glPopMatrix();
         gluDeleteQuadric ( Earth );
         glPopMatrix();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}

// Draw the sun using the basic particle texture
void World::drawSun(const GLuint& texture)
{
     glColor4f(1,1,1,1);
     glBindTexture(GL_TEXTURE_2D, texture);
     corona.setRed(1); corona.setBlue(1); corona.setGreen(1);
     corona.setPosition(-250,60,-300);
     corona.setSize(250);
     corona.drawParticle();
     corona.drawParticle();
     corona.drawParticle();
     glPushMatrix();
     glTranslatef(-250,60,-300);
     glutSolidSphere(25,20,20);
     glPopMatrix();
}

// Draw the level up message when appropriate (determined in main)
void World::drawLevelUp(float t, int level)
{
    float newTime;
    if(lightTween == 0) lightTween = t;
    else newTime = t;

    if (newTime - lightTween < 100)
    {
          glColor4f(1,0,0, (newTime - lightTween)/100);
          if (level >= 11)
          {
               glColor4f(0,1,0, (newTime - lightTween)/100);
               textHandler.drawText("you win!",9,55,75,1,2,6);
          }
          else
               textHandler.drawText("level up!",9,55,75,1,2,6);
    }
    else if (newTime - lightTween < 200)
    {
          glColor4f(1,0,0, 1);
          if (level >= 11)
          {
               glColor4f(0,1,0,1);
               textHandler.drawText("you win!",9,55,75,1,2,6);
          }
          else
               textHandler.drawText("level up!",9,55,75,1,2,6);
    }
    else if (newTime - lightTween < 300)
    {
         glColor4f(1,0,0, 1 - (newTime - lightTween-200)/100);
         if (level >= 11)
         {
               glColor4f(0,1,0, 1 - (newTime - lightTween-200)/100);
               textHandler.drawText("you win!",9,55,75,1 - 100*(newTime - lightTween-200)/100,2,6);
         }
         else
               textHandler.drawText("level up!",9,55,75,1 - 100*(newTime - lightTween-200)/100,2,6);
     }
    else
       lightTween = 0;
}

// Draw twinkling stars
void World::drawSparkles(float t)
{
     int i;
     int startTwinkle;

     for (i = 0; i < 150; i ++)
     {
          // Randomly twinkle the sparkling stars.
          startTwinkle = rand() % 20 + 1;
          if (startTwinkle < 3) sparkleSize[i] = startTwinkle;
          else sparkleSize[i] = 0;

          glPushMatrix();
          glColor3f(1,1,1);
          glTranslatef(sparkles[i][0],sparkles[i][1],sparkles[i][2]);
          glutSolidSphere(0.75,5,5);
          glColor4f(1,1,1,0.5);
          glutSolidSphere(sparkleSize[i],7,7);
          glPopMatrix();
     }
}

// Draw regular stars
void World::drawStars(float t) {
     int i;
     float starSize;
     glColor3f(1,1,1);

     for (i = 0; i < numberOfStars; i++)
     {
          starSize = (i % 2) + 1; // modulate star size based on their index
          glPointSize(starSize);
          glBegin(GL_POINTS);
          glColor3f(1,1,1);
          glVertex3f(stars[i][0], stars[i][1], stars[i][2]);
          glEnd();
     }
     
     drawSparkles(t);
}

// Generate random star locations, called in constructor
void World::initializeStars() {

     int i, j, k;
     float dice;

     for (i = 0; i < numberOfStars; i ++)
     {
          dice = (rand() % 2000) - 1000; // x values of -500 to 500
          dice += (rand() % 100)/100;
          stars[i][0] = dice;
          dice = (rand() % 1500) - 750; // y values of -500 to 500
          dice += (rand() % 100)/100;
          stars[i][1] = dice;
          dice = (rand() % 1200)-600;  // z values of 300 to -600
          dice += (rand() % 100)/100;
          stars[i][2] = -dice;

          if (stars[i][0] > -10 && stars[i][0] < 210 && stars[i][1] > -10 && stars[i][1] < 160 && stars[i][2] < 600 && stars[i][2] > -10){
               i--;
          }
     }

     for (i = 0; i < 150; i ++)
     {
          if (i % 2 == 0) sparkleSize[i] = 2;
          else sparkleSize[i] = 4;
          dice = (rand() % 1000) - 500;
          dice += (rand() % 50)/50;
          sparkles[i][0] = dice;
          dice = (rand() % 750) - 350;
          dice += (rand() % 600)/300;
          sparkles[i][1] = dice;
          sparkles[i][2] = -300;
     }
     for (i = 140; i < 150; i ++)
     {
          sparkles[i][0] = 300 + rand() % 600;
          sparkles[i][1] = 500;
          sparkles[i][2] = 100 + rand() % 200;
     }
}

// Returns true if the grid is in a flashing transition, false otherwise
bool World::drawGrid(float t, float t2, bool flashing)
{
    glColor4f(0.0, 0.38, 0.5, 0.3);
    glLineWidth(1);

     // Fade the grid in and out for 100ms between levels
    if (flashing)
    {
         if(startTime == 0) startTime = t2;
         newTime = t2;

         if (newTime - startTime < 100)
         {
              glColor4f(0, 0.38, 0.5, (1 - (newTime - startTime) / 100)*0.3);
         }
         else if (newTime - startTime < 200)
         {
              glColor4f(0,0.38,0.5,0);
         }
         else if (newTime - startTime < 300)
         {
              glColor4f(0,0.38,0.5, ((newTime-startTime-200)/100.0)*0.3);
         }
    }

    //draw grid
    int i;
    for (i = 5; i < 200; i+= 5) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(i, 150, 0);
        glVertex3f(i, 0, 0);
        glEnd();
    }
    for (i = 5; i < 150; i+= 5) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(200, i, 0);
        glVertex3f(0, i, 0);
        glEnd();
    }

    //draw outline
    glColor4f(0.6, 0.0, 0.0, 0.8);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 0, 0);
    glVertex3f(200, 150, 0);
    glVertex3f(0, 150, 0);
    glVertex3f(0, 0, 0);
    glEnd();

    glColor4f(0.6, 0.0, 0.0, gridAlphaValue);
    glLineWidth(7);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 0, 0);
    glVertex3f(200, 150, 0);
    glVertex3f(0, 150, 0);
    glVertex3f(0, 0, 0);
    glEnd();

    if (newTime == 0 && startTime == 0) return false;
    if (newTime - startTime < 300) return true;
    else
    {
         startTime = 0;
         return false;
    }
}

// Draw the level, lives, and score above the grid
void World::drawStatus(int level, int lives, int score) {
     glColor4f(1,0,0,1);
     glLineWidth(2);

     // Level:
     glPushMatrix();
          textHandler.drawText("level:",6,0,155,0,0.5,6);       // Level text control
          textHandler.drawText("score:",6,80,155,0,0.5,6);
          textHandler.drawText("lives:",6,40,155,0,0.5,6);

          glColor3f(1,1,1);
          textHandler.drawNumber(level,20,155,0,0.5,6);
          textHandler.drawNumber(lives,60,155,0,0.5,6);
          textHandler.drawNumber(score,100,155,0,0.5,6);
     glPopMatrix();
}

// Draws the main menu screen
void World::drawStartMenu(int gameType, int shipHover, int shipSelection, bool backHover, int mouseOverValue, int primarySelection, int secondarySelection, bool checkpoint)
{
     currentShipRotation += 0.5;

     // Draw splash text
     glLineWidth(2);
     glColor3f(1, 0, 0);
     textHandler.drawText("b ttlesh pe", 11, 40, 120,0,2,5.5);
     glColor3f(1, 1, 1);
     textHandler.drawText("beta release", 12, 140, 115,0,0.3,5.5);

     // Hovering over START
     if (mouseOverValue == 1)
     {
           glColor3f(0,1,0);
           glLineWidth(1);
           glBegin(GL_LINES);
           glVertex3f(90.5,30,0);
           glVertex3f(110,30,0);
           glEnd();
           glBegin(GL_LINES);
           glVertex3f(90.5,24,0);
           glVertex3f(110,24,0);
           glEnd();
     }
     else glColor3f(1,1,1);

     textHandler.drawText("start",5,90,25,0,0.5,9);

     // Hovering over QUIT
     if (mouseOverValue == 2)
     {
           glLineWidth(1);
           glColor3f(1,0,0);
           glBegin(GL_LINES);
           glVertex3f(95,20.5,0);
           glVertex3f(104.5,20.5,0);
           glEnd();
           glBegin(GL_LINES);
           glVertex3f(95,15.5,0);
           glVertex3f(104.5,15.5,0);
           glEnd();
     }
     else glColor3f(1,1,1);

     textHandler.drawText("quit",4,94.5,16.5,0,0.4,7);

     // Hovering over CREDITS
     if (mouseOverValue == 3)
     {
           glLineWidth(1);
           glColor3f(1,1,0);
           glBegin(GL_LINES);
           glVertex3f(140.5,25,0);
           glVertex3f(155,25,0);
           glEnd();
           glBegin(GL_LINES);
           glVertex3f(140.5,21,0);
           glVertex3f(155,21,0);
           glEnd();
     }
     else glColor3f(1,1,1);

     textHandler.drawText("credits",7,140,22,0,0.3,8);

     // Hovering over CONTROLS
     if (mouseOverValue == 4)
     {
           glLineWidth(1);
           glColor3f(1,1,0);
           glBegin(GL_LINES);
           glVertex3f(45,25,0);
           glVertex3f(63,25,0);
           glEnd();
           glBegin(GL_LINES);
           glVertex3f(45,21,0);
           glVertex3f(63,21,0);
           glEnd();
     }
     else glColor3f(1,1,1);

     textHandler.drawText("controls",8,45,22,0,0.3,8);

     // Draw RESUME if the player has previously reached level 6
     if (checkpoint)
     {
          if (mouseOverValue == 5)
          {
           glLineWidth(1);
           glColor3f(0,1,0);
           glBegin(GL_LINES);
           glVertex3f(88.5,39,0);
           glVertex3f(112,39,0);
           glEnd();
           glBegin(GL_LINES);
           glVertex3f(88.5,32.5,0);
           glVertex3f(112,32.5,0);
           glEnd();
          }

           else glColor3f(0,1,1);

           textHandler.drawText("resume",6,88,34,0,0.5,9);
     }

     // draw the ships for the A in battleshape
     glColor3f(1, 1, 1);
     glLineWidth(2);
     glPushMatrix();
         glTranslatef(56.5,120,0);
         glScalef(3.2,3.8,0);
         glRotatef(-90,1,0,0);
         glBegin(GL_LINE_STRIP);
         glVertex3f(1,1,0);
         glVertex3f(1.25,1.25,1.25);
         glVertex3f(1.25,1.25,2.5);
         glVertex3f(1.25,1.25,1.25);
         glVertex3f(0,0,4);
         glVertex3f(-1.25,-1.25,1.25);
         glVertex3f(-1.25,-1.25,2.5);
         glVertex3f(-1.25,-1.25,1.25);
         glVertex3f(-1,-1,0);
         glEnd();
         glBegin(GL_LINE_STRIP);
         glVertex3f(-1,1,0);
         glVertex3f(-1.25,1.25,1.25);
         glVertex3f(-1.25,1.25,2.5);
         glVertex3f(-1.25,1.25,1.25);
         glVertex3f(0,0,4);
         glVertex3f(1.25,-1.25,1.25);
         glVertex3f(1.25,-1.25,2.5);
         glVertex3f(1.25,-1.25,1.25);
         glVertex3f(1,-1,0);
         glEnd();
         glBegin(GL_LINE_STRIP);
         glVertex3f(-1.25,1.25,1.25);
         glVertex3f(-1.25,-1.25,1.25);
         glVertex3f(1.25,-1.25,1.25);
         glVertex3f(1.25,1.25,1.25);
         glVertex3f(-1.25,1.25,1.25);
         glEnd();
     glPopMatrix();

     glPushMatrix();
         glTranslatef(133,120,0);
         glScalef(3.2,3.8,0);
         glRotatef(-90,1,0,0);
         glBegin(GL_LINE_STRIP);
         glVertex3f(1,1,0);
         glVertex3f(1.25,1.25,1.25);
         glVertex3f(1.25,1.25,2.5);
         glVertex3f(1.25,1.25,1.25);
         glVertex3f(0,0,4);
         glVertex3f(-1.25,-1.25,1.25);
         glVertex3f(-1.25,-1.25,2.5);
         glVertex3f(-1.25,-1.25,1.25);
         glVertex3f(-1,-1,0);
         glEnd();
         glBegin(GL_LINE_STRIP);
         glVertex3f(-1,1,0);
         glVertex3f(-1.25,1.25,1.25);
         glVertex3f(-1.25,1.25,2.5);
         glVertex3f(-1.25,1.25,1.25);
         glVertex3f(0,0,4);
         glVertex3f(1.25,-1.25,1.25);
         glVertex3f(1.25,-1.25,2.5);
         glVertex3f(1.25,-1.25,1.25);
         glVertex3f(1,-1,0);
         glEnd();
         glBegin(GL_LINE_STRIP);
         glVertex3f(-1.25,1.25,1.25);
         glVertex3f(-1.25,-1.25,1.25);
         glVertex3f(1.25,-1.25,1.25);
         glVertex3f(1.25,1.25,1.25);
         glVertex3f(-1.25,1.25,1.25);
         glEnd();
     glPopMatrix();

     glPushMatrix();
     glTranslatef(-2,0,0); // align the ship selection to center screen

     // If the player has selected a ship
     if (shipSelection == 3 || shipSelection == 4)
     {
         // draw colour selection boxes
         glPushMatrix();
         glTranslatef(-1.25,3,0);

          // Translate the boxes to under the UFO if UFO has been selected
         if (shipSelection == 4) glTranslatef(48.5,0,0);

         // Colour selection outline
         glPushMatrix();
         glTranslatef(70 + (primarySelection-1)*5,53,0);
         glScalef(3,4,1);
         glLineWidth(4);
         glColor4f(0,1,0,0.8);
         glBegin(GL_LINE_LOOP);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();

         // Colour selection 2 outline
         glPushMatrix();
         glTranslatef(70 + (secondarySelection-1)*5,46,0);
         glScalef(3,4,1);
         glLineWidth(4);
         glColor4f(0,1,0,0.8);
         glBegin(GL_LINE_LOOP);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();

         glPushMatrix();
         glTranslatef(70,53,0);
         glScalef(3,4,1);
         glColor3f(1,1,1);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();
         glPushMatrix();
         glTranslatef(75,53,0);
         glScalef(3,4,1);
         glColor3f(1,1,0);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();
         glPushMatrix();
         glTranslatef(80,53,0);
         glScalef(3,4,1);
         glColor3f(1,0,0);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();
         glPushMatrix();
         glTranslatef(85,53,0);
         glScalef(3,4,1);
         glColor3f(0,1,1);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();

         // secondary colours
         glPushMatrix();
         glTranslatef(70,46,0);
         glScalef(3,4,1);
         glColor3f(1,1,1);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();
         glPushMatrix();
         glTranslatef(75,46,0);
         glScalef(3,4,1);
         glColor3f(1,1,0);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();
         glPushMatrix();
         glTranslatef(80,46,0);
         glScalef(3,4,1);
         glColor3f(1,0,0);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();
         glPushMatrix();
         glTranslatef(85,46,0);
         glScalef(3,4,1);
         glColor3f(0,1,1);
         glBegin(GL_QUADS);
         glVertex3f(0,0,0);
         glVertex3f(1,0,0);
         glVertex3f(1,1,0);
         glVertex3f(0,1,0);
         glEnd();
         glPopMatrix();
         glPopMatrix();
     }

     // Ship selection
     glColor3f(1, 0.6, 0);
     textHandler.drawText("bst", 3, 75, 98, 0, 0.4, 5);

     glEnable(GL_DEPTH_TEST);
     glPushMatrix();
         glLineWidth(4);
         glTranslatef(74,73,0);
         glRotatef(25,1,0,0);
         glRotatef(-25,0,0,1);
         glRotatef(currentShipRotation,0,1,0);
         glRotatef(-90,1,0,0);
         glScalef(6,6,6);

           //Draw BST
           setColour(secondarySelection,3,shipSelection);
           glBegin(GL_LINE_STRIP);
               glVertex3f(1,1,0);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(1.25,1.25,2.5);
               glEnd();
               setColour(primarySelection,3,shipSelection);
               glBegin(GL_LINE_STRIP);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(-1.25,-1.25,1.25);
               glEnd();
               setColour(secondarySelection,3,shipSelection);
               glBegin(GL_LINE_STRIP);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(-1.25,-1.25,2.5);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(-1,-1,0);
           glEnd();
           setColour(secondarySelection,3,shipSelection);
           glBegin(GL_LINE_STRIP);
               glVertex3f(-1,1,0);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(-1.25,1.25,2.5);
               glEnd();
               setColour(primarySelection,3,shipSelection);
               glBegin(GL_LINE_STRIP);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(0,0,4);
               glVertex3f(1.25,-1.25,1.25);
               glEnd();
               setColour(secondarySelection,3,shipSelection);
               glBegin(GL_LINE_STRIP);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1.25,-1.25,2.5);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1,-1,0);
           glEnd();
           setColour(primarySelection,3,shipSelection);
           glBegin(GL_LINE_STRIP);
               glVertex3f(-1.25,1.25,1.25);
               glVertex3f(-1.25,-1.25,1.25);
               glVertex3f(1.25,-1.25,1.25);
               glVertex3f(1.25,1.25,1.25);
               glVertex3f(-1.25,1.25,1.25);
           glEnd();
           glDisable(GL_DEPTH_TEST);

           // Set colour selection of the BST
           if (shipSelection == 3)
           {
               if (primarySelection == 1) glColor4f(1,1,1,0.1);
               else if (primarySelection == 2) glColor4f(1,1,0,0.1);
               else if (primarySelection == 3) glColor4f(1,0,0,0.1);
               else if (primarySelection == 4) glColor4f(0,0,1,0.1);
           }
           else glColor4f(1,1,1,0.1);

           // Draw faded primary colour inside the BST
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
     glPopMatrix();

     // BST background mouse-over
     if (shipHover == 1 || shipSelection == 3)
     {
          if (shipSelection == 3)
          {
              glLineWidth(3);
              glColor4f(1,1,1,0.9);
          }
          else { glLineWidth(1);  glColor4f(1,1,1,0.3); }
          glBegin(GL_LINE_LOOP);
          glVertex3f(62.5,40,0);
          glVertex3f(92.5,40,0);
          glVertex3f(92.5,105,0);
          glVertex3f(62.5,105,0);
          glEnd();
     }
     
     // UFO background mouse-over
     if (shipHover == 2 || shipSelection == 4)
     {
           if (shipSelection == 4)
           {
             glLineWidth(3);
             glColor4f(1,1,1,0.9);
           }
           else {     glLineWidth(1);  glColor4f(1,1,1,0.3); }
          glBegin(GL_LINE_LOOP);
          glVertex3f(111,40,0);
          glVertex3f(141,40,0);
          glVertex3f(141,105,0);
          glVertex3f(111,105,0);
          glEnd();
     }


    //Draw UFO
    glColor3f(1, 0.6, 0);
    textHandler.drawText("ufo", 3, 123, 98, 0, 0.4, 5);

    glPushMatrix();
    glTranslatef(126,80,0);
    glRotatef(25,1,0,0);
    glRotatef(-25,0,0,1);
    glRotatef(currentShipRotation,0,1,0);
    glRotatef(-90,1,0,0);
    glScalef(6,6,6);

    glColor3f(0.1,0.1,0.1);

    // Render the UFO with the appropriate colours
    glPushMatrix();
          glEnable(GL_DEPTH_TEST);
          glLineWidth(0.5);
          glPushMatrix();
          glutWireSphere(1.51,8,8);
          if (shipSelection != 4) glColor4f(1,1,0,0.5);
          else setColour(primarySelection,4,shipSelection);
          glutSolidSphere(1.5,8,8);

          glLineWidth(1.5);
          glColor4f(0.5,0.5,0.5,1);
          glutWireTorus( 0.6, 2, 10, 15);
          setColour(secondarySelection,4,shipSelection);
          glutSolidTorus(0.6,2,10,15);

          glDisable(GL_DEPTH_TEST);
     glPopMatrix();
     glPopMatrix();
     glPopMatrix();
}

void World::drawCredits(const GLuint& logoTexture, int mouseOverValue)
{
     glColor3f(1,1,0);
     textHandler.drawText("created by:",11,40,130,0,0.8,7);
     glColor3f(1,1,1);
     textHandler.drawText("derek veenstra",14,45,120,0,0.8,7);
     textHandler.drawText("alasdair hutchinson",19,45,110,0,0.8,7);
     textHandler.drawText("james pennell",13,45,100,0,0.8,7);
     glColor3f(1,1,0);
     textHandler.drawText("special thanks:",15,40,80,0,0.8,7);
     glColor3f(1,1,1);
     textHandler.drawText("alex lague",10,45,70,0,0.8,7);

     if (mouseOverValue == 1) // back
     {
           glLineWidth(1);
           glColor3f(1,1,0);
           glBegin(GL_LINES);
           glVertex3f(145.5,27,0);
           glVertex3f(160.5,27,0);
           glEnd();
           glBegin(GL_LINES);
           glVertex3f(145.5,20.5,0);
           glVertex3f(160.5,20.5,0);
           glEnd();
     }
     else glColor3f(1,1,1);

     textHandler.drawText("back",4,145,21.5,0,0.6,7);

     if (mouseOverValue == 2) // link to site
     {
          glColor3f(0,1,1);
          glBegin(GL_LINE_LOOP);
          glVertex3f(63,60,0);
          glVertex3f(138,60,0);
          glVertex3f(138,20,0);
          glVertex3f(63,20,0);
          glEnd();
          glColor4f(0,1,1,0.1);
          glBegin(GL_QUADS);
          glVertex3f(63,60,0);
          glVertex3f(138,60,0);
          glVertex3f(138,20,0);
          glVertex3f(63,20,0);
          glEnd();
     }

     // Draw shadowcat logo
     glColor3f(1,1,1);
     glPushMatrix();
     glTranslatef(-50,-2,0);
     glScalef(1.5,1.5,1);
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, logoTexture);
     glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
          glTexCoord2d(1,1); glVertex3f(135,60,0); // Top Right
          glTexCoord2d(0,1); glVertex3f(55,60,0); // Top Left
          glTexCoord2d(1,0); glVertex3f(135,-10,0); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(55,-10,0); // Bottom Left
     glEnd();
     glPopMatrix();
     glDisable(GL_TEXTURE_2D);

}

void World::drawControls(const GLuint& mouseTexture, const GLuint& keysTexture, const GLuint& eTexture, int mouseOverValue)
{
     glColor3f(1,1,1);

     // Draw the visual aids
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, mouseTexture);
     glBegin(GL_TRIANGLE_STRIP);
          glTexCoord2d(1,1); glVertex3f(45,140,0); // Top Right
          glTexCoord2d(0,1); glVertex3f(30,140,0); // Top Left
          glTexCoord2d(1,0); glVertex3f(45,120,0); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(30,120,0); // Bottom Left
     glEnd();
     glBegin(GL_TRIANGLE_STRIP);
          glTexCoord2d(1,1); glVertex3f(45,115,0); // Top Right
          glTexCoord2d(0,1); glVertex3f(30,115,0); // Top Left
          glTexCoord2d(1,0); glVertex3f(45,95,0); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(30,95,0); // Bottom Left
     glEnd();
     glBegin(GL_TRIANGLE_STRIP);
          glTexCoord2d(1,1); glVertex3f(45,90,0); // Top Right
          glTexCoord2d(0,1); glVertex3f(30,90,0); // Top Left
          glTexCoord2d(1,0); glVertex3f(45,70,0); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(30,70,0); // Bottom Left
     glEnd();
     glBindTexture(GL_TEXTURE_2D,keysTexture);
     glBegin(GL_TRIANGLE_STRIP);
          glTexCoord2d(1,1); glVertex3f(47,65,0); // Top Right
          glTexCoord2d(0,1); glVertex3f(30,65,0); // Top Left
          glTexCoord2d(1,0); glVertex3f(47,35,0); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(30,35,0); // Bottom Left
     glEnd();
     glBindTexture(GL_TEXTURE_2D,eTexture);
     glBegin(GL_TRIANGLE_STRIP);
          glTexCoord2d(1,1); glVertex3f(47,40,0); // Top Right
          glTexCoord2d(0,1); glVertex3f(30,40,0); // Top Left
          glTexCoord2d(1,0); glVertex3f(47,10,0); // Bottom Right
          glTexCoord2d(0,0); glVertex3f(30,10,0); // Bottom Left
     glEnd();
     glDisable(GL_TEXTURE_2D);

     // Draw visual aid arrows
     glColor3f(0,1,1);
     glPushMatrix();
     glTranslatef(37,117,2);
     glRotatef(90,1,0,0);
     glutSolidCone(1,4,8,8);
     glPopMatrix();

     glPushMatrix();
     glTranslatef(40,92,2);
     glRotatef(90,1,0,0);
     glutSolidCone(1,4,8,8);
     glPopMatrix();

     glDisable(GL_DEPTH_TEST);

     glPushMatrix();
     glTranslatef(3,0,0);

     glColor3f(0,1,1);
     textHandler.drawText("aim",3,52,127,0,0.6,6);
     textHandler.drawText("shoot",5,50,102,0,0.6,6);
     textHandler.drawText("shoot",5,50,80,0,0.6,6);
     textHandler.drawText("upgrades",8,46,73,0,0.5,6.5);
     textHandler.drawText("move",4,52,47,0,0.6,6);
     textHandler.drawText("nuke",4,52,23,0,0.6,6);

     glColor3f(1,1,1);
     textHandler.drawText("with the mouse",14,80,127,0,0.6,6);
     textHandler.drawText("with left click",15,80,102,0,0.6,6);
     textHandler.drawText("with right click",16,80,77,0,0.6,6);
     textHandler.drawText("with wasd keys",14,80,47,0,0.6,6);
     textHandler.drawText("with the e key",14,80,23,0,0.6,6);
     glPopMatrix();

     // hovering over BACK
     if (mouseOverValue == 1) 
     {
           glLineWidth(1);
           glColor3f(1,1,0);
           glBegin(GL_LINES);
           glVertex3f(145.5,27,0);
           glVertex3f(160.5,27,0);
           glEnd();
           glBegin(GL_LINES);
           glVertex3f(145.5,20.5,0);
           glVertex3f(160.5,20.5,0);
           glEnd();
     }
     else glColor3f(1,1,1);

     textHandler.drawText("back",4,145,21.5,0,0.6,7);

}

// Draws the game over menu
void World::drawGameOver(int level, long int score, int lives, bool contHover, bool didQuit)
{
     glPushMatrix();
     glTranslatef(35,100,0); // Translate to the centre of the screen
     glLineWidth(2);

     // If the player quits or loses all their lives, they lose. Otherwise they have won.
     if(lives < 0 || didQuit)
     {
          glColor3f(1,0,0);
          textHandler.drawText("game over", 9, 5, 20, 0, 2, 7);
     }
     else
     {
          glColor3f(0,1,0);
          textHandler.drawText("you win!", 8, 12.5, 20, 0, 2, 7);
     }

     // Report final statistics
     glColor3f(0.6,0.6,1);
     textHandler.drawText("level:", 6, 50, -5, 10, 0.5, 7);
     textHandler.drawText("score:", 6, 50, -15, 10, 0.5, 7);
     textHandler.drawText("lives:", 6, 50, -25, 10, 0.5, 7);
     glColor3f(1,1,1);
     textHandler.drawNumber(level, 80, -5, 10, 0.5, 7);
     textHandler.drawNumber(score, 80, -15, 10, 0.5, 7);
     if(lives >= 0)
        textHandler.drawNumber(lives, 80, -25, 10, 0.5, 7);
     else
        textHandler.drawNumber(0, 80, -25, 10, 0.5, 7);


     glColor3f(0,1,0);
     textHandler.drawText("thanks for playing!", 19, 30,-70,0,0.5,8);

     if(!contHover)
         glColor3f(1,0,0);
     else
         glColor3f(0,1,0);

     textHandler.drawText("menu", 4, 61, -38.5, 8, 0.5, 7);
     glPopMatrix();
}

// This function sets the glColor state depending on which ship has been selected. UFO uses unique alpha values.
void World::setColour(int color, int shipType, int shipSelection)
{
     float alpha = 1;
     if (shipType == 4) alpha = 0.5;
     if (shipType == shipSelection)
     {
        if (color == 1) glColor4f(1,1,1,alpha);
        if (color == 2) glColor4f(1,1,0,alpha);
        if (color == 3) glColor4f(1,0,0,alpha);
        if (color == 4) glColor4f(0,1,1,alpha);
     }
     else if (shipType == 4 && shipSelection != 4)
     {
          if (color == 1) glColor4f(1,1,1,alpha);
     }
     else glColor4f(1,1,1,alpha);
}
