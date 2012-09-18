/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the main class for the BattleShape project.
------------------------------------------------------------------------------*/

#include <GL/glut.h>
#include <shellapi.h>
#include <cmath>
#include <ctime>

#include "bmp.h"
#include "ViewPort.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "Vector.h"
#include "MouseHandler.h"
#include "Timer.h"
#include "GameHandler.h"
#include "Explosion.h"
#include "Propulsion.h"
#include "Torus.h"
#include "SoundManager.h"
#include "Sounds.h"
#include "Menus.h"

using namespace std;

// Instantiate major classes
ViewPort viewport;
Camera camera;
World world;
Player player;
MouseHandler mouseHandler;
Timer timer;
GameHandler gameHandler;
Propulsion propulsion;
Text text;
Menus menus;

GLuint textures[18]; // 0 is spark, 1 is planet, 2 is star, 3 is nebula1, 4 is nebula2, 5 is moon, 6 is mercury, 7 is nebula3,
                     // 9 is venus, 8 is galaxy1, 9 is venus, 10 is nebula4, 11 is nebula5, 12 is mars, 13 is nebula6
                     // 14 is shadowcat logo, 15 is mouse, 16 is wasd, 17 is e

// Game options
bool fullscreen = true;
bool fromControl = false;
//bool musicEnabled = true;
bool mainMenu = true;
bool didQuit = false;
bool creditsMenu = false;
bool controlMenu = false;
bool inGameMenu = false;
bool HUD = true;
bool transMenuToGame = false;
bool transGameOver = false;
float transTimer;

bool startMenu = false;
bool enemies = true;
bool shaking = false;
bool flashing = false;
bool gameover = false;
bool contHover = false;
bool cont = false;
bool firstAccelerating = true;

// Menu Variables
int primarySelection = 1;
int secondarySelection = 1;
int mouseOverValue = 0;
int gameType = 0; // 1 - Gauntlet, 2 - Time Attack
int shipHover = 0;
int colourHover = 0;
int shipSelection = 0;
int menuPerspective = 40;
int width = 0;
int height = 0;
bool backHover = 0;
int cheatCounter=0;
int frameCount = 0;
bool alreadyHovering = false;

// For error msgs only
bool error = false;
bool errorHover = false;

void gameOver(void){
     // Bring up the main menu
     mainMenu = true;
     transMenuToGame = false;
     transGameOver=false;
     transTimer=250;
     cont = false;
     gameover = false;
     error = false;
     shipSelection = 0;
     player.gameOver();
}
void menuToGame(void){
    gameHandler.ReInitialize();
    gameType=0;
    startMenu = false;
    mainMenu = false;
    gameover = false;
    cont=false;
    transMenuToGame=true;
    transTimer = 250;

//    gameType = 0;

    mouseOverValue = 0;

    SoundManager::fadeOutFadeIn( MUSIC::GAME_MUSIC);

}
void creditsSetup(void){
        viewport.setFarClippingPlaneDistance(10000.0f);
        viewport.setPerspective(menuPerspective);

        timer.updateTimer();

        // Set up the camera
        camera.setPositionX(100.0);
        camera.setPositionY(75.0);
        camera.setPositionZ(200);
        camera.setCamera();
        camera.setLookAtX(100+141.0);
        camera.setLookAtY(75-141.0);
        camera.setLookAtZ(200.0);
        camera.setViewUpX(0.0);
        camera.setViewUpY(0.0);
        camera.setViewUpZ(1.0);
        camera.setViewingAngle(50.0);

        world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
}
// Set up and draw menu
void menuSetup(void){
        viewport.setFarClippingPlaneDistance(10000.0f);
        viewport.setPerspective(menuPerspective);

        timer.updateTimer();

        // Set up the camera
        camera.setPositionX(100.0);
        camera.setPositionY(75.0);
        camera.setPositionZ(200);
        camera.setCamera();
        camera.setLookAtX(100+141.0);
        camera.setLookAtY(75+141.0);
        camera.setLookAtZ(200.0);
        camera.setViewUpX(0.0);
        camera.setViewUpY(0.0);
        camera.setViewUpZ(1.0);
        camera.setViewingAngle(50.0);

        world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
}
void gameOverSetup(void){
        viewport.setFarClippingPlaneDistance(10000.0f);
        viewport.setPerspective(menuPerspective);

        timer.updateTimer();

        // Set up the camera
        camera.setPositionX(100.0);
        camera.setPositionY(75.0);
        camera.setPositionZ(200);
        camera.setCamera();
        camera.setLookAtX(100-141.0);
        camera.setLookAtY(75+141.0);
        camera.setLookAtZ(200.0);
        camera.setViewUpX(0.0);
        camera.setViewUpY(0.0);
        camera.setViewUpZ(1.0);
        camera.setViewingAngle(50.0);

        world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
}

void displayCredits(void) {

        if(transTimer==0)
             creditsSetup();
        else if(transTimer>=0) // transitioning back from the credits screen
        {
            mouseOverValue = 0;
            transTimer-=timer.getTimer();
            if(transTimer<=0)
                 transTimer=0;
            viewport.setFarClippingPlaneDistance(10000.0f);
            viewport.setPerspective(menuPerspective);

            timer.updateTimer();

            // Set up the camera
            camera.setPositionX(100.0);
            camera.setPositionY(75.0);
            camera.setPositionZ(200);
            camera.setLookAtX(-41.0+(282));
            camera.setLookAtY(75+141.0-((cos(transTimer/(250/3.14))+1)/2)*(282));
            camera.setLookAtZ(200.0);
            camera.setViewUpX(0.0);
            camera.setViewUpY(0.0);
            camera.setViewUpZ(1.0);
            camera.setViewingAngle(40.0);
            camera.setCamera();
            viewport.setPerspective(camera.getViewingAngle()); //set the viewport perspective

            world.drawStars(timer.getTimer());
//             world.drawMeteor(timer.getTimer(), mainMenu, gameOver);

             glPushMatrix();

              glTranslatef(100+141,75+141,200);
              glRotatef(-45,0,0,1);
              glRotatef(90,1,0,0);
              glTranslatef(-100,-75,0);

              world.drawStartMenu(gameType, shipHover, shipSelection, backHover, mouseOverValue, primarySelection, secondarySelection, gameHandler.checkpoint);
              glPopMatrix();
        }
         glPushMatrix();

          glTranslatef(100+141,75-141,200);
          glRotatef(-135,0,0,1);
          glRotatef(90,1,0,0);
          glTranslatef(-100,-75,0);

          world.drawCredits(textures[14], mouseOverValue);

        glPopMatrix();
}

