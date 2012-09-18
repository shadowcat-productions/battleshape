/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Shot.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Shot class --------------------
*/

#include "Shot.h"
#include "SoundManager.h"
#include "Sounds.h"

/*
 -------------------- Constructors for the Shot class --------------------
*/
Shot::Shot() {

}

/*
 -------------------- Destructor for the Shot class --------------------
*/
Shot::~Shot() {
}

/*
 -------------------- Modifiers for the Shot class --------------------
*/
void Shot::setShot(GLfloat posx, GLfloat posy, GLfloat movx, GLfloat movy) {
    upgradeLevel=0;
    isActive = true;
    isPenetrating = false;
    isShrap = false;
    isBounce = false;
    isStar = false;
    hasExploded=false;
    bounceCount = 3;
    starTimer = 0;
    speed = 2;
    position.set(posx, posy, 1);
    starPosition.set(movx+posx, movy+posy, 600);
    GLfloat normx, normy, length;
    length = pow((double)(pow((double)movx,2.0) + pow((double)movy,2.0)),0.5);
    normx = movx / length;
    normy = movy / length;
    damage=1.001;
    movement.set(normx*speed, normy*speed, 0);
    currentExpansion = 1;
    anyActive = false;
}

int Shot::updateShot(float t, float explosionTimer, Drone enemies[], FragMine mines[], Factory factories[], FragBoss fragBosses[], int numberOfEnemies, int numberOfMines, int numberOfFactories, int numberOfFragBosses) {
     if(isActive==true && isShrap==false && isStar == false)
     {
         int returnValue=0;
         float tempTimer=0.0;
         while(tempTimer<t)
         {
             tempTimer+=0.834;
             if(isActive==true && isShrap==false)
             {
                 if(tempTimer<t)
                 {
                     position.set(position.getX() + movement.getX()*0.833, position.getY() + movement.getY()*0.833, 1 );
                     hitSides();
                     returnValue+= hitMine(mines, numberOfMines, isPenetrating) + hitEnemy(enemies, numberOfEnemies, isPenetrating) + hitFactory(factories, numberOfFactories, isPenetrating)+ hitFragBoss(fragBosses, numberOfFragBosses, isPenetrating);
                 }
                 else
                 {
                     position.set(position.getX() + movement.getX()*((tempTimer-t)+0.833), position.getY() + movement.getY()*((tempTimer-t)+0.833), 1 );
                     hitSides();
                     returnValue+= hitMine(mines, numberOfMines, isPenetrating) + hitEnemy(enemies, numberOfEnemies, isPenetrating) + hitFactory(factories, numberOfFactories, isPenetrating)+ hitFragBoss(fragBosses, numberOfFragBosses, isPenetrating);
                 }
             }
         }
         if(isShrap && bounceCount > 0 && isBounce)
         {
               // INSERT COOL BOUNCING NOISE HERE!
               isShrap=false;
               movement.rotate('z',rand());
               bounceCount --;
               SoundManager::playSoundEffect( SOUND_EFFECT::BOING );
               
         }
         return returnValue;
     }else if(isActive==true && isShrap==true && isStar == false){
          isActive = false;
          explosion.setNumberParticles(80);
          explosion.setPosition(position.getX(), position.getY(), position.getZ());
          explosion.setParticleSize(1.5);
          explosion.setDuration(70);
          explosion.setRed(1.0);
          explosion.setGreen(0.0);
          explosion.setBlue(0.0);
          explosion.setSize(3);
          explosion.setDrawLightFlare(false);
          explosion.initializeExplosion(explosionTimer);
     }
     else if(isActive==false && isStar == false)
     {
         explosion.drawExplosion(explosionTimer);
     }
     else if(isStar && isShrap && !hasExploded)
     {
          hasExploded=true;
          // Kaboom goes the star!
          Nuke explosionHelper;
          explosionHelper.setNuke( starPosition.getX(), starPosition.getY(), 0, 0, 0,0, 0);
          explosionHelper.explosionRadius=25;
          explosionHelper.pushRadius=75;
          explosionHelper.pushStrength=2;
          explosionHelper.detonate(enemies, numberOfEnemies, mines, numberOfMines, factories, numberOfFactories, fragBosses, numberOfFragBosses);
          delete [] &explosionHelper;
     }
     return 0;
}

