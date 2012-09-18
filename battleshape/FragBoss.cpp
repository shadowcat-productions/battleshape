/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the basic FragBoss.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the FragBoss class --------------------
*/
#include "FragBoss.h"
#include "SoundManager.h"
#include "Sounds.h"

/*
 -------------------- Constructors for the FragBoss class --------------------
*/
FragBoss::FragBoss() : isAlive(false), isShrapnel(false), isComplete(false), size(4.0){
     setHealth(1.0);
     setPointValue(1); 
     position.set(-70.0, 0.0, 1.0);   
     movement.set(0.002, 0.0, 0.0);
     direction.set(0.0, 1.0, 0.0);
}

void FragBoss::initialize(int newType) {
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
}

void FragBoss::initialize(int newType, float x, float y) {
     type=newType;
          isComplete=true;
     if(type==0)
     {
         appliedForce.set(0,0,0);
         wasDestroyed=false;
         didExplode=false;
         wasHit=false;
         spawnTimer=300.0;
         maxSpawnTimer=300.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<150;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }

         numberOfDrones = 24;
         int k=0;
         for(i=0;i<numberOfDrones;i++)
         {
              if(i%8==0)
                  k++;
              k+=3;
              float tempChanger;
              float tempR=0.5;
              float tempG=0.5;
              float tempB=0.5;
              if(k%8<4)
                  tempChanger=(float)(k%8)/4.0;
              else
                  tempChanger=1.0-((float)(k%8)-4.0)/4.0;
                  
              if(k%24<4)
              {
                   tempR=0;
                   tempG=1;
              }
              else if(k%24<8)
              {
                   tempR=0;
                   tempB=1;
              }
              else if(k%24<12)
              {
                   tempG=0;
                   tempB=1;
              }
              else if(k%24<16)
              {
                   tempG=0;
                   tempR=1;
              }
              else if(k%24<20)
              {
                   tempB=0;
                   tempR=1;
              }
              else if(k%24<24)
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
              children[i].initialize(4);
              children[i].red=tempR;
              children[i].green=tempG;
              children[i].blue=tempB;
         }
         
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(60.0);
         maxHealth=60.0;
         setPointValue(100);
         currentRotation=5;
         position.set(x,y,1);
         size = 15.0;
         speed=0;
         spinSpeed=-2.0;
     }
     if(type==1)// chain gun factory
     {
         spawnTimer=300.0;
         maxSpawnTimer=300.0;
         rollRotation=0;
         shields=60;
         maxReloadTimer=150.0;
         maxShields=60;
         currentDrone=0;
         transTimer=0;
         appliedForce.set(0,0,0);
         orbitRotation=0;
         orbitRadius=15;
         wasDestroyed=false;
         lostFactories=false;
         hasFactories=true;
         didExplode=false;
         wasHit=false;
         spawnTimer=300.0;
         maxSpawnTimer=300.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<150;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }

         numberOfDrones = 0;
         numberOfFactories = 8;
         int k=0;
         Vector tempRot;
         tempRot.set(0,1,0);
         for(i=0;i<numberOfFactories;i++)
         {
              factories[i].initialize(0,0,0);
              factories[i].direction.set(tempRot.getX(),tempRot.getY(),0);
              factories[i].position.set(x,y,0);
              tempRot.rotate('z',3.1415/4.0);
         }
         
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         maxHealth=60.0;
         setPointValue(100);
         currentRotation=5;
         position.set(x,y,1);
         size = 5.0;
         speed=0.2;
         spinSpeed=-4.0;
     }
}

/*
 -------------------- Destructor for the FragBoss class --------------------
*/
FragBoss::~FragBoss(){
}

/*
 -------------------- Accessors for the FragBoss class --------------------
*/
//returns the health of the FragBoss
const GLfloat FragBoss::getHealth() const { return health; }

//returns the point value of the FragBoss
GLint FragBoss::getPointValue(){
      int tempScore = 0;
      if(!isComplete)
      {
          tempScore=pointValue;
          pointValue=0;
      }
      return tempScore;
}

