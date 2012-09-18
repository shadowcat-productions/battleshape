/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Nuke.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Nuke class --------------------
*/

#include "Nuke.h"
#include "SoundManager.h"
#include "Sounds.h"


/*
 -------------------- Constructors for the Nuke class --------------------
*/
Nuke::Nuke() {

}

/*
 -------------------- Destructor for the Nuke class --------------------
*/
Nuke::~Nuke() {
}

/*
 -------------------- Modifiers for the Nuke class --------------------
*/
void Nuke::setNuke(GLfloat posx, GLfloat posy, GLfloat movx, GLfloat movy, GLfloat mov2x, GLfloat mov2y, GLfloat size) {
     range=size;
    isActive = true;
    isShrap = false;
    propulsion.reLoad();
    speed = 1.2;
    acceleration=1.02;
    damage=10;
    explosionRadius = 80.0;
    pushRadius=120.0;
    pushStrength=5.0;
    position.set(posx, posy, 1);
    GLfloat normx, normy, length;
    currentRotation = 0;

    direction.set(movx,movy,0);
    movement.set(mov2x, mov2y, 0);
}

int Nuke::updateNuke(float t, float explosionTimer, Drone enemies[], FragMine mines[], Factory factories[], FragBoss fragBosses[], int numberOfEnemies, int numberOfMines, int numberOfFactories, int numberOfFragBosses) {
     if(isActive==true && isShrap==false)
     {
         drawPropulsion(t);
         position.set(position.getX() + movement.getX()*t, position.getY() + movement.getY()*t, 1 );
         direction.normalize();
         direction.multiply(pow(acceleration,t)/10);
         Vector addVector;
         addVector.set(direction.getX() / 2, direction.getY() / 2, direction.getZ());
         addVector.multiply(t/2);
         movement.add(addVector);

         int score = 0;
         bool flag=false;

         if(hitSides())
             flag = true;
             
         if(hitEnemy(enemies, numberOfEnemies))
             flag = true;
             
         if(hitMine(mines, numberOfMines))
             flag = true;
             
         if(hitFactory(factories, numberOfFactories))
             flag = true;
             
         if(hitFragBoss(fragBosses, numberOfFragBosses))
             flag = true;
             
         if(flag)
             score = detonate(enemies, numberOfEnemies, mines, numberOfMines, factories, numberOfFactories, fragBosses, numberOfFragBosses);

         return score;
     }
     if(isActive == true && isShrap == true){
          isActive = false;


          torus.set(position.getX(), position.getY(), position.getZ(), 100, 2, 30);
          torus.color( 0, 0, 0.8, 0.15 );
          torus.detail(30);

          explosion.setNumberParticles(100);
          explosion.setPosition(position.getX(), position.getY(), position.getZ());
          explosion.setParticleSize(7.0);
          explosion.setDuration(130);
          explosion.setRed(0.8);
          explosion.setGreen(0.0);
          explosion.setBlue(0.0);
          explosion.setSize(8);
          explosion.setDrawLightFlare(true);
          explosion.setLightFlareAlpha(0.6);
          explosion.initializeExplosion(explosionTimer);

          explosion2.setNumberParticles(0);
          explosion2.setPosition(position.getX(), position.getY(), position.getZ());
          explosion2.setParticleSize(50.0);
          explosion2.setDuration(140);
          explosion2.setRed(0.2);
          explosion2.setGreen(0.0);
          explosion2.setBlue(0.8);
          explosion2.setSize(6);
          explosion2.setDrawLightFlare(false);
          explosion2.initializeExplosion(explosionTimer);

          explosion3.setNumberParticles(10);
          explosion3.setPosition(position.getX(), position.getY(), position.getZ());
          explosion3.setParticleSize(200.0);
          explosion3.setDuration(100);
          explosion3.setRed(1.0);
          explosion3.setGreen(0.69);
          explosion3.setBlue(0.2);
          explosion3.setSize(5);
          explosion3.setDrawLightFlare(false);
          explosion3.initializeExplosion(explosionTimer);
     }
     if(isActive == false)
     {
         torus.draw(t);
         explosion.drawExplosion(explosionTimer);
         explosion2.drawExplosion(explosionTimer);
         explosion3.drawExplosion(explosionTimer);
         for (int i = 0 ; i < 100; i++){
             trail[i].updateParticle( t );
             trail[i].drawParticle(1);
         }
     }
     return 0;
}

