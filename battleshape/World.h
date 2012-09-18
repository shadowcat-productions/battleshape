/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the World class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the World class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Particle.h"
#include "Particle2.h"
#include "Nuke.h"
#include "Text.h"
#include "Player.h"

#ifndef World_H
#define World_H

class World
{

public:
    /*
    -------------------- Constructor for the World class --------------------
    */
    World();

    /*
    -------------------- Destructor for the World class --------------------
    */
    ~World();

    /*
     -------------------- Methods for the World class --------------------
    */
    // Randomly generate star locations
    void initializeStars();
    void drawNebulas(const GLuint& texture1, const GLuint& texture2, const GLuint& texture3, const GLuint& texture4, const GLuint& texture5, const GLuint& texture6, const GLuint& texture7, float t); // draws a nebula

    // Draws regular stars, calls drawSparkles
    void drawStars(float t); 
    // Draws twinkling stars
    void drawSparkles (float t);
    // Draws the planets and moons
    void drawSolarSystem(const GLuint& EarthTexture, const GLuint& MoonTexture, const GLuint& MercuryTexture, const GLuint& VenusTexture, const GLuint& MarsTexture, float t);
    void drawSun (const GLuint& texture);

    bool drawGrid(float t, float t2, bool flashing); //method will draw the map grid and return true if its flashing
    // Draws the level, lives and score above the grid
    void drawStatus(int level, int lives, int score);
    // Draw the level up message when appropriate
    void drawLevelUp(float t, int level);

     // Menu drawing methods:
    void drawGameOver(int level, long int score, int lives, bool contHover, bool didQuit);
    void drawStartMenu(int gameType, int shipHover, int shipSelection, bool backHover, int mouseOverValue, int primarySelection, int secondarySelection, bool checkpoint); // method will draw the Start Menu
    void drawCredits(const GLuint& logoTexture, int mouseOverValue);
    void drawControls(const GLuint& mouseTexture, const GLuint& keysTexture, const GLuint& eTexture, int mouseOverValue);

     // Set glColor to the appropriate value based on what ship and colours are selected
    void setColour (int color, int shipType, int shipSelection);
    float currentShipRotation;

private:
    /*
    -------------------- Variables for the World class --------------------
    */
    float nebula1Size;
    float nebula1Origin[3];
    float nebula2Size;
    float nebula2Origin[3];
     // Solar system
    int randomNebula1;
    int randomNebula2;
    GLfloat earthSize;
    GLfloat earthDistance;
    float earthRotation;
    GLfloat mat_specular[4];
    GLfloat mat_shininess[1];
    GLfloat light_position[4];
    GLint numberOfStars; 
    GLfloat stars[5000][6]; 
    GLfloat sparkles[150][6];
    GLint sparkleSize[20];
    Particle2 corona;
    
GLfloat buffer[100];

     // Grid
    bool gridFadeUp;
    GLfloat gridAlphaValue;
    GLfloat lightTween;
    float startTime;
    float newTime;
    float lastTime;

     // Menu

    Text textHandler;
    

};
#endif
