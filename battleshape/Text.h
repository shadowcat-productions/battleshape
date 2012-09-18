/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Text class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Text class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#ifndef Text_H
#define Text_H

class Text {
public:
    Text();
    ~Text();
    bool drawText(char text[], int numberOfCharacters, float x, float y, float z, float size, float spacer);
    bool drawNumber(int number, float x, float y, float z, float size, float spacer);
};
#endif
