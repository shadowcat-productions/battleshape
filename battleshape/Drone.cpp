/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the basic Drone.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Drone class --------------------
*/

#include "Drone.h"


/*
 -------------------- Constructors for the Drone class --------------------
*/
Drone::Drone() : isAlive(false), isShrapnel(false), size(4.0)
{
     setPointValue(1);
     setHealth(1.0);
     position.set(-70.0, 0.0, 1.0);
     movement.set(0.002, 0.0, 0.0);
     direction.set(0.0, 1.0, 0.0);
}

void Drone::initialize(int newType) {
     type = newType;
     if (type == 0 || type == 1)
     {
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         red=0.0;
         green=0.8;
         blue=0.8;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         size = 3.0;
         speed=0.6;
         spinSpeed=-2.0;

         glow.setColor(0.0,1.0,1.0,0.05);
         glow.setSize(15.0);
     }
     else if (type == 2)
     {
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         red=0.0;
         green=0.8;
         blue=0.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(float((rand() % 40))*5.0+2.5,float((rand() % 30))*5.0+2.5,1);
         size = 3.0;
         speed=0.165;               //0.165 is the default value
//         maxRotTime=30.0;
         maxRotTime=5/speed;
         hangTime=5.0;
     }
     else if (type == 3)
     {
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         red=0.0;
         green=0.8;
         blue=0.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         int movementTemp=rand()%4;
         if(movementTemp==0)
             movement.set(1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==1)
             movement.set(-1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==2)
             movement.set(-1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==3)
             movement.set(1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);

         movement.rotate('z',(((float)(rand()%300)/10.0)-15.0)*3.14159/180.0);
         size = 3.0;
         speed=0.3;
         spinSpeed=-8.0;
     }
     else if (type == 4)
     {
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.8;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(0);
         currentRotation=0.0;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         int movementTemp=rand()%4;
         if(movementTemp==0)
             movement.set(1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==1)
             movement.set(-1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==2)
             movement.set(-1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==3)
             movement.set(1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);

         movement.rotate('z',(((float)(rand()%300)/10.0)-15.0)*3.14159/180.0);
         size = 2.0;
         speed=0.6;
         spinSpeed=-8.0;
     }
     else if (type == 5)
     {
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.8;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         int movementTemp=rand()%4;
         if(movementTemp==0)
             movement.set(1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==1)
             movement.set(-1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==2)
             movement.set(-1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==3)
             movement.set(1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);

         movement.rotate('z',(((float)(rand()%300)/10.0)-15.0)*3.14159/180.0);
         size = 3.0;
         speed=0.8;
         spinSpeed=-8.0;
     }
}

void Drone::initialize(int newType, float x, float y, float xDir, float yDir) {
     appliedForce.set(0,0,0);
     type = newType;
     if (type == 0 || type == 1)
     {
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         red=0.0;
         green=0.8;
         blue=0.8;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(x,y,1);
         size = 3.0;
         speed=0.3;
         spinSpeed=-2.0;

         glow.setColor(0.0,1.0,1.0,0.05);
         glow.setSize(15.0);     
     }
     else if (type == 2)
     {
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         red=0.0;
         green=0.8;
         blue=0.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(x,y,1);
         size = 3.0;
         speed=0.165;               //0.165 is the default value
//         maxRotTime=30.0;
         maxRotTime=5/speed;
         hangTime=5.0;
     }
     else if (type == 3)
     {
         spawnTimer=150.0;
         maxSpawnTimer=150.0;
         spawnDebrisLifeMax=150.0;
         int i;
         for (i=0;i<30;i++)
         {
             spawnDebris[i].setDuration(-1.0);
         }
         red=0.0;
         green=0.8;
         blue=0.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(x,y,1);

         movement.set(xDir,yDir,0.0);

         size = 3.0;
         speed=0.45;
         spinSpeed=-8.0;
     }
     else if (type == 4)
     {
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.8;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(float((rand() % 2000))/10.0,float((rand() % 1500))/10.0,1);
         int movementTemp=rand()%4;
         if(movementTemp==0)
             movement.set(1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==1)
             movement.set(-1.0/pow((float)2.0,(float)0.5),1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==2)
             movement.set(-1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);
         else if(movementTemp==3)
             movement.set(1.0/pow((float)2.0,(float)0.5),-1.0/pow((float)2.0,(float)0.5),0.0);

         movement.rotate('z',(((float)(rand()%300)/10.0)-15.0)*3.14159/180.0);
         size = 3.0;
         speed=0.6;
         spinSpeed=-8.0;
     }
     else if (type == 5)
     {
         red=1.0;
         green=1.0;
         blue=1.0;
         opacity=0.8;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(1);
         currentRotation=0.0;
         position.set(x,y,1);
         movement.set(xDir,yDir,0.0);
         size = 3.0;
         speed=0.3;
         spinSpeed=-8.0;
     }
     else if (type == 6)
     {
         red=0.8;
         green=0.5;
         blue=0.0;
         opacity=0.5;
         isAlive=true;
         isShrapnel=false;
         setHealth(1.0);
         setPointValue(0);
         currentRotation=0.0;
         maxSpeed=0.9;
         position.set(x,y,1);
         movement.set(xDir,yDir,0.0);
         size = 3.0;
         speed=0.2;
         spinSpeed=1.0;

         glow.setColor(0.0,1.0,1.0,0.05);
         glow.setSize(15.0);     
     }
}