void displayControls(void) {

        fromControl = true;

        if(transTimer==0)
             creditsSetup();
        else if(transTimer>=0) // transitioning back from the credits screen
        {
            mouseOverValue = 0;
            transTimer-=timer.getTimer();
            if(transTimer<=0)
                 transTimer=0;
            viewport.setFarClippingPlaneDistance(10000.0f);
            viewport.setPerspective(menuPerspective);

            timer.updateTimer();

            // Set up the camera
            camera.setPositionX(100.0);
            camera.setPositionY(75.0);
            camera.setPositionZ(200);
            camera.setLookAtX(-41.0+(282));
            camera.setLookAtY(75+141.0-((cos(transTimer/(250/3.14))+1)/2)*(282));
            camera.setLookAtZ(200.0);
            camera.setViewUpX(0.0);
            camera.setViewUpY(0.0);
            camera.setViewUpZ(1.0);
            camera.setViewingAngle(40.0);
            camera.setCamera();
            viewport.setPerspective(camera.getViewingAngle()); //set the viewport perspective

            world.drawStars(timer.getTimer());
//             world.drawMeteor(timer.getTimer(), mainMenu, gameOver);

             glPushMatrix();

              glTranslatef(100+141,75+141,200);
              glRotatef(-45,0,0,1);
              glRotatef(90,1,0,0);
              glTranslatef(-100,-75,0);

              world.drawStartMenu(gameType, shipHover, shipSelection, backHover, mouseOverValue, primarySelection, secondarySelection, gameHandler.checkpoint);
              glPopMatrix();
        }
         glPushMatrix();

          glTranslatef(100+141,75-141,200);
          glRotatef(-135,0,0,1);
          glRotatef(90,1,0,0);
          glTranslatef(-100,-75,0);

          world.drawControls(textures[15], textures[16], textures[17], mouseOverValue);

        glPopMatrix();
}

void displayMenu(void) {

        // Plays the menu loop

        startMenu = true;
        if(transTimer==0)
             menuSetup();
        else if(transTimer>=0)
        {
            transTimer-=timer.getTimer();
            if(transTimer<=0)
                 transTimer=0;
            viewport.setFarClippingPlaneDistance(10000.0f);
            viewport.setPerspective(menuPerspective);

            timer.updateTimer();

            // Set up the camera
            camera.setPositionX(100.0);
            camera.setPositionY(75.0);
            camera.setPositionZ(200);
            camera.setLookAtX(-41.0+((cos(transTimer/(250/3.14))+1)/2)*(282));
            camera.setLookAtY(75+141.0);
            camera.setLookAtZ(200.0);
            camera.setViewUpX(0.0);
            camera.setViewUpY(0.0);
            camera.setViewUpZ(1.0);
            camera.setViewingAngle(40.0);
            camera.setCamera();
            viewport.setPerspective(camera.getViewingAngle()); //set the viewport perspective

            world.drawStars(timer.getTimer());
//             world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
             glPushMatrix();

              glTranslatef(100-141,75+141,200);
              glRotatef(45,0,0,1);
              glRotatef(90,1,0,0);
              glTranslatef(-100,-75,0);
              glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

              glDisable(GL_BLEND);
              world.drawGameOver(gameHandler.level, gameHandler.score, gameHandler.lives, contHover, didQuit);
              glEnable(GL_BLEND);

            glPopMatrix();
        }
        else if(transTimer<=0) // transitioning back from the credits screen
        {
            mouseOverValue = 0;
            transTimer+=timer.getTimer();
            if(transTimer>=0)
                 transTimer=0;
            viewport.setFarClippingPlaneDistance(10000.0f);
            viewport.setPerspective(menuPerspective);

            timer.updateTimer();

            // Set up the camera
            camera.setPositionX(100.0);
            camera.setPositionY(75.0);
            camera.setPositionZ(200);
            camera.setLookAtX(-41.0+(282));
            camera.setLookAtY(75+141.0-(1-(cos(transTimer/(250/3.14))+1)/2)*(282));
            camera.setLookAtZ(200.0);
            camera.setViewUpX(0.0);
            camera.setViewUpY(0.0);
            camera.setViewUpZ(1.0);
            camera.setViewingAngle(40.0);
            camera.setCamera();
            viewport.setPerspective(camera.getViewingAngle()); //set the viewport perspective

            world.drawStars(timer.getTimer());
//             world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
             glPushMatrix();

              glTranslatef(100+141,75-141,200);
              glRotatef(-135,0,0,1);
              glRotatef(90,1,0,0);
              glTranslatef(-100,-75,0);
              glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

               if (fromControl)   world.drawControls(textures[15], textures[16], textures[17], mouseOverValue);
               else world.drawCredits(textures[14], mouseOverValue);

              
            glPopMatrix();
        }
        if(startMenu){
             glPushMatrix();

              glTranslatef(100+141,75+141,200);
              glRotatef(-45,0,0,1);
              glRotatef(90,1,0,0);
              glTranslatef(-100,-75,0);

              world.drawStartMenu(gameType, shipHover, shipSelection, backHover, mouseOverValue, primarySelection, secondarySelection, gameHandler.checkpoint);
              glPopMatrix();
        }
}

