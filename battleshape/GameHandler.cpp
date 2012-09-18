/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the GameHandler.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the GameHandler class --------------------
*/

#include "GameHandler.h"


/*
 -------------------- Constructors for the GameHandler class --------------------
*/

GameHandler::GameHandler() : maxInvince(100), cameraShake(false), playerDeath(false), numberOfDrones(15), numberOfMines(0), phaseCoolDown(75.0f), lives(3), score(0),
gridFlashing(false), checkpoint(false), checkpointLevel(false)
{
     newLevel();
}

/*
 -------------------- Destructor for the GameHandler class --------------------
*/
GameHandler::~GameHandler(){
}

/*
 -------------------- Accessors for the GameHandler class --------------------
*/

/*
 -------------------- Modifiers for the GameHandler class --------------------
*/

void GameHandler::ReInitialize(void){
     cameraShake=false;
     playerDeath=false;
     cheatActive=false;
     numberOfDrones = 15;
     numberOfMines = 0;
     phaseCoolDown=150.0f;
     if (checkpointLevel){ level = 6; checkpointLevel = false;}
     else level = 0;
     lives = 5;
     score = 0;
     int i;
     newLevel();
     gridFlashing=false;
}

/*
 -------------------- Methods for the GameHandler class --------------------
*/

bool GameHandler::drawEnemies(const GLuint& sparkTexture, float timer, float explosionTimer, GLfloat playerX, GLfloat playerY, GLfloat playerZ)
{
     torus.draw(timer);
     explosion1a.drawExplosion(explosionTimer);
     explosion2a.drawExplosion(explosionTimer);
     explosion3a.drawExplosion(explosionTimer);

     int i;
     bool hitPlayerFlag = false;
     phaseTimer-=timer;
     float distance;
     checkPhase();

     if(playerInvinceTimer>0) playerInvinceTimer-=timer;
     for (i = 0; i < numberOfDrones; i ++)
     {
         if(pushStrength>0.01)
         {
               if(drones[i].type==1)
               {
                   drones[i].appliedForce.set(drones[i].position.getX()-pushCenter.getX(),drones[i].position.getY()-pushCenter.getY(),0.0);

                   if(drones[i].appliedForce.normalize()==0)
                   {
                        drones[i].appliedForce.set(0,1,0.0);
                        drones[i].appliedForce.rotate('z',rand()/100.0);
                   }

                   distance=pow(pow(drones[i].position.getX()-pushCenter.getX(),2.0)+pow(drones[i].position.getY()-pushCenter.getY(),2.0),0.5);

                   if(distance==0)
                   {
                        distance=1;
                   }
                   if(distance<150.0)
                   {
                        drones[i].appliedForce.multiply(pushStrength-pushStrength*(distance/150.0));
                   }
               }
               else if(drones[i].type==2)
               {
                    if(drones[i].appliedForce.normalize()==0&&pushStrength>2.8)
                    {
                       drones[i].appliedForce.set(drones[i].position.getX()-pushCenter.getX(),drones[i].position.getY()-pushCenter.getY(),0.0);

                       if(drones[i].appliedForce.normalize()==0)
                       {
                            drones[i].appliedForce.set(0,1,0.0);
                            drones[i].appliedForce.rotate('z',rand()/100.0);
                       }

                       distance=pow(pow(drones[i].position.getX()-pushCenter.getX(),2.0)+pow(drones[i].position.getY()-pushCenter.getY(),2.0),0.5);

                       if(distance==0)
                       {
                            distance=0.001;
                       }
                       if(distance<150.0)
                       {
                            drones[i].appliedForce.multiply(pushStrength-pushStrength*(distance/150.0));
                       }
                       else
                       {
                            drones[i].appliedForce.multiply(0);
                       }
                   }
                   else if (pushStrength>2.0)
                        drones[i].appliedForce.multiply(pow(0.97,timer/2.0));
                   else
                        drones[i].appliedForce.multiply(0);
               }
               else if(drones[i].type==3)
               {
                    if(drones[i].appliedForce.normalize()==0&&pushStrength>2.7)
                    {
                       drones[i].appliedForce.set(drones[i].position.getX()-pushCenter.getX(),drones[i].position.getY()-pushCenter.getY(),0.0);
                       if(drones[i].appliedForce.normalize()==0)
                       {
                            drones[i].appliedForce.set(0,1,0.0);
                            drones[i].appliedForce.rotate('z',rand()/100.0);
                       }

                       distance=pow(pow(drones[i].position.getX()-pushCenter.getX(),2.0)+pow(drones[i].position.getY()-pushCenter.getY(),2.0),0.5);

                       if(distance==0)
                       {
                            distance=0.001;
                       }
                       if(distance<150.0)
                       {
                            drones[i].appliedForce.multiply(pushStrength-pushStrength*(distance/150.0));
                       }
                       else
                       {
                            drones[i].appliedForce.multiply(0);
                       }
                   }
                   else
                        drones[i].appliedForce.multiply(0);
               }
          }
           if(drones[i].updatePosition(timer, playerX, playerY, playerZ) && !playerDeath)
           {
               hitPlayerFlag=true;
               drones[i].takeDamage(100);
           }
           drones[i].draw(sparkTexture, timer, explosionTimer);
     }
     for (i = 0; i < numberOfMines; i ++)
     {
          if(mines[i].updatePosition(timer, playerX, playerY, playerZ) && !playerDeath)
          {
              hitPlayerFlag=true;
              mines[i].takeDamage(100);
          }
          mines[i].draw(sparkTexture, timer, explosionTimer);
     }
     for (i = 0; i < numberOfFactories; i ++)
     {
          if(factories[i].updatePosition(timer, playerX, playerY, playerZ, playerDeath) && !playerDeath)
          {
              hitPlayerFlag=true;
          }
          factories[i].draw(sparkTexture, timer, explosionTimer);
     }

     if(numberOfFragBosses>0)
     {
          if(pushStrength>0.01)
          {
               distance=pow(pow(fragBosses[0].position.getX()-pushCenter.getX(),2.0)+pow(fragBosses[0].position.getY()-pushCenter.getY(),2.0),0.5);
               fragBosses[0].appliedForce.add((fragBosses[0].position.getX()-pushCenter.getX())*(pushStrength-pushStrength*(distance/150))/distance,(fragBosses[0].position.getY()-pushCenter.getY())*(pushStrength-pushStrength*(distance/150))/distance,0.0);
               if(distance==0)
               {
                    fragBosses[0].appliedForce.set(0.0,1.0,0.0);
                    fragBosses[0].appliedForce.rotate('z',0.01*(float)rand());
                    fragBosses[0].appliedForce.multiply(pushStrength-pushStrength*(1/150.0));
               }
               for(i=0;i<fragBosses[0].numberOfDrones;i++)
               {
                   distance=pow(pow(fragBosses[0].children[i].position.getX()-pushCenter.getX(),2.0)+pow(fragBosses[0].children[i].position.getY()-pushCenter.getY(),2.0),0.5);
                   fragBosses[0].children[i].appliedForce.add((fragBosses[0].children[i].position.getX()-pushCenter.getX())*(pushStrength-pushStrength*(distance/150))/distance,(fragBosses[0].children[i].position.getY()-pushCenter.getY())*(pushStrength-pushStrength*(distance/150))/distance,0.0);
                   if(distance==0)
                   {
                        fragBosses[0].children[i].appliedForce.set(0.0,1.0,0.0);
                        fragBosses[0].children[i].appliedForce.rotate('z',0.01*(float)rand());
                        fragBosses[0].children[i].appliedForce.multiply(pushStrength-pushStrength*(1/150.0));
                   }
               }
          }

          if(fragBosses[0].updatePosition(timer, playerX, playerY, playerZ, playerDeath) && !playerDeath)
          {
              hitPlayerFlag=true;
          }
          fragBosses[0].draw(sparkTexture, timer, explosionTimer);
          if(fragBosses[0].wasHit)
          {
              fragBosses[0].wasHit=false;
              numberOfDrones+=8;
              i = (int) fragBosses[0].getHealth();
              float tempChanger;
              float tempR=0.5;
              float tempG=0.5;
              float tempB=0.5;
              int k=i%8;
              if(k<4)
                  tempChanger=(float)k/4.0;
              else
                  tempChanger=1.0-((float)k-4.0)/4.0;

              if(i%24<4)
              {
                   tempR=0;
                   tempG=1;
              }
              else if(i%24<8)
              {
                   tempR=0;
                   tempB=1;
              }
              else if(i%24<12)
              {
                   tempG=0;
                   tempB=1;
              }
              else if(i%24<16)
              {
                   tempG=0;
                   tempR=1;
              }
              else if(i%24<20)
              {
                   tempB=0;
                   tempR=1;
              }
              else if(i%24<24)
              {
                   tempB=0;
                   tempG=1;
              }
              if(tempR<0.9 && tempR>0.1)
                  tempR=tempChanger;
              else if(tempG<0.9 && tempG>0.1)
                  tempG=tempChanger;
              else if(tempB<0.9 && tempB>0.1)
                  tempB=tempChanger;

              for(i=numberOfDrones-8;i<numberOfDrones;i++)
              {
                  drones[i].initialize(4);
                  drones[i].position.set(fragBosses[0].children[i-numberOfDrones+8].position.getX(),fragBosses[0].children[i-numberOfDrones+8].position.getY(),0);
                  drones[i].movement.set(fragBosses[0].children[i-numberOfDrones+8].movement.getX(),fragBosses[0].children[i-numberOfDrones+8].movement.getY(),0);
                  drones[i].red=tempR;
                  drones[i].green=tempG;
                  drones[i].blue=tempB;
              }
          }
          if(fragBosses[0].wasDestroyed)
          {
              cameraShake=true;
              fragBosses[0].wasDestroyed=false;
          }
     }
     pushStrength=0;
     if(cheatActive)
     {
//          playerInvinceTimer=maxInvince/2;
     }
     if(playerInvinceTimer>0 )
     {
             glPushMatrix();
             glColor4f(1.0, 1.0, -1.0 + 2.0*(playerInvinceTimer/maxInvince), 0.8*(playerInvinceTimer/maxInvince) );
             glLineWidth( 1 );
             glTranslatef( playerX, playerY, playerZ);
             float scale = 2.5;
             glScalef(scale,scale,scale);
             glutWireSphere(2,15,15);
             glColor4f(1.0, 1.0, -1.0 + 2.0*(playerInvinceTimer/maxInvince), 0.4*(playerInvinceTimer/maxInvince) );
             glutSolidSphere(2,15,15);
             glPopMatrix();
          return false;
     }
     return hitPlayerFlag;
}

