/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the camera.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Camera class --------------------
*/
#include "Camera.h"

/*
 -------------------- Constructors for the Camera class --------------------
*/
Camera::Camera() : startTime(0) {
    //initialize camera variables to default settings
    setPositionX(100.0);
    setPositionY(75.0);
    setPositionZ(200.0);
    setLookAtX(100.0);
    setLookAtY(75.0);
    setLookAtZ(0.0);
    setViewUpX(0.0);
    setViewUpY(1.0);
    setViewUpZ(0.0);
    setViewingAngle(50.0);
}

/*
 -------------------- Destructor for the Camera class --------------------
*/
Camera::~Camera() {
}

/*
 -------------------- Accessors for the Camera class --------------------
*/
//returns the x coordinate of the camera
const GLfloat Camera::getPositionX() const { return positionX; }

//returns the y coordinate of the camera
const GLfloat Camera::getPositionY() const { return positionY; }

//returns the z coordinate of the camera
const GLfloat Camera::getPositionZ() const { return positionZ; }

//returns the x coordinate of the look at vector
const GLfloat Camera::getLookAtX() const { return lookAtX; }

//returns the Y coordinate of the look at vector
const GLfloat Camera::getLookAtY() const { return lookAtY; }

//returns the z coordinate of the look at vector
const GLfloat Camera::getLookAtZ() const { return lookAtZ; }

//returns the x coordinate of the view up vector
const GLfloat Camera::getViewUpX() const { return viewUpX; }

//returns the y coordinate of the look at vector
const GLfloat Camera::getViewUpY() const { return viewUpY; }

//returns the z coordinate of the look at vector
const GLfloat Camera::getViewUpZ() const { return viewUpZ; }

//returns the viewing angle
const GLfloat Camera::getViewingAngle() const { return viewingAngle; }

/*
 -------------------- Modifiers for the Camera class --------------------
*/
//sets the x coordinate of the camera to the new value provided
void Camera::setPositionX(GLfloat newPositionX) {
    positionX = newPositionX;
}

//sets the y coordinate of the camera to the new value provided
void Camera::setPositionY(GLfloat newPositionY) {
    positionY = newPositionY;
}

//sets the z coordinate of the camera to the new value provided
void Camera::setPositionZ(GLfloat newPositionZ) {
    positionZ = newPositionZ;
}

//sets the x coordinate of the look at vector to the new value provided
void Camera::setLookAtX(GLfloat newLookAtX) {
    lookAtX = newLookAtX;
}

//sets the y coordinate of the look at vector to the new value provided
void Camera::setLookAtY(GLfloat newLookAtY) {
    lookAtY = newLookAtY;
}

//sets the z coordinate of the look at vector to the new value provided
void Camera::setLookAtZ(GLfloat newLookAtZ) {
    lookAtZ = newLookAtZ;
}

//sets the x coordinate of the view up vector to the new value provided
void Camera::setViewUpX(GLfloat newViewUpX) {
    viewUpX = newViewUpX;
}

//sets the y coordinate of the view up vector to the new value provided
void Camera::setViewUpY(GLfloat newViewUpY) {
    viewUpY = newViewUpY;
}

//sets the xz coordinate of the view up vector to the new value provided
void Camera::setViewUpZ(GLfloat newViewUpZ) {
    viewUpZ = newViewUpZ;
}

//sets the viewing angle to the new value provided
void Camera::setViewingAngle(GLfloat newViewingAngle) {
    viewingAngle = newViewingAngle;
}

void Camera::backUp()
{
    BpositionX=positionX;
    BpositionY=positionY;
    BpositionZ=positionZ;
    BlookAtX=lookAtX;
    BlookAtY=lookAtY;
    BlookAtZ=lookAtZ;
    BviewUpX=viewUpX;
    BviewUpY=viewUpY;
    BviewUpZ=viewUpZ;
    BviewingAngle=viewingAngle;
}

void Camera::Restore()
{
    positionX=BpositionX;
    positionY=BpositionY;
    positionZ=BpositionZ;
    lookAtX=BlookAtX;
    lookAtY=BlookAtY;
    lookAtZ=BlookAtZ;
    viewUpX=BviewUpX;
    viewUpY=BviewUpY;
    viewUpZ=BviewUpZ;
    viewingAngle=BviewingAngle;
    setCamera();
}

/*
 -------------------- Methods for the Camera class --------------------
*/
//must initialize all properties and camera settings
void Camera::setCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(getPositionX(),
              getPositionY(),
              getPositionZ(),
              getLookAtX(),
              getLookAtY(),
              getLookAtZ(),
              getViewUpX(),
              getViewUpY(),
              getViewUpZ());
}

bool Camera::shake(float x, float y, float t)
{
     float newTime;
     if(startTime == 0) startTime = t;
     else newTime = t;
     srand((int)(t*100));

     if (newTime - startTime < 40) // shake for 100 ms
     {
          setPositionX(x + rand()%7 - 7);
          setPositionY(y + rand()%7 - 7);
          //setPositionZ(200 + rand()%7 - 8);
          setCamera();
          return true;
     }
     else
     {
          startTime = 0;
          return false;
     }
}
