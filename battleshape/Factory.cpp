/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the basic Factory.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Factory class --------------------
*/
#include "Factory.h"


/*
 -------------------- Constructors for the Factory class --------------------
*/
Factory::Factory() : isAlive(false), isShrapnel(false), isComplete(false), size(4.0)
{
     setHealth(1.0);
     setPointValue(1); 
     position.set(-70.0, 0.0, 1.0);   
     movement.set(0.002, 0.0, 0.0);
     direction.set(0.0, 1.0, 0.0);
}

void Factory::initialize(int newType) {
     type=newType;
          isComplete=true;
     if(type==0)
     {
         numberOfDrones = 8;
         int i;
         for(i=0;i<numberOfDrones;i++)
         {
              children[i].initialize(5);
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
         size = 3.0;
         speed=0.3;
         spinSpeed=-2.0;
     }
     if(type==1)
     {
         numberOfDrones = 15;
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(3.0);
         setPointValue(10);
         currentRotation=float((rand() % 2000))/200;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         movement.set(100-position.getX(),75-position.getY(),0);
         float x = position.getX();
         float y = position.getY();
         if(x>100)
         {
             if(y>75)
                 currentRotation=-(tan((y-75)/(x-100))+3.14159/2);
             else
                 currentRotation=-(3.14159/2-tan((y-75)/(x-100)));
         }         
         else
         {
             if(y>75)
                 currentRotation=3.14159/2+tan((y-75)/(x-100));
             else
                 currentRotation=3.14159/2-tan((y-75)/(x-100));
         }
         size = 5.0;
         speed=0.3;
         spinSpeed=-2.0;
         maxReloadTimer=20.0;
     }
}

void Factory::initialize(int newType, float x, float y) {
     type=newType;
          isComplete=true;
     if(type==0)
     {
         spawnTimer=300.0;
         maxSpawnTimer=300.0;

         downAngle=0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         
         numberOfDrones = 20;
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(3.0);
         maxHealth=3.0;
         setPointValue(10);
         position.set(x,y,1);
         movement.set(100-position.getX(),75-position.getY(),0);
         movement.normalize();
         currentRotation=0.0;
         if(x>100)
         {
             if(y>75)
                 currentRotation=-(tan((y-75)/(x-100))+3.14159/2);
             else
                 currentRotation=-(3.14159/2-tan((y-75)/(x-100)));
         }         
         else
         {
             if(y>75)
                 currentRotation=3.14159/2+tan((y-75)/(x-100));
             else
                 currentRotation=3.14159/2-tan((y-75)/(x-100));
         }
         size = 3.0;
         speed=0.3;
         spinSpeed=-2.0;
         maxReloadTimer=50.0;
     }
     if(type==1)
     {
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         
         numberOfDrones = 20;
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(3.0);
         maxHealth=3.0;
         setPointValue(10);
         position.set(x,y,1);
         movement.set(100-position.getX(),75-position.getY(),0);
         movement.normalize();
         currentRotation=0.0;
         if(x>100)
         {
             if(y>75)
                 currentRotation=-(tan((y-75)/(x-100))+3.14159/2);
             else
                 currentRotation=-(3.14159/2-tan((y-75)/(x-100)));
         }         
         else
         {
             if(y>75)
                 currentRotation=3.14159/2+tan((y-75)/(x-100));
             else
                 currentRotation=3.14159/2-tan((y-75)/(x-100));
         }
         size = 3.0;
         speed=0.3;
         spinSpeed=-2.0;
         maxReloadTimer=20.0;
     }
}

/*
 -------------------- Destructor for the Factory class --------------------
*/
Factory::~Factory(){
}

/*
 -------------------- Accessors for the Factory class --------------------
*/
//returns the health of the Factory
const GLfloat Factory::getHealth() const{ return health; }

//returns the point value of the Factory
GLint Factory::getPointValue(){
      int tempScore = 0;
      if(!isAlive)
      {
          tempScore=pointValue;
          pointValue=0;
      }
      return tempScore;
}

/*
 -------------------- Modifiers for the Factory class --------------------
*/
//sets the health for the Factory
void Factory::setHealth(GLfloat newHealth){
     health = newHealth;
}

//sets the point value for the Factory
void Factory::setPointValue(GLint newPointValue){
     pointValue = newPointValue;
}

/*
 -------------------- Methods for the Factory class --------------------
*/
void Factory::fire(){
     int i;

     // SOUND FOR FACTORY SHOT... Loud, turning off for now
     //SoundManager::playSoundEffect( SOUND_EFFECT::FACTORY_SHOT);
     
     for(i=0;i<numberOfDrones;i++)
     {
         if(children[i].isAlive==false)
         {
             children[i].initialize(5,position.getX(),position.getY(),movement.getX(),movement.getY());
             children[i].movement.normalize();
             break;
         }
     }
}

bool Factory::updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ, bool playerDeath){
         if (isAlive==true && isShrapnel==false  && type == 0)
         {
             if(spawnTimer>=0)
                 spawnTimer-=t;
             bool hit=false;
             Vector movementTemp;
             movementTemp.set(playerX-position.getX(),playerY-position.getY(),playerZ-position.getZ());
             movement.set(playerX-position.getX(),playerY-position.getY(),playerZ-position.getZ());
             float d = movementTemp.normalize();
             orbitDistance = direction.getLength();
             downAngle=acos(orbitDistance/d);
             
             Vector helper;
             helper.set(0,1,0);
             if(direction.getX()>=0 && direction.getY()>=0)//Check to see what quadrant the factory is currently within
             {
                 direction.rotate('z',3.1415);
                 orbitRotation=-direction.angleBetween(helper);
             }
             else if(direction.getX()<0 && direction.getY()<0)//Check to see what quadrant the factory is currently within
             {
                 direction.rotate('z',-3.1415);
                 orbitRotation=-(direction.angleBetween(helper)-3.1415);
             }
             else if(direction.getX()>=0 && direction.getY()<0)//Check to see what quadrant the factory is currently within
             {
                 direction.rotate('z',3.1415/2.0);
                 orbitRotation=(direction.angleBetween(helper)-(3.1415/2.0));
             }
             else if(direction.getX()<0 && direction.getY()>=0)//Check to see what quadrant the factory is currently within
             {
                 direction.rotate('z',-3.1415/2.0);
                 orbitRotation=(direction.angleBetween(helper)+(3.1415/2.0));
             }
             if(hitDetect(playerX,playerY,playerZ,0)&&!playerDeath)
             {
                  hit=true;
                  takeDamage(10);
             }

             if(reloadTimer<0.0 && position.getZ() < 2 && position.getZ()>0 && !playerDeath && spawnTimer<0)
             {
                 reloadTimer=maxReloadTimer;
                 fire();
             }
             else
                  reloadTimer-=t;

             movement.set(playerX-position.getX(),playerY-position.getY(),0);
             movementTemp.set(0,1,0);
             float theta = movement.angleBetween(movementTemp);
             currentRotation=theta*180.0/3.14159;
             if(movement.getX()>0.0)
                 currentRotation=(currentRotation-180.0)*-1;
                 
             int i;
             for(i=0;i<numberOfDrones;i++)
             {
                  if(children[i].updatePosition(t, playerX, playerY, playerZ)&&!playerDeath)
                  {
                      hit=true;
                      damageChild(i,10);
                  }
             }
             return hit;
         }  
     if(isAlive==true && isShrapnel==false  && spawnTimer<0.0)
     {
         if (type == 1)
         {
             bool hit=false;
             Vector movementTemp;
             movementTemp.set(playerX-position.getX(),playerY-position.getY(),0);
             movementTemp.normalize();
             if(hitDetect(playerX,playerY,playerZ,0)&&!playerDeath)
             {
                  hit=true;
                  takeDamage(10);
             }
             float theta = movement.angleBetween(movementTemp);
             float theta2 = movement.angleBetween(movementTemp);
             //printf("%.2f\n",theta);
             movement.rotate('z',-t/100.0);
             theta2 = movement.angleBetween(movementTemp);
             if (theta2>theta)
                 movement.rotate('z',t/50.0);

             if(reloadTimer<0.0 && theta2<3.14159/32.0 && !playerDeath)
             {
                 reloadTimer=maxReloadTimer;
                 fire();
             }
             else
                  reloadTimer-=t;

             movementTemp.set(0,1,0);
             theta = movement.angleBetween(movementTemp);
             currentRotation=theta*180.0/3.14159;
             if(movement.getX()>0.0)
                 currentRotation=(currentRotation-180.0)*-1;
             int i;
             for(i=0;i<numberOfDrones;i++)
             {
                  if(children[i].updatePosition(t, playerX, playerY, playerZ)&&!playerDeath)
                  {
                      hit=true;
                      damageChild(i,10);
                  }
             }
             return hit;
         }        
     }
     else if(isAlive==true && isShrapnel==false)
     {
         playerX=100;playerY=75;playerZ=0;
         bool hit=false;
         Vector movementTemp;
         movementTemp.set(playerX-position.getX(),playerY-position.getY(),0);
         movementTemp.normalize();
         float theta = movement.angleBetween(movementTemp);
         float theta2 = movement.angleBetween(movementTemp);
         //printf("%.2f\n",theta);
         if (type == 1)
         {
             movement.rotate('z',-t/100.0);
             theta2 = movement.angleBetween(movementTemp);
             if (theta2>theta)
                 movement.rotate('z',t/50.0);

             movementTemp.set(0,1,0);
             theta = movement.angleBetween(movementTemp);
             currentRotation=theta*180.0/3.14159;
             if(movement.getX()>0.0)
                 currentRotation=(currentRotation-180.0)*-1;
         }    
         spawnTimer-=t;    
     }
     else if(isAlive==true && isComplete == false){
         updateStatus();
         if (type == 0 || type == 1)
         {
             bool hit=false;
             int i;
             for(i=0;i<numberOfDrones;i++)
             {
                  if(children[i].updatePosition(t, playerX, playerY, playerZ))
                  {
                      hit=true;
                      damageChild(i,1);
                  }
             }
             return hit;
         }
     }
     else
     {spawnTimer-=t;}
     return false;
}