int GameHandler::drawUpgrades(const GLuint& sparkTexture, float timer, float lastT, GLfloat playerX, GLfloat playerY, GLfloat playerZ, int shipType){

     int temp = upgrade.updatePosition(timer, playerX, playerY, playerZ);

     upgrade.draw(sparkTexture, timer, lastT, shipType);

     if(temp != 0)
     {
          upgrade.isActive = false;
          upgrade.isShrapnel = true;
          return temp;
     }
     return 0;
}
void GameHandler::clearEnemies() {
     int i;
     // If any drones are alive, clear their info.
     for (i = 0; i < 600; i ++) {
          if (drones[i].isAlive)
          {
              drones[i].isAlive=false;
              drones[i].type=-1;
          }
     }

     for (i = 0; i < 140; i ++) {
          if (mines[i].isAlive)
          {
              mines[i].isAlive=false;
              mines[i].type=-1;
          }
     }
     for (i = 0; i < 30; i ++) {
          if (factories[i].isAlive)
          {
              factories[i].isAlive=false;
              factories[i].type=-1;
          }
     }
     if(fragBosses[0].isAlive)
     {
          fragBosses[0].isAlive=false;
          fragBosses[0].type=-1;
     }
}

void GameHandler::checkPhase() {
     if(phaseTimer<0 && phaseTimer>-1000.0)
     {
         newPhase();
     }
     else
     {
         bool endPhase = true;
         int i;

         // If no drones are left alive, set phaseTimer=phaseCoolDown!

         for (i = 0; i < numberOfDrones; i ++) {
              if (drones[i].isAlive) endPhase = false;
         }

         for (i = 0; i < numberOfMines; i ++) {
              if (mines[i].isAlive)
              {
                  endPhase = false;
              }
         }
         for (i = 0; i < numberOfFactories; i ++) {
              if (factories[i].isAlive)
              {
                  endPhase = false;
              }
         }
         if(numberOfFragBosses>0)
             if(fragBosses[0].isAlive)
                 endPhase=false;

         if (endPhase && phaseTimer<-1001.0 && phase==0)
         {
              gridFlashing=true;
              nextLevel=level+1;
              phaseTimer=300;
         }
         else if (endPhase && (phaseTimer<-1001.0 || phaseTimer>phaseCoolDown))
         {
              phaseTimer=phaseCoolDown;
         }
         if(endPhase&&phase==0 && upgrade.isActive == false && upgradeCollected==false)
         {
             upgradeCollected=true;
             if(level==1)
                 upgrade.initialize(rand() % 4 + 1);
             if(level==3)
                 upgrade.initialize(rand() % 4 + 1);
             if(level==6)
                 upgrade.initialize(rand() % 4 + 1);
             if(level==8)
                 upgrade.initialize(rand() % 4 + 1);
         }
     }
}

