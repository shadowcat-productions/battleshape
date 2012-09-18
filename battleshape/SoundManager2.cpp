/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about SoundManager2.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the SoundManager2 class --------------------
*/
#include "SoundManager2.h"
#include <stdlib.h>
#include <iostream>
#include <fmod.h>

/*
-------------------- Initialization functions for the SoundManager2 class --------------------
*/

//active flag
bool SoundManager2::active;

//active flag
bool SoundManager2::debug;
    
//music volume
int SoundManager2::musicVolume;
    
//sound effect volume
int SoundManager2::soundEffectVolume;
    
//sound effect channel
int SoundManager2::soundEffectChannel;

//initial sound effect channel
int SoundManager2::initialSoundEffectChannel;
    
//music default channel
int SoundManager2::musicChannel;

//music swap channel
int SoundManager2::swapMusicChannel;
    
//music handle
FSOUND_SAMPLE* SoundManager2::musicHandle;

//swap music handle
FSOUND_SAMPLE* SoundManager2::swapMusicHandle;

//max number of channels
int SoundManager2::maxChannels;

/*
-------------------- Initialization functions for the SoundManager2 class --------------------
*/
bool SoundManager2::initialize( bool debug_flag ){
    setDebug( debug_flag );
    activate();
    setMusicVolume(255);
    setSoundEffectVolume(255);
    setMusicChannel(1);
    setSwapMusicChannel(2);
    setInitialSoundEffectChannel(3);    
    setSoundEffectChannel(getInitialSoundEffectChannel());
    setMaxChannels(64);

    bool initialized = FSOUND_Init (44100, getMaxChannels(), 0);

    if(isDebug()){
        printf("SoundManager Initialization (debug: %i):\n", isDebug());
        printf("\tActive: %i\n", isActive());
        printf("\tMusic Volume: %i\n", getMusicVolume());
        printf("\tSound Effect Volume: %i\n", getSoundEffectVolume());
        printf("\tSound Effect Channel: %i\n", getSoundEffectChannel());
        printf("\tMusic Channel: %i\n", getMusicChannel());
        printf("\tSwap Music Channel: %i\n", getSwapMusicChannel());
        printf("\tInitial Sound Effect Channel: %i\n", getInitialSoundEffectChannel());
        printf("\tMusic Channel: %i\n", getMusicChannel());
    }

    return initialized;

}

bool SoundManager2::destroy( void ){
    stopMusic();
    FSOUND_Sample_Free (musicHandle);
    FSOUND_Sample_Free (swapMusicHandle);
    FSOUND_Close();

    if(isDebug()){
        printf("SoundManager Destroyed");
    }

    return true;
}

/*
 -------------------- Accessors for the SoundManager2 class --------------------
*/
bool SoundManager2::isActive( void ){
    return active;
}

bool SoundManager2::isDebug( void ){
    return debug;
}

int SoundManager2::getMusicVolume( void ){
    return musicVolume;
}

int SoundManager2::getSoundEffectVolume( void ){
    return soundEffectVolume;
}

int SoundManager2::getSoundEffectChannel( void ){
    return soundEffectChannel;
}

int SoundManager2::getMusicChannel( void ){
    return musicChannel;
}

int SoundManager2::getSwapMusicChannel( void ){
    return swapMusicChannel;
}

FSOUND_SAMPLE* SoundManager2::getMusicHandle( void ){
    return musicHandle;
}

FSOUND_SAMPLE* SoundManager2::getSwapMusicHandle( void ){
    return swapMusicHandle;
}

int SoundManager2::getInitialSoundEffectChannel( void ){
    return initialSoundEffectChannel;
}

int SoundManager2::getMaxChannels( void ){
    return maxChannels;
}


/*
 -------------------- Modifiers for the SoundManager2 class --------------------
*/
void SoundManager2::setActive( bool newActive ){
    active = newActive;
}

void SoundManager2::setDebug( bool newDebug ){
    debug = newDebug;
}

bool SoundManager2::toggleActive( void ){
    if(isActive()) deactivate();
    else activate();
    return isActive();
}

bool SoundManager2::toggleDebug( void ){
    if(isDebug()) setDebug(false);
    else setDebug(true);
    return isDebug();
}

void SoundManager2::activate( void ){
    setActive(true);
}

void SoundManager2::deactivate( void ){
   setActive(false);
}

void SoundManager2::setMusicVolume( int newMusicVolume ){
    musicVolume = newMusicVolume;
}

void SoundManager2::setSoundEffectVolume( int newSoundEffectVolume ){
    soundEffectVolume = newSoundEffectVolume;
}

void SoundManager2::setSoundEffectChannel( int newSoundEffectChannel ){
    soundEffectChannel = newSoundEffectChannel;
}

void SoundManager2::setMusicChannel( int newMusicChannel ){
    musicChannel = newMusicChannel;
}

void SoundManager2::setSwapMusicChannel( int newSwapMusicChannel ){
    swapMusicChannel = newSwapMusicChannel;
}

void SoundManager2::setMusicHandle( FSOUND_SAMPLE* newMusicHandle ){
    musicHandle = newMusicHandle;
}

void SoundManager2::setSwapMusicHandle( FSOUND_SAMPLE* newSwapMusicHandle ){
    swapMusicHandle = newSwapMusicHandle;
}

void SoundManager2::setInitialSoundEffectChannel( int newInitialSoundEffectChannel ){
    initialSoundEffectChannel = newInitialSoundEffectChannel;
}

void SoundManager2::setMaxChannels( int newMaxChannels ){
    maxChannels = newMaxChannels;
}


/*
 -------------------- Methods for the SoundManager2 class --------------------
*/

void SoundManager2::loadMusic(const char* filename){
    musicHandle = FSOUND_Sample_Load (musicChannel, filename, 0, 0, 0);
    if(isDebug()){
        printf("Music Loaded on Channel: %i\n", musicChannel);
    }
    //TODO allow loading a dictionary of music and playing them based on a selection
}

void SoundManager2::playMusic( const char* filename ){   
     if(isActive()){
        loadMusic(filename);
        FSOUND_PlaySound (musicChannel, musicHandle);
        if(isDebug()){
            printf("Music Started on Channel: %i\n", musicChannel);
        }
        //TODO cycle the music channels using swapMusicHandle and swapMusicChannel 
        //allowing a fade in/fade out kinda deal
     }
}

void SoundManager2::stopMusic( void ){
    FSOUND_StopSound(musicChannel);
    if(isDebug()){
        printf("Music stopped on Channel: %i\n", musicChannel);
    }
    //TODO if we have multiple music channels, stop all of them
    //TODO another function allowing you to stop just 1 music channel
}
