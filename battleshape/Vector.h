/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Vector class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Vector class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>

#ifndef Vector_H
#define Vector_H

class Vector {
public:
    /*
    -------------------- Constructors for the Vector class --------------------
    */
    Vector(GLfloat X, GLfloat Y, GLfloat Z);
    Vector();

    /*
    -------------------- Destructor for the Vector class --------------------
    */
    ~Vector();

    /*
     -------------------- Accessors for the Vector class --------------------
     */
    const GLfloat getX() const;
    const GLfloat getY() const;
    const GLfloat getZ() const;
    /*
    -------------------- Modifiers for the Vector class --------------------
    */
    void set(GLfloat a, GLfloat b, GLfloat c); // Set the vector's components
    void multiply(GLfloat a); // multiply the vectors components by a scalar
    void add(Vector a); // multiply the vectors components by a scalar
    void add(float addX, float addY, float addZ); // multiply the vectors components by a scalar
    const float angleBetween(Vector a) const; // finds the angle between this vector and the one passed to it
    const float dotProduct(Vector a) const; // finds the dot product of this vector and the one passed to it
    void rotate(char axis, GLfloat theta); // rotates the vector about given axis

    /*
     -------------------- Methods for the Vector class --------------------
     */
    float normalize(); // Normalizes this vector
    const Vector getNormal () const; // Return a normalized vector of the target vector
    const GLfloat getLength () const; // Returns the length of the vector

private:
    /*
    -------------------- Variables for the Vector class --------------------
    */
    GLfloat X;
    GLfloat Y;
    GLfloat Z;
};
#endif