/*
 -------------------- Modifiers for the FragBoss class --------------------
*/
//sets the health for the FragBoss
void FragBoss::setHealth(GLfloat newHealth){
     health = newHealth;
}

//sets the point value for the FragBoss
void FragBoss::setPointValue(GLint newPointValue){
     pointValue = newPointValue;
}

/*
 -------------------- Methods for the FragBoss class --------------------
*/

void FragBoss::fire(GLfloat playerX, GLfloat playerY, bool playerDeath)
{
     SoundManager::playSoundEffect( SOUND_EFFECT::SHOT2 );
     int i;
     if(currentDrone>37)
         currentDrone=0;     
     Vector helper;
     helper.set(playerX-position.getX(),playerY-position.getY(),0);
     helper.rotate('z',3.1415/4.0);
     helper.normalize();
     helper.multiply(size*2.1);
     for(i=currentDrone;i<currentDrone+4;i++)
     {
         helper.rotate('z',3.1415/2.0);
         children[i].initialize(6,position.getX()+helper.getX(),position.getY()+helper.getY(),helper.getX(),helper.getY());
         children[i].movement.normalize();
     }
     currentDrone+=4;
     damageShields(2);
     if(numberOfDrones<currentDrone)
         numberOfDrones=currentDrone;
}
     
     
bool FragBoss::updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ, bool playerDeath){
     if(spawnTimer>=0.0)
     {spawnTimer-=t;}
     bool flag = false;
     if(isAlive==true && isShrapnel==false)
     {
         Vector movementTemp;
         if (type == 0)
         {
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(shields<=0.0)
                 {if(movementTemp.normalize()<size && spawnTimer<0.0)
                     flag = true;}
             else
                 {if(movementTemp.normalize()<size*1.8 && spawnTimer<0.0)
                     flag = true;}
             movement.set(movementTemp.getX()*speed, movementTemp.getY()*speed, 0.0);
             appliedForce.multiply(pow(0.96,t/2.0));
             position.set( position.getX()+movement.getX()*t+appliedForce.getX()*t, position.getY()+movement.getY()*t+appliedForce.getY()*t, 1 );
             if ( position.getX() < size/2.0 ) {
                  appliedForce.multiply(pow(0.9,t/2.0));
                  position.set( size/2.0, position.getY(), position.getZ() );
             }
             if ( position.getX() > 200.0-size/2.0 ) {
                  appliedForce.multiply(pow(0.9,t/2.0));
                  position.set( 200.0-size/2.0, position.getY(), position.getZ() );
             }
             if ( position.getY() < size/2.0 ) {
                  appliedForce.multiply(pow(0.9,t/2.0));
                  position.set( position.getX(), size/2.0, position.getZ() );
             }
             if ( position.getY() > 150.0-size/2.0 ) {
                  appliedForce.multiply(pow(0.9,t/2.0));
                  position.set( position.getX(), 150.0-size/2.0, position.getZ() );
             }
             if(spinReversed)
                 currentRotation+=t*spinSpeed*0.01;
             else
                 currentRotation-=t*spinSpeed*0.01;
                 
             Vector rotation;
             if(spawnTimer<=0.0)
                 rotation.set(9.2,0,0);
             else
                 rotation.set(9.2*(1-(spawnTimer/maxSpawnTimer)),0,0);
             rotation.rotate('z',currentRotation);
             int i;
             for(i=0;i<numberOfDrones;i++)
             {
                  rotation.rotate('z',3.14159/4);
                  children[i].position.set(position.getX()+rotation.getX(),position.getY()+rotation.getY(),1);
                  children[i].movement.set(rotation.getX(),rotation.getY(),0);
                  children[i].movement.normalize();
                  if(i%8==7)
                       rotation.rotate('z',3.14159/12);
             } 
         }
        else if (type == 1)
         {// bind the location of each factory
         //  set the direction vector of each, for their rotation position
         //  run update on each factory
         //  draw the suckers
             if(transTimer<0)
             {
                 reloadTimer-=t;
                 if(reloadTimer<0)
                 {
                     reloadTimer=maxReloadTimer;
                     fire(playerX, playerY, playerDeath);
                 }
             }
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(movementTemp.normalize()<size && spawnTimer<0.0)
                 flag = true;
              if(!hasFactories)
              {
                  movement.set(movementTemp.getX()*speed, movementTemp.getY()*speed, 0.0);
                  appliedForce.multiply(pow(0.96,t/2.0));
                  position.set( position.getX()+movement.getX()*t+appliedForce.getX()*t, position.getY()+movement.getY()*t+appliedForce.getY()*t, 1 );
                  if ( position.getX() < size/2.0 ) {
                       appliedForce.multiply(pow(0.9,t/2.0));
                       position.set( size/2.0, position.getY(), position.getZ() );
                  }
                  if ( position.getX() > 200.0-size/2.0 ) {
                       appliedForce.multiply(pow(0.9,t/2.0));
                       position.set( 200.0-size/2.0, position.getY(), position.getZ() );
                  }
                  if ( position.getY() < size/2.0 ) {
                       appliedForce.multiply(pow(0.9,t/2.0));
                       position.set( position.getX(), size/2.0, position.getZ() );
                  }
                  if ( position.getY() > 150.0-size/2.0 ) {
                       appliedForce.multiply(pow(0.9,t/2.0));
                       position.set( position.getX(), 150.0-size/2.0, position.getZ() );
                  }
              }
              else
                  appliedForce.multiply(0);
             Vector helper;
             helper.set(1,0,0);
             currentRotation=movementTemp.angleBetween(helper)*180.0/3.14159;
             
             topside = false;
             if(movementTemp.getY()>0.0)
             {
                 currentRotation=(currentRotation-180.0)*-1;
                 topside=true;
             }

             if(transTimer>0.0)
             {
                 transTimer-=t;
                 if(transTimer==0)
                     transTimer-=t;
             }

             orbitRotation-=t*spinSpeed*0.01;
                 
             Vector rotation;
             rotation.set(orbitRadius,0,0);
             if(topside && transTimer==0)
                 rotation.rotate('z',-orbitRotation);
             else
                 rotation.rotate('z',orbitRotation);
             int i;
             bool hit=false;
             hasFactories=false;
             for(i=0;i<numberOfFactories;i++)
             {
                  if(factories[i].isAlive&&!factories[i].isShrapnel)
                      hasFactories=true;
                  if(topside && transTimer==0)
                       rotation.rotate('z',-3.14159/4);
                  else
                       rotation.rotate('z',3.14159/4);
                  factories[i].position.set(rotation.getX(),rotation.getY(),0);
                  if(transTimer>0)
                      factories[i].position.rotate('y',3.1415/2-(1-transTimer/50)*3.1415/2);
                  else if(transTimer==0)
                      factories[i].position.rotate('y',3.1415/2);
                  factories[i].position.rotate('z',currentRotation*3.1415/180);
                  factories[i].position.add(position);
                  factories[i].direction.set(rotation.getX(),rotation.getY(),1);
                  if(factories[i].updatePosition(t, playerX, playerY, playerZ, playerDeath))
                      hit=true;
             } 
             if(hasFactories==false && lostFactories==false)
             {
                 transTimer=50;
                 reloadTimer=maxReloadTimer;
                 lostFactories=true;
             }
             for(i=0;i<numberOfDrones;i++)
             {
                  if(children[i].updatePosition(t, playerX, playerY, playerZ))
                  {
                      hit=true;
                      damageChild(i,100);
                  }
                  if(shields>0.0)
                  {
                      if(hitDetect(children[i].position.getX(),children[i].position.getY(),1,size))
                      {
                          damageShields(8);
                          damageChild(i,100);
                      }
                  }
                  else
                  {
                      if(hitDetect(children[i].position.getX(),children[i].position.getY(),1,1))
                      {
                          damageShields(8);
                          damageChild(i,100);
                      }
                  }
             }
             return hit;
         }
     }
     else if(isAlive==true && isShrapnel==true){
         updateStatus();
         if (type == 0 || type==1)
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
     return flag;
}

void FragBoss::draw(const GLuint& sparkTexture, float timer, float explosionTimer) {
     int i;

     for (i=0;i<150;i++)
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
         if (type == 0)
         { 
             for (i=0;i<(maxSpawnTimer-spawnTimer);i+=2)
             {
                 if(spawnDebris[i/2].getDuration()<0)
                 {
                     spawnDebris[i/2].setDuration(spawnDebrisLifeMax);
                     Vector tempPosition;
                     if((maxSpawnTimer-spawnTimer)/maxSpawnTimer<0.33)
                     tempPosition.set(0,(6.0+((0.15)*(float)(rand()%20+1)))*(maxSpawnTimer-spawnTimer)/maxSpawnTimer*3,0);
                     else
                     tempPosition.set(0,(6.0+((0.15)*(float)(rand()%20+1))),0);
                     tempPosition.rotate('z', i*rand());
                     spawnDebris[i/2].setPosition(position.getX(), position.getY(), 0);
                     spawnDebris[i/2].setTravelVector(tempPosition.getX(), tempPosition.getY(), 0);
                     if(rand()%2==1)
                         spawnDebris[i/2].setColor(1,1,1,1);
                     else
                         spawnDebris[i/2].setColor(1,0,0,1);
                 }
             }
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY()+14, position.getZ()); 
                  healthbar.draw(health,maxHealth,((maxSpawnTimer-spawnTimer)/maxSpawnTimer)*20);
             glPopMatrix();
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ()); 
                  if(spinReversed)
                      glRotatef(explosionTimer,0,0,1);         
                  else
                      glRotatef(-explosionTimer,0,0,1);         
                  glColor4f(red,1.0,1.0,opacity);
                  glLineWidth(1);
                  glutWireTorus(2.4,7.1-7.1*spawnTimer/maxSpawnTimer,10,25);
             glPopMatrix();
             int tempCounter=numberOfDrones;
             if(((maxSpawnTimer-spawnTimer)/maxSpawnTimer)<0.6)
                 tempCounter=24;
             else
                 tempCounter=24;
             for(i=0;i<tempCounter;i++)
             {
                  children[i].draw(0, timer, explosionTimer);
             } 
             speed=((maxSpawnTimer-spawnTimer)/maxSpawnTimer)*0.2;
             float size=((maxSpawnTimer-spawnTimer)/maxSpawnTimer)*48.0*3.0;
             if(size>36.0)
                 size=36.0f;

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
         else if (type == 1)
         {    
             glEnable(GL_DEPTH_TEST);
    
                  glColor4f(1,0,0,0.2);
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), 5); 
                  glRotatef(currentRotation, 0, 0, -1); 
                  glRotatef(90, 0, 1, 0); 
                  if(spawnTimer>200.0)
                  {
                      glScalef((300.0-spawnTimer)/100.0,0.01,0.01);
                  }
                  else if(spawnTimer>100.0)
                  {
                      glScalef(1.0,(200.0-spawnTimer)/100.0,0.01);
                  }
                  else if(spawnTimer>0.0)
                  {
                      glScalef(1.0,1.0,(100.0-spawnTimer)/100.0);
                  }
                  glutSolidTorus(0.7,9,20,20);
             glPopMatrix();
    
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), 5); 
                  shieldR=1;
                  shieldG=1;
                  shieldB=1;
                  if(spawnTimer>200.0)
                  {
                      glScalef((300.0-spawnTimer)/100.0,0.01,0.01);
                  }
                  else if(spawnTimer>100.0)
                  {
                      glScalef(1.0,(200.0-spawnTimer)/100.0,0.01);
                  }
                  else if(spawnTimer>0.0)
                  {
                      glScalef(1.0,1.0,(100.0-spawnTimer)/100.0);
                  }
                  glColor4f(1.0-spawnTimer/300.0,1.0-spawnTimer/300.0,1.0-spawnTimer/300.0,0.2);
                  glScalef(size,size,size);
                  glutSolidDodecahedron();
                  glColor4f(1,1,1,1);
                  glLineWidth(3);
                  glutWireDodecahedron();
                  glLineWidth(2);
                  glBegin(GL_LINES);
                  for(i=0;i<numberOfFactories;i++)
                  {
                      if(factories[i].isAlive&&!factories[i].isShrapnel)
                      {
                          glVertex3f(0,0,0);
                          glVertex3f((factories[i].position.getX()-position.getX())/5,(factories[i].position.getY()-position.getY())/5,(factories[i].position.getZ()-position.getZ())/5);
                      }
                  } 
                  glLineWidth(1);
                  glEnd();
                  glScalef(1.0/size,1.0/size,1.0/size);
                  glutWireSphere(size/2,10,10);
             glPopMatrix();
                  
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), 5); 
                  glScalef((300.0-spawnTimer)/300.0,1.0,1.0);
                  glTranslatef(0, 14, 0); 
                  healthbar.draw(shields,maxShields,20);
             glPopMatrix();