void displayGameOver(void)
{
   gameOverSetup();
     glPushMatrix();

      glTranslatef(100-141,75+141,200);
      glRotatef(45,0,0,1);
      glRotatef(90,1,0,0);
      glTranslatef(-100,-75,0);
      glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

      glDisable(GL_BLEND);
         world.drawGameOver(gameHandler.level, gameHandler.score, gameHandler.lives, contHover, didQuit);
      glEnable(GL_BLEND);

     if(cont){
        gameOver();
     }
    glPopMatrix();
}

void displayTransMenuGame(void)
{

    viewport.setFarClippingPlaneDistance(10000.0f);
    viewport.setPerspective(menuPerspective);
    player.nukes=3;
     transTimer-=timer.getTimer();
     if(transTimer<0.0){
         transMenuToGame=false;
     }

    camera.setPositionX(100.0);
    camera.setPositionY(75.0);
    camera.setPositionZ(200);
    camera.setLookAtX(241.0-((cos(transTimer/(250/3.14))+1)/2)*(141));
    camera.setLookAtY(75+141.0-((cos(transTimer/(250/3.14))+1)/2)*(141));
    camera.setLookAtZ(200.0-((cos(transTimer/(250/3.14))+1)/2)*(200));
    camera.setViewUpX(0.0);
    camera.setViewUpY(0.0+((cos(transTimer/(250/3.14))+1)/2));
    camera.setViewUpZ(1.0-((cos(transTimer/(250/3.14))+1)/2));
    camera.setViewingAngle(40.0+((cos(transTimer/(250/3.14))+1)/2)*10);
    camera.setCamera();
    viewport.setPerspective(camera.getViewingAngle()); //set the viewport perspective

    if(transTimer>135)
    {
         glPushMatrix();
          glTranslatef(100+141,75+141,200);
          glRotatef(-45,0,0,1);
          glRotatef(90,1,0,0);
          glTranslatef(-100,-75,0);

          world.drawStartMenu(gameType, shipHover, shipSelection, backHover, mouseOverValue, primarySelection, secondarySelection, gameHandler.checkpoint);
         glPopMatrix();
    world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        world.drawSolarSystem(textures[1], textures[5], textures[6], textures[9], textures[12], timer.getTimer());
        world.drawNebulas(textures[3], textures[4], textures[7], textures[8], textures[10], textures[11], textures[13], timer.getTimer());
        world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
        glDisable(GL_DEPTH_TEST);
        world.drawSun(textures[0]);

        // Draw the world
        flashing = world.drawGrid(timer.getTimer(), timer.getLastTimer(), gameHandler.gridFlashing);
        if (!flashing) gameHandler.gridFlashing = false;
        else { world.drawLevelUp(timer.getLastTimer(), gameHandler.level); }
        world.drawStatus(gameHandler.level, gameHandler.lives, gameHandler.score);
      glBindTexture(GL_TEXTURE_2D, textures[0]);
        player.drawPlayer(timer.getTimer(),(GLint)(mouseHandler.getMouseGridX() - player.position.getX()),(GLint)(mouseHandler.getMouseGridY() - player.position.getY())); //draw the player
    }
}
void displayTransGameOver(void) {

    viewport.setFarClippingPlaneDistance(10000.0f);
    viewport.setPerspective(menuPerspective);

     transTimer-=timer.getTimer();
     if(transTimer<0.0)
     {
         transMenuToGame=false;
         gameover=true;
     }


    camera.setLookAtX(player.position.getX());
    camera.setLookAtY(player.position.getY());
    if (!player.cameraShake && !gameHandler.cameraShake) {
         camera.setPositionX((player.position.getX() - 100) * 2 + 100);
         camera.setPositionY((player.position.getY() - 75) * 2 + 75);
    }
//([starting value]+/-{direction to move}((cos([timer in use, counting down]/([max Timer]/3.14))+1)/2)*([value to change by]))
// this equation above creates a nice and smooth transition based upon a small section of a cos wave
    camera.setPositionX(100.0);
    camera.setPositionX(((player.position.getX() - 100) * 2 + 100)+((cos(transTimer/(250/3.14))+1)/2)*(100-((player.position.getX() - 100) * 2 + 100)));
    camera.setPositionY(75.0);
    camera.setPositionY(((player.position.getY() - 75) * 2 + 75)+((cos(transTimer/(250/3.14))+1)/2)*(75-((player.position.getY() - 75) * 2 + 75)));
    camera.setPositionZ((camera.getPositionZ()-((cos(transTimer/(250/3.14))+1)/2)*(camera.getPositionZ()-200)));//camera.getPositionZ()
    camera.setLookAtX(player.position.getX()-((cos(transTimer/(250/3.14))+1)/2)*(141+player.position.getX()-100));
    camera.setLookAtY(player.position.getY()+((cos(transTimer/(250/3.14))+1)/2)*(141-player.position.getY()+75));
    camera.setLookAtZ(((cos(transTimer/(250/3.14))+1)/2)*(200));
    camera.setViewUpX(0.0);
    camera.setViewUpY(1.0-((cos(transTimer/(250/3.14))+1)/2));
    camera.setViewUpZ(0.0+((cos(transTimer/(250/3.14))+1)/2));
    camera.setViewingAngle(50.0-((cos(transTimer/(250/3.14))+1)/2)*10);
    camera.setCamera();
    viewport.setPerspective(camera.getViewingAngle()); //set the viewport perspective

    if(transTimer>100)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        world.drawSolarSystem(textures[1], textures[5], textures[6], textures[9], textures[12], timer.getTimer());
        world.drawNebulas(textures[3], textures[4], textures[7], textures[8], textures[10], textures[11], textures[13], timer.getTimer());
        world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
        glDisable(GL_DEPTH_TEST);
        world.drawSun(textures[0]);

        // Draw the world
        flashing = world.drawGrid(timer.getTimer(), timer.getLastTimer(), gameHandler.gridFlashing);
        if (!flashing) gameHandler.gridFlashing = false;
        else { world.drawLevelUp(timer.getLastTimer(), gameHandler.nextLevel); }
        world.drawStatus(gameHandler.level, gameHandler.lives, gameHandler.score);



        player.drawPropulsion(textures[10], timer.getTimer(),timer.getLastTimer(),gameHandler.playerDeath);
          glBindTexture(GL_TEXTURE_2D, textures[0]);

        if(!gameHandler.playerDeath)
        {
            player.drawPlayer(timer.getTimer(),(GLint)(mouseHandler.getMouseGridX() - player.position.getX()),(GLint)(mouseHandler.getMouseGridY() - player.position.getY())); //draw the player
            player.movePlayer(timer.getTimer());
        }
        else
        {
            gameHandler.newLifeSequence(timer.getTimer(), timer.getLastTimer());
        }
        player.drawShots(timer.getTimer());
        player.drawNuke( timer.getTimer());

        player.moveShots(timer.getTimer(),timer.getLastTimer(), gameHandler.drones, gameHandler.mines, gameHandler.factories, gameHandler.fragBosses, gameHandler.numberOfDrones, gameHandler.numberOfMines, gameHandler.numberOfFactories, gameHandler.numberOfFragBosses);
        player.moveNuke(timer.getTimer(), timer.getLastTimer(), gameHandler.drones, gameHandler.mines, gameHandler.factories, gameHandler.fragBosses, gameHandler.numberOfDrones, gameHandler.numberOfMines, gameHandler.numberOfFactories, gameHandler.numberOfFragBosses);

        // Draw the enemies and decrement lives if the player is hit
        if (enemies){
        gameHandler.drawEnemies(0, timer.getTimer(), timer.getLastTimer(),player.position.getX(), player.position.getY(), player.position.getZ());
        }
        gameHandler.drawUpgrades(0, timer.getTimer(),timer.getLastTimer(), player.position.getX(), player.position.getY(), player.position.getZ(), player.shipType);

    }
    if(transTimer<170)
    {
//           gameOverSetup();
        world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
         glPushMatrix();

          glTranslatef(100-141,75+141,200);
          glRotatef(45,0,0,1);
          glRotatef(90,1,0,0);
          glTranslatef(-100,-75,0);
          glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

          glDisable(GL_BLEND);
             world.drawGameOver(gameHandler.level, gameHandler.score, gameHandler.lives, contHover, didQuit);
          glEnable(GL_BLEND);

         if(cont){
            gameOver();
         }
        glPopMatrix();
    }
}

