/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the Timer class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Timer class --------------------
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

#ifndef Timer_H
#define Timer_H


class Timer {
public:
    /*
    -------------------- Constructor for the Timer class --------------------
    */
    Timer();

    /*
    -------------------- Destructor for the Timer class --------------------
    */
    ~Timer();

    /*
    -------------------- Accessors for the Timer class --------------------
    */
    const float getTimer() const;
    const float getLastTimer() const;
    const bool getPauseStatus() const;
    /*
    -------------------- Modifiers for the Timer class --------------------
    */
    void setTimer(float newTimer);
    void setLastTimer(float newLastTimer);
    /*
    -------------------- Methods for the Timer class --------------------
    */
    void updateTimer();
    void pause();

private:
    /*
    -------------------- Variables for the Timer class --------------------
    */
    float timer;
    float lastTimer;
    float maxTimer;
    bool isPaused;
};


#endif