/*
 -------------------- Destructor for the Drone class --------------------
*/
Drone::~Drone(){
}

/*
 -------------------- Accessors for the Drone class --------------------
*/
//returns the health of the drone
const GLfloat Drone::getHealth() const{ return health; }

//returns the point value of the drone
GLint Drone::getPointValue(){
      int tempScore = 0;
      if(!isAlive)
      {
          tempScore=pointValue;
          pointValue=0;
      }
      return tempScore;
}

/*
 -------------------- Modifiers for the Drone class --------------------
*/
//sets the health for the drone
void Drone::setHealth(GLfloat newHealth){
     health = newHealth;
}

//sets the point value for the drone
void Drone::setPointValue(GLint newPointValue){
     pointValue = newPointValue;
}

/*
 -------------------- Methods for the Drone class --------------------
*/


/*
 --  Not sure how we should set it all up - I think we should have general  --
 --  methods here and more specific for each drone type in that class.      --
 --  I think we should just add to this as we think of more general methods --
*/
bool Drone::updatePosition(float t, GLfloat playerX, GLfloat playerY, GLfloat playerZ){
     if(isAlive==true && isShrapnel==false && spawnTimer<0.0)
     {
         Vector movementTemp;
         if (type == 0 || type == 1)
         {
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(movementTemp.normalize()<size)
                 return true;
             movement.set(movementTemp.getX()*speed, movementTemp.getY()*speed, 0.0);
             position.set( position.getX()+(movement.getX()+appliedForce.getX())*t, position.getY()+(movement.getY()+appliedForce.getY())*t, 1 );
             appliedForce.multiply(pow(0.97,t/2.0));
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
         else if(type == 2)
         {
              currentRotation-=t;
              position.set( position.getX()+appliedForce.getX()*t, position.getY()+appliedForce.getY()*t, 1 );
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             appliedForce.multiply(pow(0.9,t/2.0));
             if(currentRotation<-hangTime)
             {
                 currentRotation=maxRotTime;
                 if(abs((int)movementTemp.getX()) > abs((int)movementTemp.getY()) )
                 {
                     if(movementTemp.getX() > 0)
                         movement.set(speed, 0.0, 0.0);
                     else
                         movement.set(-speed, 0.0, 0.0);
                 }
                 else
                 {
                     if(movementTemp.getY() > 0)
                         movement.set(0.0, speed, 0.0);
                     else
                         movement.set(0.0, -speed, 0.0);
                 }
             }
             if(movementTemp.normalize()<size)
                 return true;
             if(currentRotation>0.0)
                 position.set( position.getX()+movement.getX()*t, position.getY()+movement.getY()*t, 1 );
             else
             {
                 float roundedx,roundedy;
                 roundedx=position.getX();
                 roundedy=position.getY();
                 roundedx=roundedx-2.5;
                 roundedy=roundedy-2.5;
                 roundedx=roundedx/5.0;
                 roundedy=roundedy/5.0;
                 roundedx=round(roundedx);
                 roundedy=round(roundedy);
                 roundedx=roundedx*5.0;
                 roundedy=roundedy*5.0;
                 roundedx=roundedx+2.5;
                 roundedy=roundedy+2.5;
                 position.set(roundedx, roundedy, 1 );
                 appliedForce.multiply(0.1);
             }
             if ( position.getX() < size/2.0 ) {
                  position.set( size/2.0, position.getY(), position.getZ() );
             }
             if ( position.getX() > 200.0-size/2.0 ) {
                  position.set( 200.0-size/2.0, position.getY(), position.getZ() );
             }
             if ( position.getY() < size/2.0 ) {
                  position.set( position.getX(), size/2.0, position.getZ() );
             }
             if ( position.getY() > 150.0-size/2.0 ) {
                  position.set( position.getX(), 150.0-size/2.0, position.getZ() );
             }
         }
         else if (type == 3)
         {
              movement.set(movement.getX()+appliedForce.getX(),movement.getY()+appliedForce.getY(),0);
              movement.normalize();
              appliedForce.multiply(0);
             position.set( position.getX() + movement.getX()*t*speed, position.getY()+movement.getY()*t*speed, 1 );
             // If the drone hits a wall, don't go out of the bounds of the grid, bounce!
             if ( position.getX() < size/2.0 ) {
                  position.set( size/2.0, position.getY(), position.getZ() );
                  movement.set ( -movement.getX(), movement.getY(), 0 );
             }
             if ( position.getX() > 200.0-size/2.0 ) {
                  position.set( 200.0-size/2.0, position.getY(), position.getZ() );
                  movement.set ( -movement.getX(), movement.getY(), 0 );
             }
             if ( position.getY() < size/2.0 ) {
                  position.set( position.getX(), size/2.0, position.getZ() );
                  movement.set ( movement.getX(), -movement.getY(), 0 );
             }
             if ( position.getY() > 150.0-size/2.0 ) {
                  position.set( position.getX(), 150.0-size/2.0, position.getZ() );
                  movement.set ( movement.getX(), -movement.getY(), 0 );
             }
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(movementTemp.normalize()<size+2.0)
                 return true;
         }
         else if (type == 4 || type == 5)
         {
             position.set( position.getX()+(movement.getX()+appliedForce.getX())*t, position.getY()+(movement.getY()+appliedForce.getY())*t, 1 );
             appliedForce.multiply(pow(0.97,t/2.0));
             // If the drone hits a wall, don't go out of the bounds of the grid, BLOW UP!
             if ( position.getX() < size/2.0 ) {
                  isShrapnel=true;
             }
             if ( position.getX() > 200.0-size/2.0 ) {
                  isShrapnel=true;
             }
             if ( position.getY() < size/2.0 ) {
                  isShrapnel=true;
             }
             if ( position.getY() > 150.0-size/2.0 ) {
                  isShrapnel=true;
             }
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(movementTemp.normalize()<size+2.0)
                 return true;
         }
         else if (type == 6)
         {
             position.set( position.getX()+(movement.getX()+appliedForce.getX())*t, position.getY()+(movement.getY()+appliedForce.getY())*t, 1 );
             appliedForce.multiply(pow(0.97,t/2.0));              
             // If the drone hits a wall, don't go out of the bounds of the grid, BLOW UP!
             if ( position.getX() < size/2.0 ) {
                  isShrapnel=true;
             }
             if ( position.getX() > 200.0-size/2.0 ) {
                  isShrapnel=true;
             }
             if ( position.getY() < size/2.0 ) {
                  isShrapnel=true;
             }
             if ( position.getY() > 150.0-size/2.0 ) {
                  isShrapnel=true;
             }
             movementTemp.set((playerX - position.getX()), (playerY - position.getY()), 0.0);
             if(movementTemp.normalize()<size+2.0)
                 return true;
             movementTemp.multiply(t*0.03);
             movement.add(movementTemp);
             if(movement.getLength()>maxSpeed)
             {
                 movement.normalize();
                 movement.multiply(maxSpeed);
             }
         }

     }
     else
     {spawnTimer-=t;}
     return false;
}

/*
--- This method will be created across all different types of drones to standardize the hit detection process ---
*/
bool Drone::hitDetect(GLfloat x, GLfloat y, GLfloat z, GLfloat range){
     Vector pythagoras;
     pythagoras.set(position.getX()-x,position.getY()-y,1);
     
     if (pythagoras.normalize() <= size + range  && spawnTimer<0.0 )
     {
         return true;
     }
     return false;
}

void Drone::draw(const GLuint& sparkTexture, float timer, float explosionTimer) {
//     srand(time(0));
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

         if(type==0 || type == 1)
              portal.setColor(0.0,1.0,1.0,1.0);
         else if (type == 2)
              portal.setColor(1.0,0.0,0.0,1.0);
         else if (type == 3)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size);
         portal.drawParticle();
         if(type==0 || type == 1)
              portal.setColor(0.3,1.0,1.0,1.0);
         else if (type == 2)
              portal.setColor(1.0,0.3,0.3,1.0);
         else if (type == 3)
              portal.setColor(1.0,1.0,1.0,1.0);
         portal.setSize(size/2.0);
         portal.drawParticle();
         if(type==0 || type == 1)
              portal.setColor(0.7,1.0,1.0,1.0);
         else if (type == 2)
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
             currentRotation+=timer*spinSpeed;
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
                         spawnDebris[i/5].setColor(0,1,1,1);
                 }
             }
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ());
                  glRotatef(currentRotation,0,0,1);
                  glColor4f(red,green,blue,opacity*(maxSpawnTimer-spawnTimer)/maxSpawnTimer);
                  glLineWidth(3);
                  glBegin(GL_LINE_LOOP);
                       glVertex3f(-1.5, -1.5, 1.0);
                       glVertex3f(1.5, -1.5, 1.0);
                       glVertex3f(1.5, 1.5, 1.0);
                       glVertex3f(-1.5, 1.5, 1.0);
                       glVertex3f(-1.5, -1.5, 1.0);
                  glEnd();
             glPopMatrix();

             float size=((maxSpawnTimer-spawnTimer)/maxSpawnTimer)*48.0;
             if(size>12.0)
                 size=12.0f;

             portal.setColor(0,1,1,1.0);
             portal.setPosition(position.getX(), position.getY(), position.getZ());
             portal.setSize(size);
             portal.drawParticle();
             portal.setColor(0.3,1.0,1.0,1.0);
             portal.setSize(size/2.0);
             portal.drawParticle();
             portal.setColor(0.7,1.0,1.0,1.0);
             portal.setSize(size/4.0);
             portal.drawParticle();
             portal.setSize(size);
         }
         else if (type == 2)
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
                  glColor4f(red,green,blue,opacity*(maxSpawnTimer-spawnTimer)/maxSpawnTimer);
                  glLineWidth(1);
                  glutWireCube(3);
                  glColor4f(red,green,blue,opacity/2*(maxSpawnTimer-spawnTimer)/maxSpawnTimer);
                  glLineWidth(3);
                  glutWireCube(3);
                  glColor4f(green,red,blue,opacity/2*(maxSpawnTimer-spawnTimer)/maxSpawnTimer);
                  glLineWidth(3);
                  glutSolidCube(3);
             glPopMatrix();

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
         else if (type == 3)
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
                         spawnDebris[i/5].setColor(1,1,1,1);
                 }
             }
           currentRotation+=timer*spinSpeed;
              float theta=6.0*3.14159/180.0;
              float cosTheta=cos(theta);
              float sinTheta=sin(theta);

              float tempAx, tempBx, tempAy, tempBy;
              float by=(1.0-0.618033)*size;
              float bx=0.0;
              float ay=size;
              float ax=0.0;

             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ());
                  glRotatef(currentRotation,0,0,1);
                  int i,j;
                  for (i=0;i<6;i++)
                  {
                      if(i==0)
                          {red=1.0;green=0.0;blue=0.0;}
                      else if(i==1)
                          {red=1.0;green=1.0;blue=0.0;}
                      else if(i==2)
                          {red=0.0;green=1.0;blue=0.0;}
                      else if(i==3)
                          {red=0.0;green=1.0;blue=1.0;}
                      else if(i==4)
                          {red=0.0;green=0.0;blue=1.0;}
                      else if(i==5)
                          {red=1.0;green=0.0;blue=1.0;}

                      for (j=0;j<10;j++)
                      {
                          glBegin(GL_QUADS);
                          glColor4f (1.0,1.0,1.0,(maxSpawnTimer-spawnTimer)/maxSpawnTimer); // inner vertex to white
                          glVertex3f(bx, by, 0.0);
                          glColor4f (red,green,blue,(maxSpawnTimer-spawnTimer)/maxSpawnTimer); // outer vertex to the current colour
                          glVertex3f(ax, ay, 0.0);

                          // update the colour of the disc
                          if(i==0)
                              green+=0.1;
                          else if(i==1)
                              red-=0.1;
                          else if(i==2)
                              blue+=0.1;
                          else if(i==3)
                              green-=0.1;
                          else if(i==4)
                              red+=0.1;
                          else if(i==5)
                              blue-=0.1;

                          tempAx=ax;
                          tempAy=ay;
                          tempBx=bx;
                          tempBy=by;
                          ax=cosTheta*tempAx-sinTheta*tempAy;
                          ay=sinTheta*tempAx+cosTheta*tempAy;
                          bx=cosTheta*tempBx-sinTheta*tempBy;
                          by=sinTheta*tempBx+cosTheta*tempBy;

                          glColor4f (red,green,blue,(maxSpawnTimer-spawnTimer)/maxSpawnTimer); // outer vertex to the current colour
                          glVertex3f(ax, ay, 0.0);
                          glColor4f (1.0,1.0,1.0,(maxSpawnTimer-spawnTimer)/maxSpawnTimer); // inner vertex to white
                          glVertex3f(bx, by, 0.0);
                          glEnd();
                      }
                  }
             glPopMatrix();

             float size=((maxSpawnTimer-spawnTimer)/maxSpawnTimer)*48.0;
             if(size>12.0)
                 size=12.0f;

             portal.setColor(1,1,1,1.0);
             portal.setPosition(position.getX(), position.getY(), position.getZ());
             portal.setSize(size);
             portal.drawParticle();
             portal.setColor(1.0,1.0,1.0,0.7);
             portal.setSize(size/2.0);
             portal.drawParticle();
             portal.setColor(1.0,1.0,1.0,0.3);
             portal.setSize(size/4.0);
             portal.drawParticle();
             portal.setSize(size);
         }
     }
     else if(isAlive==true && isShrapnel==false)
     {
         if (type == 0 || type == 1)
         {
             glow.setPosition(position.getX(), position.getY(), 0);
             glow.drawParticle();

             currentRotation+=timer*spinSpeed;
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ());
                  glRotatef(currentRotation,0,0,1);
                  glColor4f(red,green,blue,opacity);
                  glLineWidth(3);
                  glBegin(GL_LINE_LOOP);
                       glVertex3f(-1.5, -1.5, 1.0);
                       glVertex3f(1.5, -1.5, 1.0);
                       glVertex3f(1.5, 1.5, 1.0);
                       glVertex3f(-1.5, 1.5, 1.0);
                       glVertex3f(-1.5, -1.5, 1.0);
                  glEnd();
                  glColor4f(red,green,blue,opacity*2);
                  glLineWidth(1);
                  glBegin(GL_LINE_LOOP);
                       glVertex3f(-1.5, -1.5, 1.0);
                       glVertex3f(1.5, -1.5, 1.0);
                       glVertex3f(1.5, 1.5, 1.0);
                       glVertex3f(-1.5, 1.5, 1.0);
                       glVertex3f(-1.5, -1.5, 1.0);
                  glEnd();
             glPopMatrix();
         }
         else if (type == 2)
         {
             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ());
                  if(currentRotation>0.0)
                      glRotatef(currentRotation/maxRotTime*90.0,movement.getY(),-movement.getX(),0);
                  glColor4f(red,green,blue,opacity);
                  glLineWidth(1);
                  glutWireCube(3);
                  glColor4f(red,green,blue,opacity/2);
                  glLineWidth(3);
                  glutWireCube(3);
                  glColor4f(green,red,blue,opacity/2);
                  glLineWidth(3);
                  glutSolidCube(3);
             glPopMatrix();

             float blX, blY;
             blX=floor(position.getX()/5.0)*5.0;
             blY=floor(position.getY()/5.0)*5.0;
             glLineWidth(3);
             glColor4f(0.0,1.0,0.0,0.3);
             glBegin(GL_LINE_LOOP);
             glVertex3f(blX,blY,1.0);
             glVertex3f(blX+5.0,blY,1.0);
             glVertex3f(blX+5.0,blY+5.0,1.0);
             glVertex3f(blX,blY+5.0,1.0);
             glEnd();


         }
         else if (type == 3) // rainbow disk
         {
            currentRotation+=timer*spinSpeed;
              float theta=6.0*3.14159/180.0;
              float cosTheta=cos(theta);
              float sinTheta=sin(theta);

              float tempAx, tempBx, tempAy, tempBy;
              float by=(1.0-0.618033)*size;
              float bx=0.0;
              float ay=size;
              float ax=0.0;

             glPushMatrix();
                  glTranslatef(position.getX(), position.getY(), position.getZ());
                  glRotatef(currentRotation,0,0,1);
                  int i,j;
                  for (i=0;i<6;i++)
                  {
                      if(i==0)
                          {red=1.0;green=0.0;blue=0.0;}
                      else if(i==1)
                          {red=1.0;green=1.0;blue=0.0;}
                      else if(i==2)
                          {red=0.0;green=1.0;blue=0.0;}
                      else if(i==3)
                          {red=0.0;green=1.0;blue=1.0;}
                      else if(i==4)
                          {red=0.0;green=0.0;blue=1.0;}
                      else if(i==5)
                          {red=1.0;green=0.0;blue=1.0;}

                      for (j=0;j<10;j++)
                      {
                          glBegin(GL_QUADS);
                          glColor3f (1.0,1.0,1.0); // inner vertex to white
                          glVertex3f(bx, by, 0.0);
                          glColor3f (red,green,blue); // outer vertex to the current colour
                          glVertex3f(ax, ay, 0.0);

                          // update the colour of the disc
                          if(i==0)
                              green+=0.1;
                          else if(i==1)
                              red-=0.1;
                          else if(i==2)
                              blue+=0.1;
                          else if(i==3)
                              green-=0.1;
                          else if(i==4)
                              red+=0.1;
                          else if(i==5)
                              blue-=0.1;

                          tempAx=ax;
                          tempAy=ay;
                          tempBx=bx;
                          tempBy=by;
                          ax=cosTheta*tempAx-sinTheta*tempAy;
                          ay=sinTheta*tempAx+cosTheta*tempAy;
                          bx=cosTheta*tempBx-sinTheta*tempBy;
                          by=sinTheta*tempBx+cosTheta*tempBy;

                          glColor3f (red,green,blue); // outer vertex to the current colour
                          glVertex3f(ax, ay, 0.0);
                          glColor3f (1.0,1.0,1.0); // inner vertex to white
                          glVertex3f(bx, by, 0.0);
                          glEnd();
                      }
                  }
             glPopMatrix();
         }
         else if(type==4) // shot from mine drone
         {

              bool leftSide;
                  leftSide = false;
                  Vector up;
                  up.set(0,1,0);
                  float theta;
                  if ( movement.getX() < 0 ) {
                       leftSide = true;
                  }
                  theta = up.angleBetween(movement);
                  glPushMatrix();
                  glColor4f( red,green,blue, 0.8 );
                  glLineWidth( 1 );
                  glTranslatef( position.getX(), position.getY(), 1 );
                  if ( leftSide )
                       glRotatef( theta*180 / 3.14, 0.0, 0.0, 1.0 );
                  else
                       glRotatef( -theta*180 / 3.14, 0.0, 0.0, 1.0 );
                  glRotatef( -90.0, 1.0, 0.0, 0.0 );
                  glutWireCone( 1, 2, 4, 1 );
                  glPopMatrix();
         }
         else if(type==5) // shot from factory
         {
              glPushMatrix();
              glTranslatef( position.getX(), position.getY(), 1 );
              glColor4f( red,green,blue, 0.4 );
              glutSolidSphere(  0.5, 10, 10 );
              glColor4f( red,green,blue, 0.1 );
              glutSolidSphere(  1.2, 10, 10 );
              glColor4f( red,green,blue, 0.1 );
              glutSolidSphere(  2, 10, 10 );
              glPopMatrix();
         }
         else if (type == 6) // shot from final boss
         {
            currentRotation+=timer*spinSpeed;
              float theta=6.0*3.14159/180.0;
              float cosTheta=cos(theta);
              float sinTheta=sin(theta);
              
             glow.setSize(sin(currentRotation/10.0)+4);
             int i = ((int)currentRotation)%6;
              if(i==0)
                  {glow.setColor(1.0,(currentRotation-(int)currentRotation),0.0,0.8);}
              else if(i==1)
                  {glow.setColor(1.0-(currentRotation-(int)currentRotation),1.0,0.0,0.8);}
              else if(i==2)
                  {glow.setColor(0.0,1.0,(currentRotation-(int)currentRotation),0.8);}
              else if(i==3)
                  {glow.setColor(0.0,1.0-(currentRotation-(int)currentRotation),1.0,0.8);}
              else if(i==4)
                  {glow.setColor((currentRotation-(int)currentRotation),0.0,1.0,0.8);}
              else if(i==5)
                  {glow.setColor(1.0,0.0,1.0-(currentRotation-(int)currentRotation),0.8);}

//             (currentRotation-(int)currentRotation)

             glow.setPosition(position.getX(), position.getY(), 0);
             glow.drawParticle();
             
              glPushMatrix();
              red=1.0;green=1.0;blue=1.0;
              glTranslatef( position.getX(), position.getY(), 1 );
              glColor4f( red,green,blue, 0.4 );
              glutSolidSphere(  0.5, 10, 10 );
              glColor4f( red,green,blue, 0.1 );
              glutSolidSphere(  1.2, 10, 10 );
              glColor4f( red,green,blue, 0.1 );
              glutSolidSphere(  2, 10, 10 );
              glPopMatrix();
         }
     }
     else{
          explode( explosionTimer );
     }
}