int Shot::hitEnemy(Drone enemies[], int numberOfEnemies, bool penetratingShot) {
     int iHit;
     int score=0;
     for (iHit = 0; iHit < numberOfEnemies; iHit ++)
     {
         if(enemies[iHit].isAlive==true)
         {
             if(enemies[iHit].hitDetect(position.getX(),position.getY(),position.getZ()))
             {
                    if(!penetratingShot)
                    {
                       isActive=true;
                       isShrap=true;
                    }                      
                    if(enemies[iHit].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
                    {
                        score+= enemies[iHit].getPointValue(); 
                    }  
                    if(!penetratingShot)
                    {
                       break;
                    }                   
             }
         }        
     }
     return score;
}

int Shot::hitFactory(Factory mines[], int numberOfMines, bool penetratingShot) {
     int iHit, jHit;
     int score = 0;
     for (iHit = 0; iHit < numberOfMines; iHit ++)
     {
         if(mines[iHit].isAlive==true && mines[iHit].isShrapnel==false )
         {
              if (mines[iHit].hitDetect(position.getX(),position.getY(),position.getZ()))
              {
                    if(!penetratingShot)
                    {
                       isActive=true;
                       isShrap=true;
                    }                      
                    if(mines[iHit].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
                    {
                        score += mines[iHit].getPointValue(); 
                    }
                    if(!penetratingShot)
                    {
                       break;
                    }
              } 
         }
             for (jHit = 0; jHit < mines[iHit].numberOfDrones; jHit ++)
             {
                 if(mines[iHit].children[jHit].isAlive==true && mines[iHit].children[jHit].isShrapnel==false )
                 {
                     if (mines[iHit].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ()))
                     {
                        if(!penetratingShot)
                        {
                           isActive=true;
                           isShrap=true;
                        }                      
                        if(mines[iHit].damageChild(jHit,damage)) // returns true when the enemy dies, so pass the point value up
                        {
                            score += mines[iHit].children[jHit].getPointValue(); 
                        }     
                        if(!penetratingShot)
                        {
                           break;
                        }
                     }
                 }
             }
     }
     return score;
}

int Shot::hitMine(FragMine mines[], int numberOfMines, bool penetratingShot) {
     int iHit, jHit;
     int score=0;
     for (iHit = 0; iHit < numberOfMines; iHit ++)
     {
         if(mines[iHit].isAlive==true && mines[iHit].isShrapnel==false )
         {
              if (mines[iHit].hitDetect(position.getX(),position.getY(),position.getZ()))
              {
                    if(!penetratingShot)
                    {
                       isActive=true;
                       isShrap=true;
                    }                      
                    if(mines[iHit].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
                    {
                        score+= mines[iHit].getPointValue(); 
                    }
                    if(!penetratingShot)
                    {
                       break;
                    }
              } 
         }
         else if(mines[iHit].isAlive==true && mines[iHit].isComplete==false)
         {
             for (jHit = 0; jHit < mines[iHit].numberOfDrones; jHit ++)
             {
                 if(mines[iHit].children[jHit].isAlive==true && mines[iHit].children[jHit].isShrapnel==false )
                 {
                     if (mines[iHit].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ()))
                     {
                        if(!penetratingShot)
                        {
                           isActive=true;
                           isShrap=true;
                        }                      
                        if(mines[iHit].damageChild(jHit,damage)) // returns true when the enemy dies, so pass the point value up
                        {
                            score+= mines[iHit].children[jHit].getPointValue(); 
                        }     
                        if(!penetratingShot)
                        {
                           break;
                        }
                     }
                 }
             }
         }
     }
     return score;
}

int Shot::hitFragBoss(FragBoss fragBosses[], int numberOfFragBosses, bool penetratingShot) {
    int iHit,jHit;
    int score=0;
     if(numberOfFragBosses==1)
     {
         if(fragBosses[0].isAlive==true && fragBosses[0].isShrapnel==false )
         {
             for (iHit = 0; iHit < fragBosses[0].numberOfFactories; iHit ++)
             {
                 if(fragBosses[0].factories[iHit].isAlive==true && fragBosses[0].factories[iHit].isShrapnel==false )
                 {
                      if (fragBosses[0].factories[iHit].hitDetect(position.getX(),position.getY(),position.getZ()))
                      {
                            if(!penetratingShot)
                            {
                               isActive=true;
                               isShrap=true;
                            }                      
                            if(fragBosses[0].factories[iHit].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
                            {
                                score += fragBosses[0].factories[iHit].getPointValue(); 
                            }
                            if(!penetratingShot)
                            {
                               break;
                            }
                      } 
                 }
                 for (jHit = 0; jHit < fragBosses[0].factories[iHit].numberOfDrones; jHit ++)
                 {
                     if(fragBosses[0].factories[iHit].children[jHit].isAlive==true && fragBosses[0].factories[iHit].children[jHit].isShrapnel==false )
                     {
                         if (fragBosses[0].factories[iHit].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ()))
                         {
                            if(!penetratingShot)
                            {
                               isActive=true;
                               isShrap=true;
                            }                      
                            if(fragBosses[0].factories[iHit].damageChild(jHit,damage)) // returns true when the enemy dies, so pass the point value up
                            {
                                score += fragBosses[0].factories[iHit].children[jHit].getPointValue(); 
                            }     
                            if(!penetratingShot)
                            {
                               break;
                            }
                         }
                     }
                  }
              }
              if (fragBosses[0].hitDetect(position.getX(),position.getY(),position.getZ()))
              {              
                    isActive=true;
                    isShrap=true;
                    if(fragBosses[0].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
                    {
                        score+= fragBosses[0].getPointValue(); 
                    }
              }              
         }

         for (jHit = 0; jHit < fragBosses[0].numberOfDrones; jHit ++)
         {
             if(fragBosses[0].children[jHit].isAlive==true && fragBosses[0].children[jHit].isShrapnel==false )
             {
                 if (fragBosses[0].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ()))
                 {
                    if(!penetratingShot)
                    {
                       isActive=true;
                       isShrap=true;
                    }                      
                    if(fragBosses[0].damageChild(jHit,damage)) // returns true when the enemy dies, so pass the point value up
                    {
                        score+= fragBosses[0].children[jHit].getPointValue(); 
                    }     
                 }
             }
         }
     }
     return score;
}

void Shot::hitSides() {
    // If the shot hits a wall, explode.

   if(upgradeLevel != 4)
   {
        if (position.getX() < 0) position.set(0,position.getY(),position.getZ());
        if (position.getX() > 200) position.set(200, position.getY(), position.getZ());
        if (position.getY() < 0) position.set(position.getX(),0,position.getZ());
        if (position.getY() > 150) position.set(position.getX(), 150, position.getZ());


        if (!isBounce)
        {
             if (position.getX() <= 0 || position.getX() >= 200 || position.getY() <= 0 || position.getY() >= 150)
             {
               isActive=true;
               isShrap=true;
              // upgradeLevel = 0;
             }
        }
        else if (isBounce)
        {
             if (position.getX() <= 0) movement.set(-movement.getX(), movement.getY(), movement.getZ());
             if (position.getX() >= 200) movement.set(-movement.getX(), movement.getY(), movement.getZ());
             if (position.getY() <= 0) movement.set(movement.getX(), -movement.getY(), movement.getZ());
             if (position.getY() >= 150) movement.set(movement.getX(), -movement.getY(), movement.getZ());
        }
   }

}