// insert core boss drawing here
             for(i=0;i<numberOfFactories;i++)
             {
                  factories[i].draw(sparkTexture, timer, explosionTimer);
             } 
             glDisable(GL_DEPTH_TEST);
             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(0, timer, explosionTimer);
             } 
             for(i=0;i<numberOfFactories;i++)
             {
                  factories[i].drawShots(sparkTexture, timer, explosionTimer);
             }
         }
     }
     else if(isAlive==true && isShrapnel==false)
     {
         if (type == 0)
         {
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY()+14, position.getZ()); 
                  healthbar.draw(health,maxHealth,20);
             glPopMatrix();
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ()); 
                  if(spinReversed)
                      glRotatef(explosionTimer,0,0,1);         
                  else
                      glRotatef(-explosionTimer,0,0,1);                 
                  glColor4f(red,1.0,1.0,opacity);
                  glLineWidth(1);
                  glutWireTorus(2.4,7.1,10,25);
                  
             glPopMatrix();
             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(0, timer, explosionTimer);
             } 
         }
         if (type == 1)
         {
                  glEnable(GL_DEPTH_TEST);
             shieldR+=timer/20;
             shieldG+=timer/20;
             shieldB+=timer/20;
             
                  glColor4f(1,0,0,0.2);
             if(hasFactories)
             {
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), 5); 
                  glRotatef(currentRotation, 0, 0, -1); 
                  glRotatef(90, 0, 1, 0); 
                  glutSolidTorus(0.7,9,20,20);

             glPopMatrix();
             }             
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), 5); 
                  glColor4f(shieldR,shieldG,shieldB,0.2);
                  if(shields>0.0)
                  {
                      if(!hasFactories)
                      {
                          rollRotation+=timer*1;
                          glRotatef(currentRotation, 0, 0, -1);
                          if(topside)
                          glRotatef(rollRotation, 0, -1, 0);
                          else
                          glRotatef(rollRotation, 0, 1, 0);
                      }
                      glScalef(size,size,size);
                      glutSolidDodecahedron();
                      glLineWidth(3);
                      glColor4f(1,shields/maxShields,shields/maxShields,1);
                      glutWireDodecahedron();
                      glLineWidth(2);
                      glColor4f(1,1,1,1);
                  glBegin(GL_LINES);
                  for(i=0;i<numberOfFactories;i++)
                  {
                      if(factories[i].isAlive&&!factories[i].isShrapnel)
                      {
                          glVertex3f(0,0,0);
                          glVertex3f((factories[i].position.getX()-position.getX())/5,(factories[i].position.getY()-position.getY())/5,(factories[i].position.getZ()-position.getZ())/5);
                      }
                  } 
                  glEnd();
                      glScalef(1.0/size,1.0/size,1.0/size);
                  }
                  glutWireSphere(size/2,10,10);
                  glTranslatef(0, 14, 0); 
             glPopMatrix();
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), 5); 
                  glTranslatef(0, 14, 0); 
                  healthbar.draw(shields,maxShields,20);
             glPopMatrix();