const GLfloat Drone::getSize() const{ return size; }

GLboolean Drone::takeDamage(GLfloat damage){
     health = health - damage;
     if(health<0.0){
         isAlive = true;
         isShrapnel = true;
         spawnTimer=0.0;
         return true;
     }
     else{
         return false;
     }
}


void Drone::explode( float timer ){
     //srand((int)(timer*position.getX()*position.getY()));
    

     if (type!=4 && type!=3 && type!=5)
     {
         if (isAlive==true && isShrapnel==true){
              // Randomly choose a explosion effect
              if (health > -5) SoundManager::playSoundEffect(SOUND_EFFECT::EXPLOSION_LARGE);
              
              isAlive=false;
              explosion.setNumberParticles( (int) ceil(100 + (health * 0.85)) );
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
         }
         else if(isAlive==false && isShrapnel==true){
             explosion.drawExplosion(timer);
         }
     }
     else if (type == 4 || type == 5)
     {
         if (isAlive==true && isShrapnel==true){
              isAlive=false;
              explosion.setNumberParticles(25);
              explosion.setPosition(position.getX(), position.getY(), position.getZ());
              explosion.setParticleSize(3.0);
              explosion.setDuration(70);
              explosion.setRed(red);
              explosion.setGreen(green);
              explosion.setBlue(blue);
              explosion.setSize(3);
              explosion.setDrawLightFlare(false);
              explosion.initializeExplosion(timer);
              position.set( -70.0,-10.0,-10.0);
         }
         else if(isAlive==false && isShrapnel==true){
             explosion.drawExplosion(timer);
         }
     }
     else if (type == 3)
     {
         if (isAlive==true && isShrapnel==true){
              // Randomly choose a explosion effect
              if (health > -5) SoundManager::playSoundEffect(SOUND_EFFECT::EXPLOSION_LARGE);
              
              int i=rand()%6;
              //srand((int)ceil(position.getX()*position.getY()));
              if(i==0)
                  {red=1.0;green=0.0;blue=0.0;}
              else if(i==1)
                  {red=1.0;green=1.0;blue=0.0;}
              else if(i==2)
                  {red=0.0;green=1.0;blue=0.0;}
              else if(i==3)
                  {red=0.0;green=1.0;blue=1.0;}
              else if(i==4)
                  {red=0.0;green=0.0;blue=1.0;}
              else if(i==5)
                  {red=1.0;green=0.0;blue=1.0;}
                  
              isAlive=false;
              explosion.setNumberParticles((int)ceil(100+(health*0.85)));
              explosion.setPosition(position.getX(), position.getY(), position.getZ());
              explosion.setParticleSize(5.0);
              explosion.setDuration(100);
              explosion.setRed(red);
              explosion.setGreen(green);
              explosion.setBlue(blue);
              explosion.setSize(5);
              explosion.setDrawLightFlare(true);
              explosion.initializeExplosion(timer);
              position.set( -70.0, -10.0, -10.0);
         }
         else if(isAlive==false && isShrapnel==true){
             explosion.drawExplosion(timer);
         }
     }
}