// Main display loop
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    timer.updateTimer(); // increment timer

    int errorCheck=0;

    // Menu display block
    if(mainMenu)
    {
         displayMenu();
    }
    else if(gameover)
    {
         displayGameOver();
    }
    else if(transMenuToGame)
    {
         displayTransMenuGame();
    }
    else if(transGameOver)
    {
         displayTransGameOver();
    }
    else if(creditsMenu)
    {
         displayCredits();
    }
    else if(controlMenu)
    {
         displayControls();
    }
    else
    // In-Game display block
    {

        if(!inGameMenu) glutSetCursor(GLUT_CURSOR_NONE); // Disable the cursor in-game

        viewport.setPerspective(camera.getViewingAngle()); //set the viewport perspective
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        world.drawSolarSystem(textures[1], textures[5], textures[6], textures[9], textures[12], timer.getTimer());
        world.drawNebulas(textures[3], textures[4], textures[7], textures[8], textures[10], textures[11], textures[13], timer.getTimer());
        world.drawStars(timer.getTimer());
//        world.drawMeteor(timer.getTimer(), mainMenu, gameOver);
        glDisable(GL_DEPTH_TEST);
        world.drawSun(textures[0]);

        // Draw the world

        flashing = world.drawGrid(timer.getTimer(), timer.getLastTimer(), gameHandler.gridFlashing);
        if (!flashing) {gameHandler.gridFlashing = false;}
        else {world.drawLevelUp(timer.getLastTimer(),gameHandler.nextLevel); }

        world.drawStatus(gameHandler.level, gameHandler.lives, gameHandler.score);

        // Update the camera

        camera.setLookAtX(player.position.getX());

        camera.setLookAtY(player.position.getY());
        if (!player.cameraShake && !gameHandler.cameraShake) {

             camera.setPositionX((player.position.getX() - 100) * 2 + 100);

             camera.setPositionY((player.position.getY() - 75) * 2 + 75);
        }
        else {shaking = camera.shake((player.position.getX() - 100) * 2 + 100, (player.position.getY() - 75) * 2 + 75, timer.getLastTimer());}
        if (!shaking) {player.cameraShake = false; gameHandler.cameraShake = false;}

        camera.setCamera();

        // Draw the player

        player.drawPropulsion(textures[10], timer.getTimer(),timer.getLastTimer(), gameHandler.playerDeath);
        glBindTexture(GL_TEXTURE_2D, textures[0]);

        if(!gameHandler.playerDeath)
        {
            player.drawPlayer(timer.getTimer(),(GLint)(mouseHandler.getMouseGridX() - player.position.getX()),(GLint)(mouseHandler.getMouseGridY() - player.position.getY())); //draw the player
            player.movePlayer(timer.getTimer());
            player.shoot((GLint)(mouseHandler.getMouseGridX() - player.position.getX()),(GLint)(mouseHandler.getMouseGridY() - player.position.getY()));
        }
        else
        {

            if(gameHandler.newLifeSequence(timer.getTimer(), timer.getLastTimer()))
            {
                player.position.set(100,75,1);
                player.shields=3;
                player.movement.set(0,0,0);
            }

            player.position.set(gameHandler.playerDeathLoc.getX()-((cos(gameHandler.newLifeTimer/50.93)+1)/2)*gameHandler.spawnPath.getX(),gameHandler.playerDeathLoc.getY()-((cos(gameHandler.newLifeTimer/50.93)+1)/2)*gameHandler.spawnPath.getY(),1);
        }

        player.drawShots(timer.getTimer());
        player.drawNuke(timer.getLastTimer());

        // Move the player's shots and update the score if they hit

        player.moveShots(timer.getTimer(),timer.getLastTimer(), gameHandler.drones, gameHandler.mines, gameHandler.factories, gameHandler.fragBosses, gameHandler.numberOfDrones, gameHandler.numberOfMines, gameHandler.numberOfFactories, gameHandler.numberOfFragBosses);
        player.moveNuke(timer.getTimer(), timer.getLastTimer(), gameHandler.drones, gameHandler.mines, gameHandler.factories, gameHandler.fragBosses, gameHandler.numberOfDrones, gameHandler.numberOfMines, gameHandler.numberOfFactories, gameHandler.numberOfFragBosses);

        gameHandler.updateScore();

        // Update the mouse if the game isn't paused, then draw the mouse

        if (!timer.getPauseStatus()) mouseHandler.updateMouse(camera.getPositionX(), camera.getPositionY(), camera.getPositionZ(), player.position.getX(), player.position.getY(), viewport.getWindowHeight(), viewport.getWindowWidth(), camera.getViewingAngle());
        if(!inGameMenu) mouseHandler.drawMouse(timer.getLastTimer());
        if(gameHandler.level==11)
        {
             transGameOver=true;
             transTimer=250;
             gameHandler.level--;
        }

        // Draw the enemies and decrement lives if the player is hit
        if (enemies){
             if(gameHandler.drawEnemies(0, timer.getTimer(), timer.getLastTimer(),player.position.getX(), player.position.getY(), player.position.getZ()))
             {
                 if(player.ram() && !gameHandler.playerDeath)
                 {
                     gameHandler.lives--;
                     if(gameHandler.lives == -1){

                          transGameOver=true;
                          SoundManager::fadeOutFadeIn( MUSIC::MENU_MUSIC);
                          transTimer=250;
//                        gameover = true;
                     }

                     gameHandler.killPlayer(timer.getLastTimer(), player.position);
                 }
             }
        }

        // Draw the upgrades and apply them to the player if they are collected

        int upg = gameHandler.drawUpgrades(0, timer.getTimer(), timer.getLastTimer(), player.position.getX(), player.position.getY(), player.position.getZ(), player.shipType);
        if( upg != 0)
        {
            player.getUpgrade(upg);
        }

        
        // Start here for camera-free drawing

     camera.backUp();
             camera.setPositionX(100.0);
             camera.setPositionY(75.0);
             camera.setPositionZ(200);
             camera.setLookAtX(100+141.0);
             camera.setLookAtY(75+141.0);
             camera.setLookAtZ(200.0);
             camera.setViewUpX(0.0);
             camera.setViewUpY(0.0);
             camera.setViewUpZ(1.0);
            camera.setViewingAngle(50.0);
             camera.setCamera();

       glPushMatrix();
       glTranslatef(100+141,75+141,200);
       glRotatef(-45,0,0,1);
       glRotatef(90,1,0,0);

       if(inGameMenu) // In-game menu block
       {
          menus.drawMenu(timer.getTimer(), mouseOverValue);
       }
       if (HUD) // Heads up display block
       {
          menus.drawHUD(timer.getTimer(), player.upgradeLevel, player.specialShots, gameHandler.level, gameHandler.lives, gameHandler.score, player.shipType, player.shields, player.nukes);
       }
       if (timer.getPauseStatus() && !inGameMenu)
       {
          menus.drawPause();
       }
       glPopMatrix();
     camera.Restore();


    }
    glFlush();
    glutSwapBuffers();

    frameCount ++;
    srand(frameCount);
}