int Nuke::detonate(Drone enemies[], int numberOfEnemies, FragMine mines[], int numberOfMines, Factory factories[], int numberOfFactories, FragBoss fragBosses[], int numberOfFragBosses)
{
    int explosionCheck = 0;
    int explosionCheck2 = 0;
    float pushDistance;
    Vector helperVector;
    int score = 1;
    for (explosionCheck = 0; explosionCheck < numberOfEnemies; explosionCheck ++)
    {
         if(enemies[explosionCheck].isAlive==true)
         {                   
            float distance = sqrt(pow((enemies[explosionCheck].position.getX() - position.getX()),2) + pow((enemies[explosionCheck].position.getY() - position.getY()),2));

            if (distance < explosionRadius)
            {
               if(enemies[explosionCheck].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
               {
                   score += enemies[explosionCheck].getPointValue();
               }
            }
            else if(distance<pushRadius)
            {
                 enemies[explosionCheck].appliedForce.add((enemies[explosionCheck].position.getX()-position.getX())*(pushStrength-pushStrength*(distance/pushRadius))/distance,(enemies[explosionCheck].position.getY()-position.getY())*(pushStrength-pushStrength*(distance/pushRadius))/distance,0.0);
            }
         }
    }

    for (explosionCheck = 0; explosionCheck < numberOfMines; explosionCheck ++){
        if(mines[explosionCheck].isAlive==true && mines[explosionCheck].isShrapnel==false )
        {
            float distance = sqrt(pow((mines[explosionCheck].position.getX() - position.getX()),2) + pow((mines[explosionCheck].position.getY() - position.getY()),2));

            if (distance < explosionRadius){
               if(mines[explosionCheck].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
               {
                score += mines[explosionCheck].getPointValue();
               }
            }
        }
        else if(mines[explosionCheck].isAlive==true && mines[explosionCheck].isComplete==false )
        {
             for (explosionCheck2 = 0; explosionCheck2 < mines[explosionCheck].numberOfDrones; explosionCheck2 ++)
             {
                float distance = sqrt(pow((mines[explosionCheck].children[explosionCheck2].position.getX() - position.getX()),2) + pow((mines[explosionCheck].children[explosionCheck2].position.getY() - position.getY()),2));

                if (distance < explosionRadius){
                   if(mines[explosionCheck].damageChild(explosionCheck2, damage)) // returns true when the enemy dies, so pass the point value up
                   {
                    score += mines[explosionCheck].children[explosionCheck2].getPointValue();
                   }
                }
                else if(distance<pushRadius)
                {
                     mines[explosionCheck].children[explosionCheck2].appliedForce.add((mines[explosionCheck].children[explosionCheck2].position.getX()-position.getX())*(pushStrength-pushStrength*(distance/pushRadius))/distance,(mines[explosionCheck].children[explosionCheck2].position.getY()-position.getY())*(pushStrength-pushStrength*(distance/pushRadius))/distance,0.0);
                }
             }
        }
    }
    for (explosionCheck = 0; explosionCheck < numberOfFactories; explosionCheck ++){
        if(factories[explosionCheck].isAlive==true && factories[explosionCheck].isShrapnel==false )
        {
            float distance = sqrt(pow((factories[explosionCheck].position.getX() - position.getX()),2) + pow((factories[explosionCheck].position.getY() - position.getY()),2));

            if (distance < explosionRadius){
               if(factories[explosionCheck].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
               {
                score += factories[explosionCheck].getPointValue();
               }
            }
        }
             for (explosionCheck2 = 0; explosionCheck2 < factories[explosionCheck].numberOfDrones; explosionCheck2 ++)
             {
                float distance = sqrt(pow((factories[explosionCheck].children[explosionCheck2].position.getX() - position.getX()),2) + pow((factories[explosionCheck].children[explosionCheck2].position.getY() - position.getY()),2));

                if (distance < explosionRadius){
                   if(factories[explosionCheck].damageChild(explosionCheck2, damage)) // returns true when the enemy dies, so pass the point value up
                   {
                    score += factories[explosionCheck].children[explosionCheck2].getPointValue();
                   }
                }
                else if(distance<pushRadius)
                {
                     factories[explosionCheck].children[explosionCheck2].appliedForce.add((factories[explosionCheck].children[explosionCheck2].position.getX()-position.getX())*(pushStrength-pushStrength*(distance/pushRadius))/distance,(factories[explosionCheck].children[explosionCheck2].position.getY()-position.getY())*(pushStrength-pushStrength*(distance/pushRadius))/distance,0.0);
                }
             }
    }

    if(numberOfFragBosses>0){
        if(fragBosses[0].isAlive==true && fragBosses[0].isShrapnel==false )
        {
           for (explosionCheck = 0; explosionCheck < fragBosses[0].numberOfFactories; explosionCheck ++){
                if(fragBosses[0].factories[explosionCheck].isAlive==true && fragBosses[0].factories[explosionCheck].isShrapnel==false )
                {
                    float distance = sqrt(pow((fragBosses[0].factories[explosionCheck].position.getX() - position.getX()),2) + pow((fragBosses[0].factories[explosionCheck].position.getY() - position.getY()),2));
        
                    if (distance < explosionRadius && fragBosses[0].spawnTimer<0.0){
                       if(fragBosses[0].factories[explosionCheck].takeDamage(2)) // returns true when the enemy dies, so pass the point value up
                       {
                        score += fragBosses[0].factories[explosionCheck].getPointValue();
                       }
                    }
                }
                     for (explosionCheck2 = 0; explosionCheck2 < fragBosses[0].factories[explosionCheck].numberOfDrones; explosionCheck2 ++)
                     {
                        float distance = sqrt(pow((fragBosses[0].factories[explosionCheck].children[explosionCheck2].position.getX() - position.getX()),2) + pow((fragBosses[0].factories[explosionCheck].children[explosionCheck2].position.getY() - position.getY()),2));
        
                        if (distance < explosionRadius){
                           if(fragBosses[0].factories[explosionCheck].damageChild(explosionCheck2, damage)) // returns true when the enemy dies, so pass the point value up
                           {
                            score += fragBosses[0].factories[explosionCheck].children[explosionCheck2].getPointValue();
                           }
                        }
                        else if(distance<pushRadius)
                        {
                             fragBosses[0].factories[explosionCheck].children[explosionCheck2].appliedForce.add((fragBosses[0].factories[explosionCheck].children[explosionCheck2].position.getX()-position.getX())*(pushStrength-pushStrength*(distance/pushRadius))/distance,(fragBosses[0].factories[explosionCheck].children[explosionCheck2].position.getY()-position.getY())*(pushStrength-pushStrength*(distance/pushRadius))/distance,0.0);
                        }
                     }
            }
            float distance = sqrt(pow((fragBosses[0].position.getX() - position.getX()),2) + pow((fragBosses[0].position.getY() - position.getY()),2));

            if (distance < explosionRadius){
               if(fragBosses[0].takeDamage(damage)) // returns true when the enemy dies, so pass the point value up
               {
                score += fragBosses[0].getPointValue();
               }
            }
            if(distance<pushRadius)
            {
                 pushStrength=pushStrength/3;
                 fragBosses[0].appliedForce.add((fragBosses[0].position.getX()-position.getX())*(pushStrength-pushStrength*(distance/pushRadius))/distance,(fragBosses[0].position.getY()-position.getY())*(pushStrength-pushStrength*(distance/pushRadius))/distance,0.0);
                 pushStrength=pushStrength*3;
            }
        }
        if(fragBosses[0].isAlive==true && (fragBosses[0].isComplete==false || fragBosses[0].type==1) )
        {
             for (explosionCheck2 = 0; explosionCheck2 < fragBosses[0].numberOfDrones; explosionCheck2 ++)
             {
                float distance = sqrt(pow((fragBosses[0].children[explosionCheck2].position.getX() - position.getX()),2) + pow((fragBosses[0].children[explosionCheck2].position.getY() - position.getY()),2));

                if (distance < explosionRadius){
                   if(fragBosses[0].damageChild(explosionCheck2, damage)) // returns true when the enemy dies, so pass the point value up
                   {
                    score += fragBosses[0].children[explosionCheck2].getPointValue();
                   }
                }
                else if(distance<pushRadius)
                {
                     fragBosses[0].children[explosionCheck2].appliedForce.add((fragBosses[0].children[explosionCheck2].position.getX()-position.getX())*(pushStrength-pushStrength*(distance/pushRadius))/distance,(fragBosses[0].children[explosionCheck2].position.getY()-position.getY())*(pushStrength-pushStrength*(distance/pushRadius))/distance,0.0);
                }
             }
        }
    }
    SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_LARGE);
    SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_ENORMOUS);
    SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_ENERGY);
    return score;
}

