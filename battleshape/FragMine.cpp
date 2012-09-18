/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the basic FragMine.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the FragMine class --------------------
*/
#include "FragMine.h"


/*
 -------------------- Constructors for the FragMine class --------------------
*/
FragMine::FragMine() : isAlive(false), isShrapnel(false), isComplete(false), size(4.0)
{
     setHealth(1.0);
     setPointValue(1);
     position.set(-70.0, 0.0, 1.0);
     movement.set(0.002, 0.0, 0.0);
     direction.set(0.0, 1.0, 0.0);
}

void FragMine::initialize(int newType) {
     type=newType;
          isComplete=true;
     if(type==0)
     {
         numberOfDrones = 8;
         int i;
         for(i=0;i<numberOfDrones;i++)
         {
              children[i].initialize(4);
         }

         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=float((rand() % 2000))/200;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         size = 5.0;
         speed=0.0;
         spinSpeed=-2.0;
     }
     if(type==1) // clockwise rotators
     {
         numberOfDrones = 8;
         int i;
         for(i=0;i<numberOfDrones;i++)
         {
              children[i].initialize(4);
         }

         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=float((rand() % 2000))/200;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         size = 5.0;
         speed=0.3;
         spinSpeed=3.0;
     }
}

void FragMine::initialize(int newType, float x, float y) {
     type=newType;
          isComplete=true;
     if(type==0)
     {
         wasDestroyed=false;
         didExplode=false;
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }

         numberOfDrones = 8;

         for(i=0;i<numberOfDrones;i++)
         {
              children[i].initialize(4);
         }

         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=5;
         position.set(x,y,1);
         size = 5.0;
         speed=0.0;
         spinSpeed=-2.0;
     }
     if(type==1)
     {
         wasDestroyed=false;
         didExplode=false;
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }

         numberOfDrones = 8;

         for(i=0;i<numberOfDrones;i++)
         {
              children[i].initialize(4);
         }

         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=5;
         position.set(x,y,1);
         size = 5.0;
         speed=0.3;
         spinSpeed=3.0;
     }
}

void FragMine::initialize(int newType, float x, float y, float xDir, float yDir) {
     type=newType;
          isComplete=true;
     if(type==0)
     {
         wasDestroyed=false;
         didExplode=false;
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }

         numberOfDrones = 8;

         for(i=0;i<numberOfDrones;i++)
         {
              children[i].initialize(4);
         }

         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=5;
         position.set(x,y,1);
         size = 5.0;
         speed=0.0;
         spinSpeed=-2.0;
     }
     if(type==1)
     {
         wasDestroyed=false;
         didExplode=false;
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }

         numberOfDrones = 8;

         for(i=0;i<numberOfDrones;i++)
         {
              children[i].initialize(4);
         }

         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=5;
         position.set(x,y,1);
         direction.set(xDir,yDir,0);
         size = 5.0;
         speed=0.3;
         spinSpeed=-3.0;
         spinReversed=true;
     }
}

/*
 -------------------- Destructor for the FragMine class --------------------
*/
FragMine::~FragMine(){
}

/*
 -------------------- Accessors for the FragMine class --------------------
*/
//returns the health of the FragMine
const GLfloat FragMine::getHealth() const{
     return health;
}

//returns the point value of the FragMine
GLint FragMine::getPointValue(){
      int tempScore = 0;
      if(!isComplete)
      {
          tempScore=pointValue;
          pointValue=0;
      }
      return tempScore;
}

/*
 -------------------- Modifiers for the FragMine class --------------------
*/
//sets the health for the FragMine
void FragMine::setHealth(GLfloat newHealth){
     health = newHealth;
}

//sets the point value for the FragMine
void FragMine::setPointValue(GLint newPointValue){
     pointValue = newPointValue;
}

/*
 -------------------- Methods for the FragMine class --------------------
*/