void mouseFunction (GLint button, GLint action, GLint xMouse, GLint yMouse) {
    // Start Game

    if (startMenu)
    {
       // Start button
       if(gameType == 1)
       {
           if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
           {
              if (gameHandler.checkpoint) {
                  gameHandler.level = 5;  
                  gameHandler.checkpoint = false;
              }else{
                    gameHandler.level = 0;
              }
              didQuit=false;
              player.shipType = shipSelection;
              player.setColour(primarySelection, secondarySelection);
              creditsMenu = false;
              if (player.shipType == 3)
              {
                                  // CHANGE BST SETTINGS HERE
                  player.acceleration = 0.2;
                  player.maxVelocity = 1.25;
                  player.dampening = 0.92;
              }
              else if (player.shipType == 4)
              {
                                  // CHANGE UFO SETTINGS HERE
                  player.acceleration = 0.2;
                  player.maxVelocity = 1.1;
                  player.dampening = 0.9;
              }
              if(player.shipType == 3 || player.shipType == 4)      menuToGame();
              else
              {
                 player.shipType = 3;
                                 // BST SETTINGS HERE AS WELL
                  player.acceleration = 0.2;
                  player.maxVelocity = 1.25;
                  player.dampening = 0.92;
                 player.setColour(1, 1);
                 menuToGame();
              }
           }
       }
       // Ship Selection:
       // Click BST
       if(shipHover == 1 && shipSelection != 3)
       {
             if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
             {
                 shipSelection = 3;
                 primarySelection = 1;
                 secondarySelection = 1;
             }
       }
       // click UFO
       else if (shipHover == 2 && shipSelection != 4){
             if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
                 shipSelection = 4;
                 primarySelection = 2;
                 secondarySelection = 1;
             }
       }
       // default value
       else  shipHover = 0;


       // Set colour when clicked
       if ((shipSelection == 3 || shipSelection == 4) && colourHover != 0)
       {
           if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
           {
              if (colourHover <= 4) primarySelection = colourHover;
              else secondarySelection = colourHover - 4;
           }
       }

       // Quit click
       if(mouseOverValue == 2)
       {
           if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
           {
                glutLeaveGameMode();
                exit(0);
           }
       }
       // Credits click
       else if (mouseOverValue == 3)
       {
          if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
          {
               creditsMenu = true; mainMenu = false; transTimer = 250; startMenu = false; fromControl = false;
          }
       }
       // Controls click
       else if (mouseOverValue == 4)
       {
          if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
          {
               controlMenu = true; mainMenu = false; transTimer = 250; startMenu = false;
          }
       }
    }// End start menu block

     // Game over screen block
    else if (gameover)
    {
      // Continue if clicked
      if(contHover)
      {
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        {
            gameHandler.clearEnemies();
            cont = true;
            contHover = false;
        }
      }
    }
    // In game menu block
    else if (inGameMenu)
    {
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        {
          if (mouseOverValue == 1) {inGameMenu = false; timer.pause(); } // resume gameplay
          else if (mouseOverValue == 2) {transGameOver = true; transTimer = 250; timer.pause(); inGameMenu = false; didQuit=true;} // go to gameover screen
          else if (mouseOverValue == 3) {glutLeaveGameMode();  exit(0);} // quit window
        }
    }
     // Credits block
    else if (creditsMenu)
    {
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        {
           if (mouseOverValue == 1) { mainMenu = true; transTimer = -250; creditsMenu = false; startMenu = true; fromControl = false;}
           if (mouseOverValue == 2)
           {
                SHELLEXECUTEINFO sei;
                ::ZeroMemory(&sei,sizeof(SHELLEXECUTEINFO));
                sei.cbSize = sizeof( SHELLEXECUTEINFO );        // Set Size
                sei.lpVerb = TEXT( "open" );                    // Set Verb
                sei.lpFile = (LPCTSTR)"http://shadowcatproductions.ca";                          // Set Target To Open
                sei.nShow = SW_SHOWNORMAL;                      // Show Normal
                ShellExecuteEx(&sei);
           }
        }
    }
    else if (controlMenu)
    {
          if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
          {
               if (mouseOverValue == 1) { mainMenu = true; transTimer = -250; controlMenu = false; startMenu = true; fromControl = true;}
          }
    }

    else
    // Gameplay mouse function
    {
        if (timer.getPauseStatus() == false)
        {
             // Shoot when the left mouse button is down
             if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
                 player.shooting(true);
             } else if (button == GLUT_LEFT_BUTTON && action == GLUT_UP) {
                 player.shooting(false);
             }
             
             // Shoot upgraded shots when right mouse button is down
             if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
             {
                    player.shootingSpec = true;
             }
             else if (button == GLUT_RIGHT_BUTTON && action == GLUT_UP) {
                    player.shootingSpec = false;
                    
             }
        }
    }
}

