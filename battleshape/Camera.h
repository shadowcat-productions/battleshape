/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Camera class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Camera class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

#ifndef Camera_H
#define Camera_H


class Camera {
public:
    /*
    -------------------- Constructor for the Camera class --------------------
    */
    Camera();

    /*
    -------------------- Destructor for the Camera class --------------------
    */
    ~Camera();

    /*
    -------------------- Accessors for the Camera class --------------------
    */
    const GLfloat getPositionX() const; //must return the x coordinate of the camera
    const GLfloat getPositionY() const; //must return the y coordinate of the camera
    const GLfloat getPositionZ() const; //must return the z coordinate of the camera
    const GLfloat getLookAtX() const; //must return the x coordinate of the look at vector
    const GLfloat getLookAtY() const; //must return the y coordinate of the look at vector
    const GLfloat getLookAtZ() const; //must return the z coordinate of the look at vector
    const GLfloat getViewUpX() const; //must return the x coordinate of the view up vector
    const GLfloat getViewUpY() const; //must return the y coordinate of the view up vector
    const GLfloat getViewUpZ() const; //must return the z coordinate of the view up vector
    const GLfloat getViewingAngle() const; //must return the viewing angle
    float startTime;

    /*
    -------------------- Modifiers for the Camera class --------------------
    */
    void backUp();
    void Restore();

    void setPositionX(GLfloat newPositionX); //must set the x coordinate of the camera to the new value provided
    void setPositionY(GLfloat newPositionY); //must set the y coordinate of the camera to the new value provided
    void setPositionZ(GLfloat newPositionZ); //must set the z coordinate of the camera to the new value provided
    void setLookAtX(GLfloat newLookAtX); //must set the x coordinate of the look at vector to the new value provided
    void setLookAtY(GLfloat newLookAtY); //must set the y coordinate of the look at vector to the new value provided
    void setLookAtZ(GLfloat newLookAtZ); //must set the z coordinate of the look at vector to the new value provided
    void setViewUpX(GLfloat newViewUpX); //must set the x coordinate of the view up vector to the new value provided
    void setViewUpY(GLfloat newViewUpY); //must set the y coordinate of the view up vector to the new value provided
    void setViewUpZ(GLfloat newViewUpZ); //must set the z coordinate of the view up vector to the new value provided
    void setViewingAngle(GLfloat newViewingAngle); //must set the viewing angle to the new value provided

    /*
    -------------------- Methods for the Camera class --------------------
    */
    bool shake(float x, float y, float t);  // shake the camera, return true if shaking
    void setCamera(); //must initialize all properties and camera settings

private:
    /*
    -------------------- Variables for the Camera class --------------------
    */
    GLfloat positionX; //variable must store the x coordinate of the camera
    GLfloat positionY; //variable must store the y coordinate of the camera
    GLfloat positionZ; //variable must store the z coordinate of the camera
    GLfloat lookAtX; //variable must store the x coordinate of the look at vector
    GLfloat lookAtY; //variable must store the y coordinate of the look at vector
    GLfloat lookAtZ; //variable must store the z coordinate of the look at vector
    GLfloat viewUpX; //variable must store the x coordinate of the view up vector
    GLfloat viewUpY; //variable must store the y coordinate of the view up vector
    GLfloat viewUpZ; //variable must store the z coordinate of the view up vector
    GLfloat viewingAngle; //variable must store the viewing angle

    GLfloat BpositionX; //
    GLfloat BpositionY; //
    GLfloat BpositionZ; //
    GLfloat BlookAtX; //
    GLfloat BlookAtY; //
    GLfloat BlookAtZ; //          Backups of all the primary variables
    GLfloat BviewUpX; //
    GLfloat BviewUpY; //
    GLfloat BviewUpZ; //
    GLfloat BviewingAngle; //

};


#endif