// insert core boss drawing here
             for(i=0;i<numberOfFactories;i++)
             {
                  factories[i].draw(sparkTexture, timer, explosionTimer);
             } 
             glDisable(GL_DEPTH_TEST);
             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(0, timer, explosionTimer);
             } 
             for(i=0;i<numberOfFactories;i++)
             {
                  factories[i].drawShots(sparkTexture, timer, explosionTimer);
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
     else
     {
         for(i=0;i<numberOfDrones;i++)
         {
              children[i].draw(0, timer, explosionTimer);
         } 
     }
}
void FragBoss::damageShields(GLfloat damage)
{
    if(shields>damage)
        shields-=damage;
    else if (shields>0.0)
    {
        shields=0.0;
        takeDamage(damage);
    }
    else
        takeDamage(damage);
    shieldR=1.0;
    shieldG=0.0;
    shieldB=0.0;
}
void FragBoss::regenShields(GLfloat damage)
{
    shields+=damage;
    shieldR=0.0;
    shieldG=0.0;
    shieldB=1.0;
    if (shields>maxShields)
        shields=maxShields;
}
void FragBoss::reverseSpin(){
     spinReversed=!spinReversed;
}
bool FragBoss::hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat range){
     Vector pythagoras;
     pythagoras.set(position.getX()-x,position.getY()-y,0);
     
     if (pythagoras.normalize() <= size + range  && spawnTimer<0.0)
     {
         return true;
     }
     return false;
}