void motion(GLint x, GLint y) {

    // Update the mouse location
    mouseHandler.setMouseX(x);
    mouseHandler.setMouseY(y);

    // Check mouse coordinates with menu options.
        if(startMenu)
        {

              if (transTimer<=0)
              {
                  // Ship Selection
                  if(x > width * 0.25 && x < width * 0.42 && y > height * 0.3 && y < height * 0.726) shipHover = 1;
                  else if(x > width * 0.565 && x < width * 0.79 && y > height * 0.3 && y < height * 0.726) shipHover = 2;
                  else   shipHover = 0;
                  
                  // Colours
                  if (shipSelection == 3)
                  {
                      if(x > width * 0.27 && x < width * 0.291 && y > height * 0.6 && y < height * 0.63) colourHover = 1;
                      else if(x > width * 0.3 && x < width * 0.325 && y > height * 0.6 && y < height * 0.63) colourHover = 2;
                      else if(x > width * 0.34 && x < width * 0.36 && y > height * 0.6 && y < height * 0.63) colourHover = 3;
                      else if(x > width * 0.375 && x < width * 0.395 && y > height * 0.6 && y < height * 0.63) colourHover = 4;
                      
                      else if(x > width * 0.27 && x < width * 0.291 && y > height * 0.65 && y < height * 0.68) colourHover = 5;
                      else if(x > width * 0.3 && x < width * 0.325 && y > height * 0.65 && y < height * 0.68) colourHover = 6;
                      else if(x > width * 0.34 && x < width * 0.36 && y > height * 0.65 && y < height * 0.68) colourHover = 7;
                      else if(x > width * 0.375 && x < width * 0.395 && y > height * 0.65 && y < height * 0.68) colourHover = 8;
                      
                      else colourHover = 0;
                  }
                  else if (shipSelection == 4)
                  {
                      if(x > width * 0.604 && x < width * 0.626 && y > height * 0.6 && y < height * 0.63) colourHover = 1;
                      else if(x > width * 0.64 && x < width * 0.66 && y > height * 0.6 && y < height * 0.63) colourHover = 2;
                      else if(x > width * 0.674 && x < width * 0.695 && y > height * 0.6 && y < height * 0.63) colourHover = 3;
                      else if(x > width * 0.71 && x < width * 0.73 && y > height * 0.6 && y < height * 0.63) colourHover = 4;
                      
                      else if(x > width * 0.604 && x < width * 0.626 && y > height * 0.65 && y < height * 0.68) colourHover = 5;
                      else if(x > width * 0.64 && x < width * 0.66 && y > height * 0.65 && y < height * 0.68) colourHover = 6;
                      else if(x > width * 0.674 && x < width * 0.695 && y > height * 0.65 && y < height * 0.68) colourHover = 7;
                      else if(x > width * 0.71 && x < width * 0.73 && y > height * 0.65 && y < height * 0.68) colourHover = 8;
                      
                      else colourHover = 0;
                  }
                                    
                  // start game
                  if(x > width * 0.43 && x < width * 0.585 && y > height * 0.81 && y < height * 0.85)
                  {
                    //hover
                    if(!alreadyHovering){
                        SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                        alreadyHovering = true;
                    }
                    gameType = 1; 
                    mouseOverValue = 1;}
                  // quit
                  else if (x > width * 0.45 && x < width * 0.535 && y > height * 0.875 && y < height * 0.906) {
                    //hover              
                    if(!alreadyHovering){
                        SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                        alreadyHovering = true;
                    }          
                    mouseOverValue = 2;
                    }

                  // credits
                  else if (x > width * 0.76 && x < width * 0.89 && y > height * 0.84 && y < height * 0.87) {
                    //hover      
                    if(!alreadyHovering){
                        SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                        alreadyHovering = true;
                    }              
                    mouseOverValue = 3;
                    }
                  // controls
                  else if (x > width * 0.11 && x < width * 0.25 && y > height * 0.84 && y < height * 0.87) {
                    //hover             
                    if(!alreadyHovering){
                        SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                        alreadyHovering = true;
                    }       
                    mouseOverValue = 4;
                   }
                   // resume
                    else if (x > width * 0.405 && x < width * 0.6 && y > height * 0.75 && y < height * 0.785 && gameHandler.checkpoint) {
                    //hover
                    if(!alreadyHovering){
                        SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                        alreadyHovering = true;
                    }
                    mouseOverValue = 5;
                    gameType = 1;
                   }
                  else   {
                    //unhover                
                    alreadyHovering = false;
                    mouseOverValue = 0; gameType = 0;
                }
               }
               else
               {
                       //unhover
                       alreadyHovering = false;
                       mouseOverValue = 0;
                       gameType = 0;
                       backHover = false;
               }
        }
        
        else if(inGameMenu && transTimer<=0)
        {

            // resume
            if(x > width * 0.375 && x < width * 0.62 && y > height * 0.39 && y < height * 0.43 )  {
                if(!alreadyHovering || mouseOverValue != 1){
                    SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                    alreadyHovering = true;
                }
                mouseOverValue = 1;
            }
            // abandon
            else if(x > width * 0.37 && x < width * 0.63 && y > height * 0.44 && y < height * 0.485)  {
                if(!alreadyHovering || mouseOverValue != 2){
                    SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                    alreadyHovering = true;
                }
                mouseOverValue = 2;
            }
            // credits
            else if(x > width * 0.37 && x < width * 0.63 && y > height * 0.495 && y < height * 0.535)  {
                if(!alreadyHovering || mouseOverValue != 3){
                    SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                    alreadyHovering = true;
                }
                mouseOverValue = 3;
            }
            else{ 
                alreadyHovering = false;   
                mouseOverValue = 0; 
            }

        }
        
        else if (gameover)
        { // for continue button
          if(x > width * 0.413 && x < width * 0.65 && y > height * 0.540 && y < height * 0.614){
             contHover = true;
                if(!alreadyHovering){
                    SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                    alreadyHovering = true;
                }
          }
          else{  
                alreadyHovering = false;   
                contHover = false;
            }
        }
        
        else if (creditsMenu)
        {
           // back button
           if(x > width * 0.79 && x < width * 0.92 && y > height * 0.82 && y < height * 0.87) {
                mouseOverValue = 1;
                if(!alreadyHovering){
                    SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                    alreadyHovering = true;
                }
            }
           // logo
           else if(x > width * 0.23 && x < width * 0.75 && y > height * 0.61 && y < height * 0.88)
           {
               mouseOverValue = 2;
                if(!alreadyHovering){
                    SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                    alreadyHovering = true;
                }
               glutSetCursor(GLUT_CURSOR_HELP);
           }
           else {
                mouseOverValue = 0; 
                alreadyHovering = false;  
                glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            }
        }
        else if (controlMenu)
        {
            // back button
            if(x > width * 0.79 && x < width * 0.92 && y > height * 0.82 && y < height * 0.87) {
                mouseOverValue = 1;
                if(!alreadyHovering){
                    SoundManager::playSoundEffect( SOUND_EFFECT::MOUSEOVER_1 );
                    alreadyHovering = true;
                }
            }else{
                mouseOverValue = 0; 
                alreadyHovering = false;  
            }
        }
}