bool FragMine::updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ){
     if(spawnTimer>=0.0)
     {spawnTimer-=t;}
     if(isAlive==true && isShrapnel==false)
     {
         Vector movementTemp;
         if (type == 0)
         {
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(movementTemp.normalize()<size)
                 return true;
             movement.set(movementTemp.getX()*speed, movementTemp.getY()*speed, 0.0);
             position.set( position.getX()+movement.getX()*t, position.getY()+movement.getY()*t, 1 );
             if(spinReversed)
                 currentRotation+=t*spinSpeed*0.01;
             else
                 currentRotation-=t*spinSpeed*0.01;

             Vector rotation;
             if(spawnTimer<=0.0)
                 rotation.set(3.9,0,0);
             else
                 rotation.set(3.9*(1-(spawnTimer/maxSpawnTimer)),0,0);
             rotation.rotate('z',currentRotation);
             int i;
             for(i=0;i<numberOfDrones;i++)
             {
                  rotation.rotate('z',3.14159/4);
                  children[i].position.set(position.getX()+rotation.getX(),position.getY()+rotation.getY(),1);
                  children[i].movement.set(rotation.getX(),rotation.getY(),0);
                  children[i].movement.normalize();
             }
         }
         if (type == 1)
         {
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(movementTemp.normalize()<size)
                 return true;
             movement.set(direction.getX()*speed, direction.getY()*speed, 0.0);
             position.set( position.getX()+movement.getX()*t, position.getY()+movement.getY()*t, 1 );
             float threshhold = 5;
             if(direction.getY()<-0.5)
             {
                if(position.getY()<threshhold)
                {
                   position.set(position.getX(),threshhold,position.getZ());
                   direction.rotate('z',3.14159/2);
                }
             }
             else if(direction.getY()>0.5)
             {
                if(position.getY()>150-threshhold)
                {
                   position.set(position.getX(),150-threshhold,position.getZ());
                   direction.rotate('z',3.14159/2);
                }
             }
             else if(direction.getX()<-0.5)
             {
                if(position.getX()<threshhold)
                {
                   position.set(threshhold,position.getY(),position.getZ());
                   direction.rotate('z',3.14159/2);
                }
             }
             else if(direction.getX()>0.5)
             {
                if(position.getX()>200-threshhold)
                {
                   position.set(200-threshhold,position.getY(),position.getZ());
                   direction.rotate('z',3.14159/2);
                }
             }

             if(spinReversed)
                 currentRotation+=t*spinSpeed*0.01;
             else
                 currentRotation-=t*spinSpeed*0.01;

             Vector rotation;
             if(spawnTimer<=0.0)
                 rotation.set(3.9,0,0);
             else
                 rotation.set(3.9*(1-(spawnTimer/maxSpawnTimer)),0,0);
             rotation.rotate('z',currentRotation);
             int i;
             for(i=0;i<numberOfDrones;i++)
             {
                  rotation.rotate('z',3.14159/4);
                  children[i].position.set(position.getX()+rotation.getX(),position.getY()+rotation.getY(),1);
                  children[i].movement.set(rotation.getX(),rotation.getY(),0);
                  children[i].movement.normalize();
             }
         }
     }
     else if(isAlive==true && isShrapnel==true){
         updateStatus();
         if (type == 0 || type ==1)
         {
             bool hit=false;
             int i;
             for(i=0;i<numberOfDrones;i++)
             {
                  if(children[i].updatePosition(t, playerX, playerY, playerZ))
                  {
                      hit=true;
                      damageChild(i,100);
                  }
             }
             return hit;
         }
     }
     return false;
}

