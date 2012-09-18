/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Vector system.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Vector class --------------------
*/

#include "Vector.h"

/*
-------------------- Constructors for the Vector class --------------------
*/
Vector::Vector(GLfloat a, GLfloat b, GLfloat c) : X(a), Y(b), Z(c)
{
}

Vector::Vector() : X(0.0), Y(0.0), Z(0.0)
{
}

/*
-------------------- Destructor for the Vector class --------------------
*/
Vector::~Vector() {

}

/*
-------------------- Accessors for the Vector class --------------------
*/
//function to return X component of a vector
const GLfloat Vector::getX() const {
    return X;
}
//function to return Y component of a vector
const GLfloat Vector::getY() const {
    return Y;
}
//function to return X component of a vector
const GLfloat Vector::getZ() const {
    return Z;
}

//function to return length of a vector
const GLfloat Vector::getLength() const {
     return pow((pow(X,2)+pow(Y,2)+pow(Z,2)),0.5);
}
/*
-------------------- Modifiers for the Vector class --------------------
*/
//functions that set the components of a vector
void Vector::set(GLfloat a, GLfloat b, GLfloat c) {
    X = a;
    Y = b;
    Z = c;
}

void Vector::multiply(GLfloat a) {
    X = X*a;
    Y = Y*a;
    Z = Z*a;
}

void Vector::add(Vector a) {
    X = X+a.getX();
    Y = Y+a.getY();
    Z = Z+a.getZ();
}

void Vector::add(float addX, float addY, float addZ) {
    X = X+addX;
    Y = Y+addY;
    Z = Z+addZ;
}

const float Vector::angleBetween(Vector a) const {
return acos(dotProduct(a)/(getLength()*a.getLength()));
}

const float Vector::dotProduct(Vector a) const {
return getX()*a.getX()+getY()*a.getY()+getZ()*a.getZ();
}

void Vector::rotate(char axis, GLfloat theta) {
    GLfloat a,b,c;
    a = X;
    b = Y;
    c = Z;

     if (axis == 'z')
     {
         X=cos(-theta)*a-sin(-theta)*b;
         Y=sin(-theta)*a+cos(-theta)*b;
     }
     else if (axis == 'x')
     {
         Y=cos(-theta)*b-sin(-theta)*c;
         Z=sin(-theta)*b+cos(-theta)*c;
     }
     else if (axis == 'y')
     {
         X=cos(-theta)*a-sin(-theta)*c;
         Z=sin(-theta)*a+cos(-theta)*c;
     }
}

float Vector::normalize() {
    GLfloat length = pow((pow((float)X,2.0)+pow((float)Y,2.0)+pow((float)Z,2.0)),0.5);
    if(length>0)
    {
        X = X/length;
        Y = Y/length;
        Z = Z/length;
    }
    return length;
}

const Vector Vector::getNormal() const {
    GLfloat length = pow((pow(X,2),pow(Y,2),pow(Z,2)),0.5);
    GLfloat nx, ny, nz;
    nx = X/length;
    ny = Y/length;
    nz = Z/length;

    Vector returnVector;
    returnVector.set(nx, ny, nz);
    return returnVector;
}
