/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the ViewPort class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the ViewPort class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#ifndef ViewPort_H
#define ViewPort_H


class ViewPort {
public:
    /*
    -------------------- Constructor for the ViewPort class --------------------
    */
    ViewPort();

    /*
    -------------------- Destructor for the ViewPort class --------------------
    */
    ~ViewPort();

    /*
    -------------------- Accessors for the ViewPort class --------------------
    */
    const GLint getWindowXPosition() const; //must return the windows x coordinate position
    const GLint getWindowYPosition() const; //must return the windows y coordinate position
    const GLint getWindowHeight() const; //must return the windows height
    const GLint getWindowWidth() const; //must return the windows width
    const GLfloat getWindowRedColour() const; //must return the windows red colour component
    const GLfloat getWindowGreenColour() const; //must return the windows green colour component
    const GLfloat getWindowBlueColour() const; //must return the windows blue colour component
    const GLfloat getWindowAlphaValue() const;  //must return the windows red colour component
    const GLfloat getNearClippingPlaneDistance() const; //must return the near clipping planes distance
    const GLfloat getFarClippingPlaneDistance() const; //must return the far clipping planes distance
    const std::string getWindowTitle() const; //must return the title of the window
    const GLfloat getAspectRatio() const; //must return the aspect ratio of the window

    /*
    -------------------- Modifiers for the ViewPort class --------------------
    */
    void setWindowXPosition(GLint newWindowXPosition); //must set the windows x position to the new value provided
    void setWindowYPosition(GLint newWindowYPosition); //must set the windows y position to the new value provided
    void setWindowHeight(GLint newWindowHeight); //must set the windows height to the new value provided
    void setWindowWidth(GLint newWindowWidth); //must set the windows width to the new value provided
    void setWindowRedColour(GLfloat newWindowRedColour); //must set the windows red colour component to the new red value provided
    void setWindowGreenColour(GLfloat newWindowGreenColour); //must set the windows green colour component to the new value provided
    void setWindowBlueColour(GLfloat newWindowBlueColour); //must set the windows blue colour component to the new value provided
    void setWindowAlphaValue(GLfloat newWindowAlphaValue); //must set the windows alpha value to the new value provided
    void setNearClippingPlaneDistance(GLfloat newNearClippingPlaneDistance); //must set the near clipping planes distance to the new value provided
    void setFarClippingPlaneDistance(GLfloat newFarClippingPlaneDistance); //must set the far clipping planes distance to the new value provided
    void setWindowTitle(std::string newWindowTitle); //must set the windows title to the new value provided

    /*
    -------------------- Methods for the ViewPort class --------------------
    */
    void displayWindow(); //must set all properties and display the window
    void refreshWindowColour(); //must refresh the window colour
    void setPerspective(GLfloat viewingAngle); //must initialize matrix mode and set the gluPerspective

private:

    /*
    -------------------- Variables for the ViewPort class --------------------
    */
    GLint windowXPosition; //variable must store the x coordinate of the window
    GLint windowYPosition; //variable must store the y coordinate of the window
    GLint windowWidth; //variable must store the width of the window
    GLint windowHeight; //variable must store the height of the window
    GLfloat windowRedColour; //variable must store the red colour componant of the window
    GLfloat windowGreenColour; //variable must store the green colour componant of the window
    GLfloat windowBlueColour; //variable must store the blue colour componant of the window
    GLfloat windowAlphaValue;  //variable must store the alpha value of the window
    GLfloat nearClippingPlaneDistance; //variable must store the near clipping plane distance
    GLfloat farClippingPlaneDistance; //variable must store the far clipping plane distance
    std::string windowTitle; //variable must store the title of the window
};


#endif
