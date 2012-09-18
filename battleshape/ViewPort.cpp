/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the viewport.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the ViewPort class --------------------
*/

#include "ViewPort.h"

/*
 -------------------- Constructor for the ViewPort class --------------------
*/
ViewPort::ViewPort() {
    //initialize viewport variables to default settings
    //window variables
    //setWindowXPosition(30);
    //setWindowYPosition(30);
    //setWindowWidth(1000);
    //setWindowHeight(800);
    setWindowRedColour(0.0);
    setWindowGreenColour(0.0);
    setWindowBlueColour(0.0);
    setWindowAlphaValue(1.0);

    //clipping variables
    setNearClippingPlaneDistance(1.0);
    setFarClippingPlaneDistance(900.0);

    //display window
}

/*
 -------------------- Destructor for the ViewPort class --------------------
*/
ViewPort::~ViewPort() {
}

/*
 -------------------- Accessors for the ViewPort class --------------------
*/
//returns the x coordinate of the window
const GLint ViewPort::getWindowXPosition() const {
    return windowXPosition;
}

//returns the y coordinate of the window
const GLint ViewPort::getWindowYPosition() const {
    return windowYPosition;
}

//returns the height of the window
const GLint ViewPort::getWindowHeight() const {
    return windowHeight;
}

//returns the width of the window
const GLint ViewPort::getWindowWidth() const {
    return windowWidth;
}

//returns the red colour component of the window
const GLfloat ViewPort::getWindowRedColour() const {
    return windowRedColour;
}

//returns the green colour component of the window
const GLfloat ViewPort::getWindowGreenColour() const {
    return windowGreenColour;
}

//returns the blue colour component of the window
const GLfloat ViewPort::getWindowBlueColour() const {
    return windowBlueColour;
}

//returns the alpha value of the window
const GLfloat ViewPort::getWindowAlphaValue() const {
    return windowAlphaValue;
}

//returns the aspect ratio of the window
const GLfloat ViewPort::getAspectRatio() const {
    return getWindowWidth() / getWindowHeight();
}

//returns the near clipping plane distance
const GLfloat ViewPort::getNearClippingPlaneDistance() const {
    return nearClippingPlaneDistance;
}

//returns the far clipping plane distance
const GLfloat ViewPort::getFarClippingPlaneDistance() const {
    return farClippingPlaneDistance;
}

//returns the title of the window
const std::string ViewPort::getWindowTitle() const {
    return windowTitle;
}

/*
 -------------------- Modifiers for the ViewPort class --------------------
*/
//sets the x coordinate of the window to the new value provided
void ViewPort::setWindowXPosition(GLint newWindowXPosition) {
    windowXPosition = newWindowXPosition;
}

//sets the y coordinate of the window to the new value provided
void ViewPort::setWindowYPosition(GLint newWindowYPosition) {
    windowYPosition = newWindowYPosition;
}

//sets the height of the window to the new value provided
void ViewPort::setWindowHeight(GLint newWindowHeight) {
    windowHeight = newWindowHeight;
}

//sets the width of the window to the new value provided
void ViewPort::setWindowWidth(GLint newWindowWidth) {
    windowWidth = newWindowWidth;
}

//sets the red colour component of the window to the new value provided
void ViewPort::setWindowRedColour(GLfloat newWindowRedColour) {
    windowRedColour = newWindowRedColour;
}

//sets the green colour component of the window to the new value provided
void ViewPort::setWindowGreenColour(GLfloat newWindowGreenColour) {
    windowGreenColour = newWindowGreenColour;
}

//sets the blue colour component of the window to the new value provided
void ViewPort::setWindowBlueColour(GLfloat newWindowBlueColour) {
    windowBlueColour = newWindowBlueColour;
}

//sets the alpha value of the window to the new value provided
void ViewPort::setWindowAlphaValue(GLfloat newWindowAlphaValue) {
    windowAlphaValue = newWindowAlphaValue;
}

//sets the near clipping plane distance to the new value provided
void ViewPort::setNearClippingPlaneDistance(GLfloat newNearClippingPlaneDistance) {
    nearClippingPlaneDistance = newNearClippingPlaneDistance;
}

//sets the far clipping plane distance to the new value provided
void ViewPort::setFarClippingPlaneDistance(GLfloat newFarClippingPlaneDistance) {
    farClippingPlaneDistance = newFarClippingPlaneDistance;
}

//sets the title of the window to the new value provided
void ViewPort::setWindowTitle(std::string newWindowTitle) {
    windowTitle = newWindowTitle;
}

/*
 -------------------- Methods for the ViewPort class --------------------
*/
//initializes window position, window size, window background colour, window title and displays it
void ViewPort::displayWindow() {
    glutInitWindowPosition (getWindowXPosition(), getWindowYPosition());
    glutInitWindowSize (getWindowWidth(), getWindowHeight());
    glClearColor(getWindowRedColour(), getWindowGreenColour(), getWindowBlueColour(), getWindowAlphaValue());
    //glutCreateWindow(getWindowTitle().c_str());
    //glutGameModeString("1024x768:24");
    //glutEnterGameMode(); 
    glutFullScreen();
}

//refreshes the background colour of the window
void ViewPort::refreshWindowColour() {
    glClearColor (getWindowRedColour(), getWindowGreenColour(), getWindowBlueColour(), getWindowAlphaValue());
}

//initializes matrix mode and sets the gluPerspective
void ViewPort::setPerspective(GLfloat viewingAngle) {
    glViewport(0, 0, (GLsizei)getWindowWidth(), (GLsizei)getWindowHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(viewingAngle, getAspectRatio(), getNearClippingPlaneDistance(), getFarClippingPlaneDistance());
    glShadeModel (GL_SMOOTH);    // recently added by Al, watch for issues caused by this
    glMatrixMode (GL_MODELVIEW);
    glClearDepth(1.0f);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
    glDisable(GL_TEXTURE_2D);    
}
