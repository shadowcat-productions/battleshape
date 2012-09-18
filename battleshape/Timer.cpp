/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about the Timer.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the Camera class --------------------
*/

#include "Timer.h"

/*
 -------------------- Constructors for the Timer class --------------------
*/
Timer::Timer() : isPaused(false){
}

/*
 -------------------- Destructor for the Timer class --------------------
*/
Timer::~Timer(){
      maxTimer=1.0;
}

/*
 -------------------- Accessors for the Timer class --------------------
*/
const float Timer::getTimer() const{
     if (isPaused) return 0;
     return timer;
}

const float Timer::getLastTimer() const{
     return lastTimer;
}

/*
 -------------------- Modifiers for the Timer class --------------------
*/
void Timer::setTimer(float newTimer){
     if(newTimer>2.5)
          timer = 2.5;
     else
          timer = newTimer;
}

void Timer::setLastTimer(float newLastTimer){
    lastTimer = newLastTimer;
}

void Timer::pause() {
     if (isPaused) { isPaused = false; }
     else if (!isPaused) {isPaused = true; }

}

const bool Timer::getPauseStatus() const{
     if (isPaused) return true;
     else return false;
}

/*
 -------------------- Methods for the Timer class --------------------
*/
void Timer::updateTimer(){
         const float t2 = glutGet(GLUT_ELAPSED_TIME) / 20.0;
         setTimer(t2 - getLastTimer());
         setLastTimer(t2);
}