void FragMine::draw(const GLuint& sparkTexture, float timer, float explosionTimer) {
     int i;

     for (i=0;i<30;i++)
     {
         if(spawnDebris[i].getDuration()>0)
         {
            glPushMatrix();
             spawnDebris[i].setDuration(spawnDebris[i].getDuration()-timer);
             spawnDebris[i].setAlpha(spawnDebris[i].getDuration()/spawnDebrisLifeMax);
             Vector debrisRotationVector;
             debrisRotationVector.set(spawnDebris[i].getTravelVector().getX(), spawnDebris[i].getTravelVector().getY(), spawnDebris[i].getTravelVector().getZ());
             debrisRotationVector.rotate('z',timer/10.0);
             spawnDebris[i].setTravelVector(debrisRotationVector.getX(), debrisRotationVector.getY(), spawnDebris[i].getTravelVector().getZ()+timer/10.0);
            glTranslatef(spawnDebris[i].getTravelVector().getX(), spawnDebris[i].getTravelVector().getY(), spawnDebris[i].getTravelVector().getZ());
             spawnDebris[i].drawParticle();

            glPopMatrix();
         }
     }
     if(portal.getSize()>2.0 && spawnTimer<=0.0)
    {
         float size=portal.getSize();
         size-=timer/10.0;

         if (type == 0)
              portal.setColor(1.0,0.0,0.0,1.0);
         else if (type == 3)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size);
         portal.drawParticle();
         if (type == 0)
              portal.setColor(1.0,0.3,0.3,1.0);
         else if (type == 3)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size/2.0);
         portal.drawParticle();
         if (type == 0 )
              portal.setColor(1.0,0.7,0.7,1.0);
         else if (type == 3)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size/4.0);
         portal.drawParticle();
         portal.setSize(size);
    }
     if(spawnTimer>0.0)
     {
         if (type == 0 || type == 1)
         {
             for (i=0;i<(maxSpawnTimer-spawnTimer);i+=5)
             {
                 if(spawnDebris[i/5].getDuration()<0)
                 {
                     spawnDebris[i/5].setDuration(spawnDebrisLifeMax);
                     Vector tempPosition;
                     tempPosition.set(0,2.0+((0.05)*(float)(rand()%20)),0);
                     tempPosition.rotate('z', i*rand());
                     spawnDebris[i/5].setPosition(position.getX(), position.getY(), 0);
                     spawnDebris[i/5].setTravelVector(tempPosition.getX(), tempPosition.getY(), 0);
                     if(rand()%2==1)
                         spawnDebris[i/5].setColor(1,1,1,1);
                     else
                         spawnDebris[i/5].setColor(1,0,0,1);
                 }
             }
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ());
                  if(spinReversed)
                      glRotatef(explosionTimer,0,0,1);
                  else
                      glRotatef(-explosionTimer,0,0,1);
                  glColor4f(red,0.0,0.0,opacity);
                  glLineWidth(1);
                  glutWireTorus(0.8,3-3*spawnTimer/maxSpawnTimer,5,15);

             glPopMatrix();
             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(0, timer, explosionTimer);
             }

             float size=((maxSpawnTimer-spawnTimer)/maxSpawnTimer)*48.0;
             if(size>12.0)
                 size=12.0f;

             portal.setColor(1,0,0,1.0);
             portal.setPosition(position.getX(), position.getY(), position.getZ());
             portal.setSize(size);
             portal.drawParticle();
             portal.setColor(1.0,0.3,0.3,1.0);
             portal.setSize(size/2.0);
             portal.drawParticle();
             portal.setColor(1.0,0.7,0.7,1.0);
             portal.setSize(size/4.0);
             portal.drawParticle();
             portal.setSize(size);
         }
     }
     else if(isAlive==true && isShrapnel==false)
     {
         if (type == 0 || type==1)
         {
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ());
                  if(spinReversed)
                      glRotatef(explosionTimer,0,0,1);
                  else
                      glRotatef(-explosionTimer,0,0,1);
                  glColor4f(red,0.0,0.0,opacity);
                  glLineWidth(1);
                  glutWireTorus(0.8,3,5,15);

             glPopMatrix();
             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(0, timer, explosionTimer);
             }
         }
     }
     else if(isAlive==true && isShrapnel==true){
         explode( explosionTimer );
         torus.draw(timer);
         explosion.drawExplosion(explosionTimer);
         explosion2.drawExplosion(explosionTimer);
         explosion3.drawExplosion(explosionTimer);
         if (type == 0 || type == 1)
         {
             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(0, timer, explosionTimer);
             }
         }
     }
}

void FragMine::reverseSpin(){
     spinReversed=!spinReversed;
}
bool FragMine::hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat range){
     Vector pythagoras;
     pythagoras.set(position.getX()-x,position.getY()-y,0);

     if (pythagoras.normalize() <= size + range  && spawnTimer<0.0)
     {
         return true;
     }
     return false;
}

const GLfloat FragMine::getSize() const{
     return size;
}

GLboolean FragMine::takeDamage(GLfloat damage){
     health = health - damage;
     if(health<0.0){
         wasDestroyed=true;
         isAlive = true;
         isShrapnel = true;
         SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_LARGE);
         return true;
     }
     else{
         return false;
     }
}

void FragMine::updateStatus(){
     int aliveChildren, i;
     aliveChildren=0;
     for(i=0;i<numberOfDrones;i++)
     {
         if(children[i].isAlive)
         {
             aliveChildren++;
         }
     }
     if(aliveChildren==0)
     {
         isAlive=false;
     }
}

GLboolean FragMine::damageChild(int child, GLfloat damage){
     children[child].health = children[child].health - damage;
     updateStatus();
     if(children[child].health<0.0){
         children[child].isAlive = true;
         children[child].isShrapnel = true;
         return true;
     }
     else{
         return false;
     }
}

void FragMine::explode( float explosionTimer ){
     if(wasDestroyed && !didExplode)
     {
          torus.set(position.getX(), position.getY(), position.getZ(), 30, 2, 15);
          torus.color( 0, 0, 0.8, 0.15 );
          torus.detail(20);

          explosion.setNumberParticles(50);
          explosion.setPosition(position.getX(), position.getY(), position.getZ());
          explosion.setParticleSize(4.0);
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

          explosion3.setNumberParticles(4);
          explosion3.setPosition(position.getX(), position.getY(), position.getZ());
          explosion3.setParticleSize(60.0);
          explosion3.setDuration(100);
          explosion3.setRed(1.0);
          explosion3.setGreen(0.69);
          explosion3.setBlue(0.2);
          explosion3.setSize(5);
          explosion3.setDrawLightFlare(false);
          explosion3.initializeExplosion(explosionTimer);
          didExplode=true;
     }
     if (isAlive==true && isShrapnel==true){
          isComplete=false;
          isAlive=true;
     }
     else if(isAlive==false && isShrapnel==true){

     }
}