void GameHandler::newPhase() {
     int i;
     phase --;

     SoundManager::playSoundEffect( SOUND_EFFECT::NEW_PHASE);

     if(phase<0)
     {
         newLevel();
     }
     else if (level == 1)
     {
          if(phase==1)
          {
             phaseTimer=2000.0;
             for (i = numberOfDrones; i < numberOfDrones +15; i ++)
             {
                 drones[i].initialize(level,rand()%50,(rand()%50),0,0);
             }
             for (i = numberOfDrones +15; i < numberOfDrones +30; i ++)
             {
                 drones[i].initialize(level,200-rand()%50,150-(rand()%50),0,0);
             }
             numberOfDrones += 30;
         }
          else
          {
             for (i = numberOfDrones; i < numberOfDrones +15; i ++)
             {
                 drones[i].initialize(level,rand()%50,150-(rand()%50),0,0);
             }
             for (i = numberOfDrones +15; i < numberOfDrones +30; i ++)
             {
                 drones[i].initialize(level,200-rand()%50,(rand()%50),0,0);
             }
             for (i = numberOfDrones+30; i < numberOfDrones +45; i ++)
             {
                 drones[i].initialize(level,rand()%50,(rand()%50),0,0);
             }
             for (i = numberOfDrones +45; i < numberOfDrones +60; i ++)
             {
                 drones[i].initialize(level,200-rand()%50,150-(rand()%50),0,0);
             }
             numberOfDrones += 60;
         }
     }
     else if (level == 2)
     {
          if(phase==1)
          {
                 phaseTimer=250.0;
                 for (i = numberOfDrones; i < numberOfDrones+40; i ++)
                 {
                      drones[i].initialize(level,(i-numberOfDrones)*5+2.5,2.5,0,0);
                 }
                 for (i = numberOfDrones+40; i < numberOfDrones+80; i ++)
                 {
                      drones[i].initialize(level,(i-numberOfDrones-40)*5+2.5,147.5,0,0);
                 }
                 numberOfDrones += 80;
          }
          else
          {
                 for (i = numberOfDrones; i < numberOfDrones+15; i ++)
                 {
                      drones[i].initialize(1,rand()%15+5,rand()%150,0,0);
                 }
                 for (i = numberOfDrones+15; i < numberOfDrones+30; i ++)
                 {
                      drones[i].initialize(1,195-rand()%15,rand()%150,0,0);
                 }
                 numberOfDrones += 30;
          }
     }
     else if (level == 3)
     {
          if(phase==1)
          {
                 phaseTimer=2000.0;
                 for (i = numberOfDrones; i < numberOfDrones+40; i ++)
                 {
                      drones[i].initialize(level,(i-numberOfDrones)*5+2.5,2.5,0,1);
                 }
                 for (i = numberOfDrones+40; i < numberOfDrones+80; i ++)
                 {
                      drones[i].initialize(level,(i-numberOfDrones-40)*5+2.5,147.5,0,-1);
                 }
                 numberOfDrones += 80;
          }
          else
          {
              Vector rotation;
              Vector tempDirection;
              rotation.set(0,50,0);
                 for (i = numberOfDrones; i < numberOfDrones+36; i ++)
                 {
                     rotation.rotate('z',3.15159*2/36);
                     tempDirection.set(rotation.getX(),rotation.getY(),0);
                     tempDirection.normalize();
                      drones[i].initialize(3,rotation.getX()+100,rotation.getY()+75,tempDirection.getX(),tempDirection.getY());
                     tempDirection.rotate('z',3.15159);
                      drones[i+36].initialize(3,rotation.getX()+100,rotation.getY()+75,tempDirection.getX(),tempDirection.getY());
                 }
                 numberOfDrones += 72;
          }
     }
     else if (level == 4)
     {
          if(phase==1)
          {
                 phaseTimer=200.0;
                 numberOfMines=30;
                 for (i = 0; i < 15; i ++)
                 {
                      mines[i].initialize(0,25,i*10+5);
                      if(i%2==0)
                          mines[i].reverseSpin();
                 }
                 for (i = 15; i < 30; i ++)
                 {
                      mines[i].initialize(0,175,(i-15)*10+5);
                      if(i%2==0)
                          mines[i].reverseSpin();
                 }
          }
          else
          {
                 for (i = numberOfDrones; i < numberOfDrones+30; i ++)
                 {
                      drones[i].initialize(1,rand()%15+5,rand()%150,0,0);
                 }
                 for (i = numberOfDrones+30; i < numberOfDrones+60; i ++)
                 {
                      drones[i].initialize(1,195-rand()%15,rand()%150,0,0);
                 }
                 numberOfDrones += 60;
          }
     }
     else if (level == 5)
     {
          if(phase==14)
          {
             phaseTimer=10.0;
             for (i = numberOfDrones; i < numberOfDrones+10; i ++)
             {
                  drones[i].initialize(2,((i-numberOfDrones)*5+2.5),2.5,0,0);
             }
             for (i = numberOfDrones+10; i < numberOfDrones+20; i ++)
             {
                  drones[i].initialize(2,(i-10-numberOfDrones)*5+2.5,147.5,0,0);
             }
             numberOfDrones+=20;
             for (i = numberOfMines; i < numberOfMines+15; i ++)
             {
                  mines[i].initialize(0,25,(i-numberOfMines)*10+5);
                  if(i%2==0)
                      mines[i].reverseSpin();
             }
             numberOfMines+=15;
             drones[numberOfDrones].initialize(3,2.5,140-(phase-1)*5,1,0);
//             drones[numberOfDrones+1].initialize(3,2.5,(phase-1)*5+2.5,1,0);
             numberOfDrones ++;
          }
          else if (phase==0)
          {
             numberOfDrones=0;
                 numberOfFragBosses=1;
                fragBosses[0].initialize(0,50,75);
          }
          else
          {
             phaseTimer=10;
             drones[numberOfDrones].initialize(3,2.5,140-(phase-1)*5,1,0);
             drones[numberOfDrones+1].initialize(3,2.5,(phase-1)*5+10,1,0);
             numberOfDrones += 2;
          }
          if(phase==1)
          {
             phaseTimer=-1001.0;
          }
     }
     else if (level == 6)
     {
          if(phase==0)
          {
             numberOfFactories = 4;
             numberOfMines = 4;
             numberOfDrones = 36+18;
             numberOfFragBosses = 0;
             mines[2].initialize(0,175,125);
             mines[3].initialize(0,25,25);
             factories[2].initialize(1,175,25);
             factories[3].initialize(1,25,125);
             drones[36+4].initialize(3,7.5,7.5,1,1);
             drones[36+13].initialize(3,200-7.5,150-7.5,-1,-1);
             for (i = 0; i < 4; i ++)
             {
                  drones[36+i].initialize(3,7.5+5*(i+1),7.5,1,1);
                  drones[36+i+5].initialize(3,7.5,7.5+5*(i+1),1,1);
                  drones[36+i+9].initialize(3,200-7.5-5*(i+1),150-7.5,-1,-1);
                  drones[36+i+14].initialize(3,200-7.5,150-7.5-5*(i+1),-1,-1);
             }
             drones[numberOfDrones+4].initialize(2,7.5,150-7.5,1,-1);
             drones[numberOfDrones+13].initialize(2,200-7.5,7.5,-1,1);
             for (i = 0; i < 4; i ++)
             {
                  drones[numberOfDrones+i].initialize(2,7.5+5*(i+1),150-7.5,1,-1);
                  drones[numberOfDrones+i+5].initialize(2,7.5,150-7.5-5*(i+1),1,-1);
                  drones[numberOfDrones+i+9].initialize(2,200-7.5-5*(i+1),7.5,-1,1);
                  drones[numberOfDrones+i+14].initialize(2,200-7.5,7.5+5*(i+1),-1,1);
             }
             numberOfDrones+=18;
          }
     }
     else if(level == 7)
     {
          if(phase == 0)
          {
                 for (i = numberOfDrones; i < numberOfDrones+30; i ++)
                 {
                      drones[i].initialize(3,2.5,(i-numberOfDrones)*5+2.5,1,0);
                 }
                 for (i = numberOfDrones+30; i < numberOfDrones+60; i ++)
                 {
                      drones[i].initialize(3,200-2.5,(i-30-numberOfDrones)*5+2.5,-1,0);
                 }
                 numberOfDrones += 60;
          }
     }
     else{}

     if(phase==0)
     {
          phaseTimer=-1001.0; // This is set below the threshold for checking to go to a new phase
          // the point of which being that you should have an infinite amount of time on the last phase of the level
     }
}
int GameHandler::updateScore() {
     int i;
     for(i=0;i<numberOfDrones;i++)
     {
         score+=drones[i].getPointValue();
     }
     for(i=0;i<numberOfMines;i++)
     {
         score+=mines[i].getPointValue();
     }
     for(i=0;i<numberOfFactories;i++)
     {
         score+=factories[i].getPointValue();
     }
     if(numberOfFragBosses>0)
         score+=fragBosses[0].getPointValue();
     return 0;
}