const GLfloat FragBoss::getSize() const{ return size; }

GLboolean FragBoss::takeDamage(GLfloat damage){
     if(!hasFactories && shields<=0.0)
         health = health - damage;
     else if(!hasFactories && shields>0.0)
         regenShields(damage);
     if(health<0.0){
        SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_LARGE);
         SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_ENORMOUS);
         SoundManager::playSoundEffect( SOUND_EFFECT::EXPLOSION_ENERGY);
         wasDestroyed=true;
         wasHit=false;
         isAlive = true;
         isShrapnel = true;
         return true;
     }
     else{
         if(type==0 || hasFactories)
             wasHit=true;
         return false;
     }
}

void FragBoss::updateStatus(){
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

GLboolean FragBoss::damageChild(int child, GLfloat damage){
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

void FragBoss::explode( float explosionTimer ){
     if(wasDestroyed && !didExplode)
     {
          torus.set(position.getX(), position.getY(), position.getZ(), 50, 2, 15);
          torus.color( 0, 0, 0.8, 0.15 );
          torus.detail(30);
          
          explosion.setNumberParticles(75);
          explosion.setPosition(position.getX(), position.getY(), position.getZ());
          explosion.setParticleSize(6.0);
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

          explosion3.setNumberParticles(6);
          explosion3.setPosition(position.getX(), position.getY(), position.getZ());
          explosion3.setParticleSize(80.0);
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
          /*
          explosion.setNumberParticles(300);
          explosion.setPosition(position.getX(), position.getY(), position.getZ());
          explosion.setParticleSize(5.0);
          explosion.setDuration(100);
          explosion.setRed(red);
          explosion.setGreen(green);
          explosion.setBlue(blue);
          explosion.setSize(5);
          explosion.setDrawLightFlare(true);
          explosion.initializeExplosion(timer);
          position.set( -70.0,-10.0,-10.0);
          */
     }
     else if(isAlive==false && isShrapnel==true){

     }
}
