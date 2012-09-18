/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for the SoundManager2 class.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the SoundManager class --------------------
*/
#include <stdlib.h>
#include <iostream>
#include <fmod.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#ifndef SoundManager_H
#define SoundManager_H


class SoundManager {
public:
    /*
    -------------------- Control functions for the SoundManager class --------------------
    */
    static bool initialize( bool debug_flag = false );
    static bool destroy( void );

    /*
    -------------------- Accessors for the SoundManager class --------------------
    */
    
    static bool isActive( void );
    static bool isDebug( void );
    static int getMusicVolume( void );
    static int getSoundEffectVolume( void );
    static int getSoundEffectChannel( void );
    static int getMusicChannel( void );
    static FSOUND_SAMPLE* getMusicHandle( void );
    static int getInitialSoundEffectChannel( void );
    static int getMaxChannels( void );
    bool SoundManager::isMusicPlaying( void );
        
    /*
    -------------------- Modifiers for the SoundManager class --------------------
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
    static void setMusicHandle( FSOUND_SAMPLE* newMusicHandle );
    static void setInitialSoundEffectChannel( int newInitialSoundEffectChannel );
    static void setMaxChannels( int newMaxChannels );

    
    /*
    -------------------- Methods for the SoundManager class --------------------
    */

    static void loadMusic(const char* filename);
    static void playMusic(const char* filename);
    static void stopMusic( void );
    static void playSoundEffect( const char* filename );
    static void cycleSoundEffectChannel( void );
    static void SoundManager::fadeMusicOut( void );
    static void SoundManager::fadeMusicIn( void );
    static void SoundManager::fadeOutFadeIn( const char* music );

private:
    /*
    -------------------- Private Methods for the SoundManager class --------------------
    */
    static void Pause(clock_t Delay);

    /*
    -------------------- Variables for the SoundManager class --------------------
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
    
    //music handle
    static FSOUND_SAMPLE* musicHandle;

    //max number of channels
    static int maxChannels;

    //Threads for sound fade
    static DWORD WINAPI _fadeMusicOut(LPVOID pvParam);
    static DWORD WINAPI _fadeMusicIn(LPVOID pvParam);
    static DWORD WINAPI _fadeOutFadeIn(LPVOID pvParam);

};


#endif