// Key press functionality
static void key(unsigned char key, int x, int y) {
       if(cheatCounter==0 && key=='i')
       {
           cheatCounter++;
       }
       else if(cheatCounter==1 && key=='s')
       {
           cheatCounter++;
       }
       else if(cheatCounter==2 && key=='n')
       {
           cheatCounter++;
       }
       else if(cheatCounter==3 && key=='u')
       {
           cheatCounter=0;
           gameHandler.cheatActive=true;
           player.getUpgrade(1);
           player.specialShots = 10000;
           player.nukes=10000;
           player.shields=10000;
       }
       else{
           cheatCounter=0;
       }
     if (timer.getPauseStatus() == false)
     {
         switch (key) {
         case 'w':
             player.accelerating(true);
             if(firstAccelerating){
                SoundManager::playSoundEffect( SOUND_EFFECT::THRUSTER );
             }
             firstAccelerating = false;
             break;
         case 'a':
             player.turningLeft(true);
             break;
         case 's':
             player.acceleratingBack(true);
             break;
         case 'd':
             player.turningRight(true);
             break;
         case 'v':
              if(gameHandler.cheatActive)
              {
                  player.getUpgrade(0);
                  player.specialShots = 10000;
                  break;
              }
         case 't':
              if(gameHandler.cheatActive)
              {
                  player.getUpgrade(1);
                  player.specialShots = 10000;
                  break;
              }
         case 'y':
              if(gameHandler.cheatActive)
              {
                  player.getUpgrade(2);
                  player.specialShots = 10000;
                  break;
              }
         case 'u':
              if(gameHandler.cheatActive)
              {
                  player.getUpgrade(3);
                  player.specialShots = 10000;
                  break;
              }
         case 'i':
              if(gameHandler.cheatActive)
              {
                  player.getUpgrade(4);
                  player.specialShots = 10000;
                  break;
              }
              break;
         case 'h':
               HUD = !HUD;
               break;
         case 'e':
             if (gameHandler.playerDeath == false) player.shootNuke((GLint)(mouseHandler.getMouseGridX() - player.position.getX()),(GLint)(mouseHandler.getMouseGridY() - player.position.getY()));
             break;
         case '-':
               camera.setPositionZ(camera.getPositionZ() + 3);
               if (camera.getPositionZ() > 600) {camera.setPositionZ(600);}
               break;
               break;
         case '=':
               camera.setPositionZ(camera.getPositionZ() - 3);
               if (camera.getPositionZ() < 30) {camera.setPositionZ(30);}
               break;
         case 27:
             break;
     }
    glutPostRedisplay();
}
}