void GameHandler::newLevel() {

     int i;
     level ++;

     upgradeCollected=false;

     if(level==1)
     {
         numberOfDrones = 30;
         phase=2;
         phaseTimer=2000.0;
         numberOfMines = 0;
         numberOfFragBosses=0;
         for (i = 0; i < 15; i ++)
         {
             drones[i].initialize(level,rand()%50,150-(rand()%50),0,0);
         }
         for (i = 15; i < 30; i ++)
         {
             drones[i].initialize(level,200-rand()%50,(rand()%50),0,0);
         }
     }
     else if(level==2)
     {
         phase=2;
         phaseTimer=2000.0;
         numberOfDrones = 60;
         numberOfMines = 0;
         for (i = 0; i < 30; i ++)
         {
              drones[i].initialize(level,2.5,i*5+2.5,0,0);
         }
         for (i = 30; i < 60; i ++)
         {
              drones[i].initialize(level,200-2.5,(i-30)*5+2.5,0,0);
         }
     }
     else if(level==3)
     {
         phase=2;
         phaseTimer=2000.0;
         numberOfDrones = 60;
         numberOfMines = 0;
         for (i = 0; i < 30; i ++)
         {
              drones[i].initialize(level,2.5,i*5+2.5,1,0);
         }
         for (i = 30; i < 60; i ++)
         {
              drones[i].initialize(level,200-2.5,(i-30)*5+2.5,-1,0);
         }
     }
     else if (level == 4)
     {
         phase=2;
         phaseTimer=400.0;
         numberOfDrones = 80;
         numberOfMines = 0;
         numberOfFactories = 0;
         for (i = 0; i < 40; i ++)
         {
              drones[i].initialize(2,i*5+2.5,2.5,0,0);
         }
         for (i = 40; i < 80; i ++)
         {
              drones[i].initialize(2,(i-40)*5+2.5,147.5,0,0);
         }
     }
     else if (level == 5)
     {
         phase=15;
         phaseTimer=500.0;
         numberOfDrones = 20;
         numberOfMines = 0;
         numberOfFactories = 0;
         for (i = 0; i < 10; i ++)
         {
              drones[i].initialize(2,200-(i*5+2.5),2.5,0,0);
         }
         for (i = 10; i < 20; i ++)
         {
              drones[i].initialize(2,(i-10)*5+2.5+30*5,147.5,0,0);
         }
         numberOfMines=15;
         for (i = 0; i < 15; i ++)
         {
              mines[i].initialize(0,175,(i)*10+5);
              if(i%2==0)
                  mines[i].reverseSpin();
         }
         for (i = numberOfDrones; i < numberOfDrones+30; i ++)
         {
              drones[i].initialize(1,195-rand()%15,rand()%150,0,0);
         }
         numberOfDrones += 30;
     }
     else if (level == 6)
     {
         checkpoint = true;
         phase=1;
         phaseTimer=2000.0;
         numberOfFactories = 2;
         numberOfMines = 2;
         numberOfDrones = 18;
         numberOfFragBosses = 0;
         factories[0].initialize(1,175,125);
         factories[1].initialize(1,25,25);
         mines[0].initialize(0,175,25);
         mines[1].initialize(0,25,125);
         drones[4].initialize(2,7.5,7.5,0,0);
         drones[13].initialize(2,200-7.5,150-7.5,0,0);
         for (i = 0; i < 4; i ++)
         {
              drones[i].initialize(2,7.5+5*(i+1),7.5,0,0);
              drones[i+5].initialize(2,7.5,7.5+5*(i+1),0,0);
              drones[i+9].initialize(2,200-7.5-5*(i+1),150-7.5,0,0);
              drones[i+14].initialize(2,200-7.5,150-7.5-5*(i+1),0,0);
         }
         drones[numberOfDrones+4].initialize(3,7.5,150-7.5,1,-1);
         drones[numberOfDrones+13].initialize(3,200-7.5,7.5,-1,1);
         for (i = 0; i < 4; i ++)
         {
              drones[numberOfDrones+i].initialize(3,7.5+5*(i+1),150-7.5,1,-1);
              drones[numberOfDrones+i+5].initialize(3,7.5,150-7.5-5*(i+1),1,-1);
              drones[numberOfDrones+i+9].initialize(3,200-7.5-5*(i+1),7.5,-1,1);
              drones[numberOfDrones+i+14].initialize(3,200-7.5,7.5+5*(i+1),-1,1);
         }
         numberOfDrones+=18;
     }
     else if (level == 7)
     {
         phase=1;
         phaseTimer=500.0;
         numberOfFactories = 4;
         numberOfMines = 0;
         numberOfDrones = 0;
         numberOfFragBosses = 0;
         factories[0].initialize(1,175,125);
         factories[1].initialize(1,25,25);
         factories[2].initialize(1,175,25);
         factories[3].initialize(1,25,125);
         for (i = numberOfDrones; i < numberOfDrones+40; i ++)
         {
              drones[i].initialize(3,(i-numberOfDrones)*5+2.5,2.5,100-(i-numberOfDrones)*5+2.5,72.5);
         }
         for (i = numberOfDrones+40; i < numberOfDrones+80; i ++)
         {
              drones[i].initialize(3,(i-numberOfDrones-40)*5+2.5,147.5,100-(i-numberOfDrones-40)*5+2.5,75-147.5);
         }
         numberOfDrones+=80;
     }
     else if (level == 8)
     {
         phase=0;
         phaseTimer=-1001.0;
         numberOfFactories = 10;
         numberOfMines = 0;
         numberOfDrones = 0;
         numberOfFragBosses = 0;
         for (i = 0; i < 5; i ++)
         {
              factories[i].initialize(1,25,25+25*i);
              factories[i+5].initialize(1,175,25+25*i);
         }
         for (i = numberOfDrones; i < numberOfDrones+5; i ++)
         {
              drones[i].initialize(3,(i-numberOfDrones)*48.75+2.5,2.5,0,1);
         }
         for (i = numberOfDrones+5; i < numberOfDrones+10; i ++)
         {
              drones[i].initialize(3,(i-numberOfDrones-5)*48.75+2.5,147.5,0,-1);
         }
         numberOfDrones+=10;
     }
     else if(level == 9)
     {
         phase=0;
         phaseTimer=-1001.0;
         numberOfFactories = 4;
         numberOfMines = 0;
         numberOfDrones = 0;
         numberOfFragBosses = 0;
         factories[0].initialize(1,175,125);
         factories[1].initialize(1,25,25);
         factories[2].initialize(1,175,25);
         factories[3].initialize(1,25,125);
         int x=5;
         int y=5;
         while(x<195)
         {
            mines[numberOfMines].initialize(1,x,y,-1,0);
            numberOfMines++;
            x+=10;
         }
         while(y<145)
         {
            mines[numberOfMines].initialize(1,x,y,0,-1);
            numberOfMines++;
            y+=10;
         }
         while(x>5)
         {
            mines[numberOfMines].initialize(1,x,y,1,0);
            numberOfMines++;
            x-=10;
         }
         while(y>5)
         {
            mines[numberOfMines].initialize(1,x,y,0,1);
            numberOfMines++;
            y-=10;
         }
     }
     else if (level == 10)
     {
         phase=0;
         numberOfFactories = 0;
         numberOfMines = 0;
         numberOfDrones = 0;
         numberOfFragBosses = 1;
         fragBosses[0].initialize(1,150,75);
     }
     else
     {
         phase=0;
         numberOfFactories = 1;
         numberOfMines = 0;
         numberOfDrones = 0;
         numberOfFragBosses = 0;
         for (i = 0; i < numberOfFactories; i ++)
         {
              factories[i].initialize(1,2000,75);
         }
     }
}

