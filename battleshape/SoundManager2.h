/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the SoundManager2 class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the SoundManager2 class --------------------
*/
#include <stdlib.h>
#include <iostream>
#include <fmod.h>

#ifndef SoundManager2_H
#define SoundManager2_H


class SoundManager2 {
public:
    /*
    -------------------- Control functions for the SoundManager2 class --------------------
    */
    static bool initialize( bool debug_flag = false );
    static bool destroy( void );

    /*
    -------------------- Accessors for the SoundManager2 class --------------------
    */
    
    static bool isActive( void );
    static bool isDebug( void );
    static int getMusicVolume( void );
    static int getSoundEffectVolume( void );
    static int getSoundEffectChannel( void );
    static int getMusicChannel( void );
    static int getSwapMusicChannel( void );
    static FSOUND_SAMPLE* getMusicHandle( void );
    static FSOUND_SAMPLE* getSwapMusicHandle( void );
    static int getInitialSoundEffectChannel( void );
    static int getMaxChannels( void );
        
    /*
    -------------------- Modifiers for the SoundManager2 class --------------------
    */
    static void setActive( bool newActive );
    static void setDebug( bool newDebug );
    static bool toggleActive( void );
    static bool toggleDebug( void );
    static void activate( void );
    static void deactivate( void );
    static void setMusicVolume( int newMusicVolume );
    static void setSoundEffectVolume( int newSoundEffectVolume );
    static void setSoundEffectChannel( int newSoundEffectChannel );
    static void setMusicChannel( int newMusicChannel );
    static void setSwapMusicChannel( int newSwapMusicChannel );
    static void setMusicHandle( FSOUND_SAMPLE* newMusicHandle );
    static void setSwapMusicHandle( FSOUND_SAMPLE* newSwapMusicHandle );
    static void setInitialSoundEffectChannel( int newInitialSoundEffectChannel );
    static void setMaxChannels( int newMaxChannels );
    
    /*
    -------------------- Methods for the SoundManager2 class --------------------
    */

    static void loadMusic(const char* filename);
    static void playMusic(const char* filename);
    static void stopMusic( void );

private:
    /*
    -------------------- Variables for the SoundManager2 class --------------------
    */

    //active flag
    static bool debug;
    
    //active flag
    static bool active;
    
    //music volume
    static int musicVolume;
    
    //sound effect volume
    static int soundEffectVolume;
    
    //sound effect channel
    static int soundEffectChannel;

    //initial sound effect channel
    static int initialSoundEffectChannel;
    
    //music default channel
    static int musicChannel;

    //music default channel
    static int swapMusicChannel;
    
    //music handle
    static FSOUND_SAMPLE* musicHandle;

    //music handle
    static FSOUND_SAMPLE* swapMusicHandle;

    //max number of channels
    static int maxChannels;
};


#endif