void Factory::drawShots(const GLuint& sparkTexture, float timer, float explosionTimer) {
     explode( explosionTimer );
     if(isAlive==true && isShrapnel==false && type == 0)
     {
         int i;
         for(i=0;i<numberOfDrones;i++)
         {
              children[i].draw(sparkTexture, timer, explosionTimer);
         }
     } 
}

void Factory::draw(const GLuint& sparkTexture, float timer, float explosionTimer) {
         if (type == 0)//Rotate down, Rotate to face player, move up r, rotate to orbit rotation, move to BOSS location (factory location minus direction)
         {
                  if(isAlive && !isShrapnel)
                  {
             glPushMatrix();
//                  glTranslatef(position.getX()-direction.getX(), position.getY()-direction.getY(), position.getZ()-direction.getZ()); 
                  glTranslatef(position.getX(), position.getY(), position.getZ()-10); 
                  glRotatef(currentRotation,0,0,1);// to face player (may need to fix current rotation)
                  glTranslatef(0,0,direction.getLength());
                  glRotatef(orbitRotation*180/3.1415,0,1,0);// orbit rotation
//                glRotatef(downAngle,1,0,0);// angle down, to account for 3D movement
                  glColor4f(1.0,0.0,0.0,0.7);
                  if(spawnTimer>200.0)
                  {
                      glScalef(0.01,(300.0-spawnTimer)/100.0,0.01);
                  }
                  else if(spawnTimer>100.0)
                  {
                      glScalef((200.0-spawnTimer)/100.0,1.0,0.01);
                  }
                  else if(spawnTimer>0.0)
                  {
                      glScalef(1.0,1.0,(100.0-spawnTimer)/100.0);
                  }
                  glutSolidCube(2);
             glPopMatrix();
             }
/*             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(sparkTexture, timer, explosionTimer);
             } */
         }
         
     int i;
/*     if(type==0)
     {
            glPushMatrix();
//             glTranslatef(spawnDebris[i].getTravelVector().getX(), spawnDebris[i].getTravelVector().getY(), spawnDebris[i].getTravelVector().getZ());
             glRotatef();
     }        
     */
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

         if(type==0 || type == 1)
              portal.setColor(1.0,0.0,0.0,1.0);
         else if (type == 2)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size);
         portal.drawParticle();
         if(type==0 || type == 1)
              portal.setColor(1.0,0.3,0.3,1.0);
         else if (type == 2)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size/2.0);
         portal.drawParticle();
         if(type==0 || type == 1)
              portal.setColor(1.0,0.7,0.7,1.0);
         else if (type == 2)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size/4.0);
         portal.drawParticle();
         portal.setSize(size);
    }
     if(spawnTimer>0.0)
     {
         if (type == 0 && isAlive==true && isShrapnel == false)//Rotate down, Rotate to face player, move up r, rotate to orbit rotation, move to BOSS location (factory location minus direction)
         {
             glPushMatrix();
//                  glTranslatef(position.getX()-direction.getX(), position.getY()-direction.getY(), position.getZ()-direction.getZ()); 
                  glTranslatef(position.getX(), position.getY(), position.getZ()-10); 
                  glRotatef(currentRotation,0,0,1);// to face player (may need to fix current rotation)
                  glTranslatef(0,0,direction.getLength());
                  glRotatef(orbitRotation*180/3.1415,0,1,0);// orbit rotation
                  if(spawnTimer>200.0)
                  {
                      glScalef(0.01,(300.0-spawnTimer)/100.0,0.01);
                  }
                  else if(spawnTimer>100.0)
                  {
                      glScalef((200.0-spawnTimer)/100.0,1.0,0.01);
                  }
                  else if(spawnTimer>0.0)
                  {
                      glScalef(1.0,1.0,(100.0-spawnTimer)/100.0);
                  }
//                glRotatef(downAngle,1,0,0);// angle down, to account for 3D movement
                  
                  int segments=6;
                  float height=6.0;
                  float width=1.0;
                  
                  glColor4f(1.0,1.0-(reloadTimer/maxReloadTimer),1.0-(reloadTimer/maxReloadTimer),opacity);
                  Vector drawHelper;
                  drawHelper.set(0,0,width);
                  glBegin(GL_QUAD_STRIP);
                  for(i=0;i<segments;i++)
                  {
                      glVertex3f(drawHelper.getX(),height,drawHelper.getY());
                      glVertex3f(drawHelper.getX(),-height,drawHelper.getY());
                      drawHelper.rotate('y',3.14159*2/segments);
                  }
                  glEnd();
                           
                  glColor4f(red,health/maxHealth,0.0,opacity);
                  glLineWidth(2);
                  
                  glutWireCube(4);
                  glTranslatef(0,4,0);
                  glutWireCube(4);
                  glTranslatef(0,-8,0);
                  glutWireCube(4);
             glPopMatrix();
         }
         else
         {
             for (i=0;i<(maxSpawnTimer-spawnTimer);i+=5)
             {
                 if(spawnDebris[i/5].getDuration()<0)
                 {
                     spawnDebris[i/5].setDuration(spawnDebrisLifeMax);
                     Vector tempPosition;
                     tempPosition.set(0,2.0+((0.05)*(float)(rand()%60)),0);
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
                      glRotatef(currentRotation,0,0,1);
                      
                      int segments=6;
                      float height=6.0;
                      float width=1.0;
                      
                      glColor4f(1.0,1.0-(reloadTimer/maxReloadTimer),1.0-(reloadTimer/maxReloadTimer),opacity*(maxSpawnTimer-spawnTimer)/maxSpawnTimer);
                      Vector drawHelper;
                      drawHelper.set(0,0,width);
                      glBegin(GL_QUAD_STRIP);
                      for(i=0;i<segments;i++)
                      {
                          glVertex3f(drawHelper.getX(),height,drawHelper.getY());
                          glVertex3f(drawHelper.getX(),-height,drawHelper.getY());
                          drawHelper.rotate('y',3.14159*2/segments);
                      }
                      glEnd();
                               
                      glColor4f(red,health/maxHealth,0.0,opacity*(maxSpawnTimer-spawnTimer)/maxSpawnTimer);
                      glLineWidth(2);
                      /*
                      glBegin(GL_LINE_LOOP);
                        glVertex3f(-2,-6,-1);
                        glVertex3f(2,-6,-1);
                        glVertex3f(2,-6,3);
                        glVertex3f(-2,-6,3);
                      glEnd();
                      glBegin(GL_LINE_LOOP);
                        glVertex3f(-2,-2,-1);
                        glVertex3f(2,-2,-1);
                        glVertex3f(2,-2,3);
                        glVertex3f(-2,-2,3);
                      glEnd();
                      glBegin(GL_LINE_LOOP);
                        glVertex3f(-2,2,-1);
                        glVertex3f(2,2,-1);
                        glVertex3f(2,2,3);
                        glVertex3f(-2,2,3);
                      glEnd();
                      glBegin(GL_LINE_LOOP);
                        glVertex3f(-2,6,-1);
                        glVertex3f(2,6,-1);
                        glVertex3f(2,6,3);
                        glVertex3f(-2,6,3);
                      glEnd();
                      glBegin(GL_LINES);
                        glVertex3f(-2,6,-1);
                        glVertex3f(-2,-6,-1);
                        
                        glVertex3f(-2,-6,3);
                        glVertex3f(-2,6,3);
                        
                        glVertex3f(2,6,3);
                        glVertex3f(2,-6,3);
                        
                        glVertex3f(2,-6,-1);
                        glVertex3f(2,6,-1);
                      glEnd();*/
                      glutWireCube(4);
                      glTranslatef(0,4,0);
                      glutWireCube(4);
                      glTranslatef(0,-8,0);
                      glutWireCube(4);
                 glPopMatrix();
                 float size=((maxSpawnTimer-spawnTimer)/maxSpawnTimer)*48.0*3;
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
     }
     else if(isAlive==true && isShrapnel==false)
     {
         if (type == 0)//Rotate down, Rotate to face player, move up r, rotate to orbit rotation, move to BOSS location (factory location minus direction)
         {
             glPushMatrix();
//                  glTranslatef(position.getX()-direction.getX(), position.getY()-direction.getY(), position.getZ()-direction.getZ()); 
                  glTranslatef(position.getX(), position.getY(), position.getZ()-10); 
                  glRotatef(currentRotation,0,0,1);// to face player (may need to fix current rotation)
                  glTranslatef(0,0,direction.getLength());
                  glRotatef(orbitRotation*180/3.1415,0,1,0);// orbit rotation
//                glRotatef(downAngle,1,0,0);// angle down, to account for 3D movement
                  
                  int segments=6;
                  float height=6.0;
                  float width=1.0;
                  
                  glColor4f(1.0,1.0-(reloadTimer/maxReloadTimer),1.0-(reloadTimer/maxReloadTimer),opacity);
                  Vector drawHelper;
                  drawHelper.set(0,0,width);
                  glBegin(GL_QUAD_STRIP);
                  for(i=0;i<segments;i++)
                  {
                      glVertex3f(drawHelper.getX(),height,drawHelper.getY());
                      glVertex3f(drawHelper.getX(),-height,drawHelper.getY());
                      drawHelper.rotate('y',3.14159*2/segments);
                  }
                  glEnd();
                           
                  glColor4f(red,health/maxHealth,0.0,opacity);
                  glLineWidth(2);
                  
                  glutWireCube(4);
                  glTranslatef(0,4,0);
                  glutWireCube(4);
                  glTranslatef(0,-8,0);
                  glutWireCube(4);
             glPopMatrix();
/*             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(sparkTexture, timer, explosionTimer);
             } */
         }
         if (type == 1)
         {
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ()); 
                  glRotatef(currentRotation,0,0,1);
                  
                  int segments=6;
                  float height=6.0;
                  float width=1.0;
                  
                  glColor4f(1.0,1.0-(reloadTimer/maxReloadTimer),1.0-(reloadTimer/maxReloadTimer),opacity);
                  Vector drawHelper;
                  drawHelper.set(0,0,width);
                  glBegin(GL_QUAD_STRIP);
                  for(i=0;i<segments;i++)
                  {
                      glVertex3f(drawHelper.getX(),height,drawHelper.getY());
                      glVertex3f(drawHelper.getX(),-height,drawHelper.getY());
                      drawHelper.rotate('y',3.14159*2/segments);
                  }
                  glEnd();
                           
                  glColor4f(red,health/maxHealth,0.0,opacity);
                  glLineWidth(2);
                  glBegin(GL_LINE_LOOP);
                    glVertex3f(-2,-6,-1);
                    glVertex3f(2,-6,-1);
                    glVertex3f(2,-6,3);
                    glVertex3f(-2,-6,3);
                  glEnd();
                  glBegin(GL_LINE_LOOP);
                    glVertex3f(-2,-2,-1);
                    glVertex3f(2,-2,-1);
                    glVertex3f(2,-2,3);
                    glVertex3f(-2,-2,3);
                  glEnd();
                  glBegin(GL_LINE_LOOP);
                    glVertex3f(-2,2,-1);
                    glVertex3f(2,2,-1);
                    glVertex3f(2,2,3);
                    glVertex3f(-2,2,3);
                  glEnd();
                  glBegin(GL_LINE_LOOP);
                    glVertex3f(-2,6,-1);
                    glVertex3f(2,6,-1);
                    glVertex3f(2,6,3);
                    glVertex3f(-2,6,3);
                  glEnd();
                  glBegin(GL_LINES);
                    glVertex3f(-2,6,-1);
                    glVertex3f(-2,-6,-1);
                    
                    glVertex3f(-2,-6,3);
                    glVertex3f(-2,6,3);
                    
                    glVertex3f(2,6,3);
                    glVertex3f(2,-6,3);
                    
                    glVertex3f(2,-6,-1);
                    glVertex3f(2,6,-1);
                  glEnd();
             glPopMatrix();
             for(i=0;i<numberOfDrones;i++)
             {
                  children[i].draw(sparkTexture, timer, explosionTimer);
             } 
         }
     }
     else if(isAlive==true && isShrapnel==true && isComplete==true){
          explode( explosionTimer );
     }   
     if(isAlive==true)
     {
         if (type == 1)
         {
             explode( explosionTimer );
             for(i=0;i<numberOfDrones;i++)
             {
                 children[i].draw(sparkTexture, timer, explosionTimer);
             } 
         } 
     }
     if(type==1)
     explode( explosionTimer );
}

const GLfloat Factory::getSize() const{ return size; }

GLboolean Factory::takeDamage(GLfloat damage){
     health = health - damage;
     if(health<0.0){
         isAlive = true;
         isShrapnel = true;
         SoundManager::playSoundEffect(SOUND_EFFECT::EXPLOSION_ENORMOUS);
         return true;
     }
     else{
         return false;
     }
}

bool Factory::hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat range){
     
     Vector pythagoras;
     movement.normalize();
     pythagoras.set(position.getX()-x,position.getY()-y,position.getZ()-z);
     if (pythagoras.normalize() <= size + range && spawnTimer<0.0)
     {
         return true;
     }
     pythagoras.set(position.getX()+movement.getX()*4-x,position.getY()+movement.getY()*4-y,position.getZ()+movement.getZ()*4-z);
     if (pythagoras.normalize() <= size + range && spawnTimer<0.0)
     {
         return true;
     }
     pythagoras.set(position.getX()-movement.getX()*4-x,position.getY()-movement.getY()*4-y,position.getZ()-movement.getZ()*4-z);
     if (pythagoras.normalize() <= size + range && spawnTimer<0.0)
     {
         return true;
     }
     return false;
}

void Factory::updateStatus(){
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
         if(explosion.isActive()==false)
             isAlive=false;
     }
}

GLboolean Factory::damageChild(int child, GLfloat damage){
     return children[child].takeDamage(damage);
}

void Factory::explode( float timer ){
     if (isAlive==true && isShrapnel==true&& isComplete==true){
          isComplete=false;
          isAlive=true;
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
        //  position.set( -70.0,-10.0,-10.0);
     }
     else if(isAlive==true && isComplete==false){
         explosion.drawExplosion(timer);
     }
}