bool GameHandler::newLifeSequence(float t, float explosionTimer){
         torus.draw(t);
         torus2.draw(t);
         int i;
         for(i=0;i<numTorii;i++)
         {
              smallTorii[i].draw(t);
         }
         explosion1a.drawExplosion(explosionTimer);
         explosion2a.drawExplosion(explosionTimer);
         explosion3a.drawExplosion(explosionTimer);
         Vector position;
         newLifeTimer-=t;
          glPointSize(2);
          glColor4f(0.7,0.7,1,1);
         glBegin(GL_POINTS);
         if(newLifeTimer>90)
         {
             for(i=0;i<100;i++)
             {
                  playerDebris[i].setPosition(playerDebris[i].position.getX()+playerDebris[i].travelVector.getX()*t,playerDebris[i].position.getY()+playerDebris[i].travelVector.getY()*t,1);
                  playerDebris[i].travelVector.multiply(pow(0.95,t/2.0));
                  glVertex3f(playerDebris[i].position.getX(),playerDebris[i].position.getY(),1);
             }
         }
         else if (lives >=0)
         {
             for(i=0;i<100;i++)
             {
                  playerDebris[i].setPosition(playerDebris[i].position.getX()+playerDebris[i].travelVector.getX()*t,playerDebris[i].position.getY()+playerDebris[i].travelVector.getY()*t,1);
                  playerDebris[i].travelVector.multiply(pow(0.95,t/2.0));
                  glVertex3f(playerDebris[i].position.getX()+((cos(newLifeTimer/(90/3.14))+1)/2)*(100-playerDebris[i].position.getX()),playerDebris[i].position.getY()+((cos(newLifeTimer/(90/3.14))+1)/2)*(75-playerDebris[i].position.getY()),1);
             }
         }
         glEnd();
         position.set(100,75,0);
         for(i=numTorii;i<10;i++)
         {
              if(newLifeTimer<120-5*i && lives>=0)
              {
                  smallTorii[i].set(100, 75, 1, 75-5*i, 0.65+0.1*i, 20);
                  smallTorii[i].expanding=false;
                  smallTorii[i].color( 0, 0+0.1*(10-i), 0.8, 0.15 );
                  smallTorii[i].detail(30-2*i);
                  numTorii++;
              }
         }
         if(newLifeTimer<0)
         {

        SoundManager::playSoundEffect( SOUND_EFFECT::PLAYER_RESPAWN );
          playerInvinceTimer=maxInvince;
          torus.set(100, 75, 1, 100, 2, 30);
          torus.color( 0, 0, 0.8, 0.15 );
          torus.detail(30);

          explosion1a.setNumberParticles(50);
          explosion1a.setPosition(position.getX(), position.getY(), position.getZ());
          explosion1a.setParticleSize(5.0);
          explosion1a.setDuration(130);
          explosion1a.setRed(0.0);
          explosion1a.setGreen(0.8);
          explosion1a.setBlue(0.0);
          explosion1a.setSize(8);
          explosion1a.setDrawLightFlare(true);
          explosion1a.setLightFlareAlpha(0.6);
          explosion1a.initializeExplosion(explosionTimer);

          explosion2a.setNumberParticles(0);
          explosion2a.setPosition(position.getX(), position.getY(), position.getZ());
          explosion2a.setParticleSize(50.0);
          explosion2a.setDuration(140);
          explosion2a.setRed(0.2);
          explosion2a.setGreen(0.0);
          explosion2a.setBlue(0.8);
          explosion2a.setSize(6);
          explosion2a.setDrawLightFlare(false);
          explosion2a.initializeExplosion(explosionTimer);

          explosion3a.setNumberParticles(8);
          explosion3a.setPosition(position.getX(), position.getY(), position.getZ());
          explosion3a.setParticleSize(170.0);
          explosion3a.setDuration(100);
          explosion3a.setRed(0.2);
          explosion3a.setGreen(0.69);
          explosion3a.setBlue(1.0);
          explosion3a.setSize(5);
          explosion3a.setDrawLightFlare(false);
          explosion3a.initializeExplosion(explosionTimer);
             pushCenter.set(100,75,1);
             pushStrength=3.0;
             playerDeath=false;
             return true;
         }
         return false;
}