// Key press: WASD movement
static void key2(unsigned char key, int x, int y) {

     if (timer.getPauseStatus() == false)
     {
         switch (key) {
         case 'w':
             player.accelerating(false);
             firstAccelerating = true;
             break;
         case 'a':
             player.turningLeft(false);
             break;
         case 's':
             player.acceleratingBack(false);
             break;
         case 'd':
             player.turningRight(false);
             break;
         case 27:
             if(!mainMenu){
                 glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
                 timer.pause();
                 inGameMenu=true;
                SoundManager::playSoundEffect( SOUND_EFFECT::PAUSE );
             }
             break;
         default:
             break;
         }
     }
     else
     {
          if (key == 27) {
              timer.pause();
              SoundManager::playSoundEffect( SOUND_EFFECT::PAUSE );
              if(!mainMenu){
                 inGameMenu = false;
              }
         }
     }
     glutPostRedisplay();
}


// Key press Left, Right, Up, Down movement
void SpecialKeysDown( int key, int x, int y) {
    switch ( key ) {
    case GLUT_KEY_LEFT :
        player.turningLeft(true) ;
        break;
    case GLUT_KEY_RIGHT :
        player.turningRight(true) ;
        break;
    case GLUT_KEY_UP :
        player.accelerating(true) ;
        break;
    case GLUT_KEY_DOWN :
        player.acceleratingBack(true) ;
        break;
    }
}

// Disable movement once the keys are released
void SpecialKeysUp( int key, int x, int y) {
    switch ( key ) {
    case GLUT_KEY_LEFT :
        player.turningLeft(false) ;
        break;
    case GLUT_KEY_RIGHT :
        player.turningRight(false) ;
        break;
    case GLUT_KEY_UP :
        player.accelerating(false) ;
        break;
    case GLUT_KEY_DOWN :
        player.acceleratingBack(false) ;
        break;
    }
}

//Idle function
void idle(void) {
    glutPostRedisplay();
}

static void reshapeFcn (GLint newWidth, GLint newHeight) {
    width = newWidth;
    height = newHeight;
    const float ar = (float) newWidth / (float) newHeight;
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    viewport.setWindowWidth(newWidth);
    viewport.setWindowHeight(newHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
        FILE *File=NULL;								// File Handle
        if (!Filename)									// Make Sure A Filename Was Given
        {
                return NULL;							// If Not Return NULL
        }
        File=fopen(Filename,"r");						// Check To See If The File Exists
        if (File)										// Does The File Exist?
        {
			fclose(File);								// Close The Handle
			return auxDIBImageLoad(Filename);			// Load The Bitmap And Return A Pointer
        }
        return NULL;									// If Load Failed Return NULL
}

int LoadGLTexture(char *Filename, int num)									// Load Bitmap And Convert To A Texture
{
        int Status=FALSE;								// Status Indicator
        AUX_RGBImageRec *TextureImage[1];				// Create Storage Space For The Textures
        memset(TextureImage,0,sizeof(void *)*1);		// Set The Pointer To NULL

        if (TextureImage[0] = LoadBMP(Filename))	    // Load Particle Texture
        {
			Status=TRUE;								// Set The Status To TRUE
			glGenTextures(1, &textures[num-1]);				// Create One Texture

			glBindTexture(GL_TEXTURE_2D, textures[num-1]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        }

        if (TextureImage[0])							// If Texture Exists
		{
			if (TextureImage[0]->data)					// If Texture Image Exists
			{
				free(TextureImage[0]->data);			// Free The Texture Image Memory
			}
			free(TextureImage[0]);						// Free The Image Structure
		}
        return Status;									// Return The Status
}



//Main Method
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    int xMax = GetSystemMetrics (SM_CXSCREEN);
    int yMax = GetSystemMetrics (SM_CYSCREEN);
    char x [4];
    char y [4];
    char gameModeString [15];
     
    sprintf(x, "%d", xMax);
    sprintf(y, "%d", yMax);

    // set game mode string to be XRES x YRES : 24    
    sprintf(gameModeString, "%s%s%s%s%d", x,"x",y,":",24);
        
    glutCreateWindow("Battleshape - Alpha 2.8.5");  // Not Fullscreen
    //glutGameModeString(gameModeString); // Fullscreen
    //glutEnterGameMode(); // Fullscreen
    
    LoadGLTexture("Textures/Particle3.bmp",1);
    LoadGLTexture("Textures/earth.bmp",2);
    LoadGLTexture("Textures/star.bmp",3);
    LoadGLTexture("Textures/nebula1.bmp",4);
    LoadGLTexture("Textures/nebula2.bmp",5);
    LoadGLTexture("Textures/moon.bmp",6);
    LoadGLTexture("Textures/mercury.bmp",7);
    LoadGLTexture("Textures/nebula3.bmp",8);
    LoadGLTexture("Textures/galaxy1.bmp",9);
    LoadGLTexture("Textures/venus.bmp",10);
    LoadGLTexture("Textures/nebula4.bmp",11);
    LoadGLTexture("Textures/nebula5.bmp",12);
    LoadGLTexture("Textures/mars.bmp",13);
    LoadGLTexture("Textures/nebula6.bmp",14);
    LoadGLTexture("Textures/scplogo.bmp",15);
    LoadGLTexture("Textures/mouse.bmp",16);
    LoadGLTexture("Textures/wasd.bmp",17);
    LoadGLTexture("Textures/e.bmp",18);

    bool debug_sound = false;
    SoundManager::initialize(debug_sound);
    SoundManager::playMusic( MUSIC::MENU_MUSIC );

    // Enable blending, alpha, anti-aliasing
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_TEXTURE_2D);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshapeFcn);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(key2);
    glutMouseFunc(mouseFunction);
    glutPassiveMotionFunc(motion);
    glutMotionFunc(motion);
    glutSpecialFunc(SpecialKeysDown);
    glutSpecialUpFunc(SpecialKeysUp);
    glutMainLoop();
    return EXIT_SUCCESS;
}