bool Nuke::hitEnemy(Drone enemies[], int numberOfEnemies) {
     int iHit;
     for (iHit = 0; iHit < numberOfEnemies; iHit ++)
     {
         if(enemies[iHit].isAlive==true)
         {
              if (enemies[iHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
              {
                   isActive=true;
                   isShrap=true;

                   //set up explosion
                   return true;
              }
         }
     }
     return false;
}

bool Nuke::hitMine(FragMine mines[], int numberOfMines) {
     int iHit, jHit;
     for (iHit = 0; iHit < numberOfMines; iHit ++)
     {
         if(mines[iHit].isAlive==true && mines[iHit].isComplete==true)
         {
              if(mines[iHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
              {
                   isActive=true;
                   isShrap=true;

                   //set up explosion
                   return true;
              }
         }
         else if(mines[iHit].isAlive==true && mines[iHit].isComplete==false)
         {
             for (jHit = 0; jHit < mines[iHit].numberOfDrones; jHit ++)
             {
                 if(mines[iHit].children[jHit].isAlive==true)
                 {
                      if (mines[iHit].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
                      {
                           isActive=true;
                           isShrap=true;

                           //set up explosion
                           return true;
                      }
                 }
             }
         }
     }
     return false;
}

bool Nuke::hitFactory(Factory mines[], int numberOfMines) {
     int iHit, jHit;
     for (iHit = 0; iHit < numberOfMines; iHit ++)
     {
         if(mines[iHit].isAlive==true && mines[iHit].isComplete==true)
         {
              if(mines[iHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
              {
                   isActive=true;
                   isShrap=true;

                   //set up explosion
                   return true;
              }
         }
             for (jHit = 0; jHit < mines[iHit].numberOfDrones; jHit ++)
             {
                 if(mines[iHit].children[jHit].isAlive==true)
                 {
                      if (mines[iHit].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
                      {
                           isActive=true;
                           isShrap=true;

                           //set up explosion
                           return true;
                      }
                 }
             }
     }
     return false;
}


bool Nuke::hitFragBoss(FragBoss mines[], int numberOfMines) {
     int iHit, jHit;
     if(numberOfMines>0)
     {
         iHit=0;
         if(mines[iHit].isAlive==true && mines[iHit].isComplete==true)
         {
        		for (iHit = 0; iHit < mines[0].numberOfFactories; iHit ++)
        		{
        			if(mines[0].factories[iHit].isAlive==true && mines[0].factories[iHit].isShrapnel==false )
        			{
        				if (mines[0].factories[iHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
        				{
                            isActive=true;
                            isShrap=true;
                            return true;
        				} 
        			}
                    for (jHit = 0; jHit < mines[0].factories[iHit].numberOfDrones; jHit ++)
                    {
                        if(mines[0].factories[iHit].children[jHit].isAlive==true && mines[0].factories[iHit].children[jHit].isShrapnel==false )
                        {
                            if (mines[0].factories[iHit].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
                            {
        					   isActive=true;
        					   isShrap=true;
        					   return true;
                            }
                        }
                    }
        		}
              iHit=0;
              if(mines[iHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
              {
                   isActive=true;
                   isShrap=true;

                   //set up explosion
                   return true;
              }
         }
         iHit=0;
         if(mines[iHit].isAlive==true && (mines[iHit].isComplete==false || mines[iHit].type==1))
         {
             for (jHit = 0; jHit < mines[iHit].numberOfDrones; jHit ++)
             {
                 if(mines[iHit].children[jHit].isAlive==true)
                 {
                      if (mines[iHit].children[jHit].hitDetect(position.getX(),position.getY(),position.getZ(),range))
                      {
                           isActive=true;
                           isShrap=true;

                           //set up explosion
                           return true;
                      }
                 }
             }
         }
     }
     return false;
}

bool Nuke::hitSides() {
    // If the shot hits a wall, explode.
   int i;
   int score = 0;

   if (position.getX() < 0 || position.getX() > 200 || position.getY() < 0 || position.getY() > 150) 
   {
        isActive = true;
        isShrap = true;
        return true;
    }

    return false;
}

void Nuke::drawNuke( float t ) {
     bool leftSide = false;
     float dot;
     float theta;
     currentRotation += t;
    Vector up;
    up.set(0,1,0);
     if(isActive){
                  leftSide = false;
                  theta = up.angleBetween(direction);
                  if ( direction.getX() < 0 ) {
                       leftSide = true;
                  }
                  glPushMatrix();
                  glLineWidth( 1 );
                  glTranslatef( position.getX(), position.getY(), 1 );
                  
                  if ( leftSide )
                       glRotatef( theta*180 / 3.14159, 0.0, 0.0, 1.0 );
                  else
                       glRotatef( -theta*180 / 3.14159, 0.0, 0.0, 1.0 );
                  glRotatef( -90.0, 1.0, 0.0, 0.0 );
                  glRotatef(currentRotation,0,0,1);
                  glScalef(0.5,0.5,0.5);
                  
                  glColor4f( 1.0, 1.0, 1.0, 0.8 );
                  
                  glPushMatrix();
                  glScalef(1,0.001,1);
                  glutSolidCone( 3, 3, 4, 1);
                  glPopMatrix();
                  glPushMatrix();
                  glScalef(0.001,1,1);
                  glutSolidCone( 3, 3, 4, 1);
                  glPopMatrix();


                  int segments=6;
                  float height=5.0;
                  float width=1.0;
                  
                  Vector drawHelper;
                  drawHelper.set(width,0,0);
                  int i;
                  glBegin(GL_QUAD_STRIP);
                  for(i=0;i<segments;i++)
                  {
                      glVertex3f(drawHelper.getX(),drawHelper.getY(),0);
                      glVertex3f(drawHelper.getX(),drawHelper.getY(),height);
                      drawHelper.rotate('z',3.14159*2/segments);
                  }
                  glEnd();
                  
                  glTranslatef(0,0,5.0);
                  glColor4f( 1.0, 0.0, 0.0, 0.8 );
                  glutSolidCone( 1, 2, 4, 1 );
                  
                  glPopMatrix();
     }
}

void Nuke::drawPropulsion(float t){
        if (direction.getLength()>0.0) propulsion.updatePropulsion(t, position, direction, true,false);
        else propulsion.updateRipples(t, position, true, 0.8, 0.2, 0.2);
}