void GameHandler::killPlayer(float explosionTimer, Vector position){
         playerDeath=true;
         SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_LARGE);
         SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_ENORMOUS);
         SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_ENERGY);
         cameraShake=true;
         numTorii=0;
         pushCenter.set(position.getX(),position.getY(),1);
         playerDeathLoc.set(position.getX(),position.getY(),1);
         spawnPath.set(position.getX()-100,position.getY()-75,0);
         pushStrength=3.0;
         newLifeTimer=160.0;
     if(lives>=0)
     {
         int i;
         for(i=0;i<100;i++)
         {
              playerDebris[i].position.set(position.getX(),position.getY(),1);
              playerDebris[i].travelVector.set(0,0.1*(float)(rand()%40),0);
              playerDebris[i].travelVector.rotate('z',0.01*(float)rand());
         }
         torus2.set(100, 75, 1, 100, 0.65, 100);
         torus2.expanding=false;
         torus2.color( 0, 0, 0.8, 0.15 );
         torus2.detail(30);
     }
      torus.set(position.getX(), position.getY(), position.getZ(), 100, 2, 30);
      torus.color( 0, 0, 0.8, 0.15 );
      torus.detail(30);

      explosion1a.setNumberParticles(100);
      explosion1a.setPosition(position.getX(), position.getY(), position.getZ());
      explosion1a.setParticleSize(7.0);
      explosion1a.setDuration(130);
      explosion1a.setRed(0.0);
      explosion1a.setGreen(0.8);
      explosion1a.setBlue(0.0);
      explosion1a.setSize(8);
      explosion1a.setDrawLightFlare(true);
      explosion1a.setLightFlareAlpha(0.6);
      explosion1a.initializeExplosion(explosionTimer);

      explosion2a.setNumberParticles(0);
      explosion2a.setPosition(position.getX(), position.getY(), position.getZ());
      explosion2a.setParticleSize(50.0);
      explosion2a.setDuration(140);
      explosion2a.setRed(0.2);
      explosion2a.setGreen(0.0);
      explosion2a.setBlue(0.8);
      explosion2a.setSize(6);
      explosion2a.setDrawLightFlare(false);
      explosion2a.initializeExplosion(explosionTimer);

      explosion3a.setNumberParticles(10);
      explosion3a.setPosition(position.getX(), position.getY(), position.getZ());
      explosion3a.setParticleSize(200.0);
      explosion3a.setDuration(100);
      explosion3a.setRed(0.2);
      explosion3a.setGreen(0.69);
      explosion3a.setBlue(1.0);
      explosion3a.setSize(5);
      explosion3a.setDrawLightFlare(false);
      explosion3a.initializeExplosion(explosionTimer);
}

void GameHandler::gameOver(){
     // Reset variables
     cameraShake=false;
     cheatActive=false;
     numberOfDrones = 0;
     numberOfMines = 0;
     phaseCoolDown=75.0f;
     upgrade.isActive = false;

     lives = 5;
     score = 0;
     newLevel();
     gridFlashing=false;
     playerInvinceTimer=0;
     delete [] mines;
     delete [] fragBosses;
     delete [] factories;
     delete [] drones;
}
