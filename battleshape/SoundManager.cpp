/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: The class contains all information about SoundManager.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for the SoundManager class --------------------
*/
#include "SoundManager.h"


/*
-------------------- Initialization functions for the SoundManager class --------------------
*/

//active flag
bool SoundManager::active;

//debug flag
bool SoundManager::debug;
    
//music volume
int SoundManager::musicVolume;
    
//sound effect volume
int SoundManager::soundEffectVolume;
    
//sound effect channel
int SoundManager::soundEffectChannel;

//initial sound effect channel
int SoundManager::initialSoundEffectChannel;
    
//music default channel
int SoundManager::musicChannel;
    
//music handle
FSOUND_SAMPLE* SoundManager::musicHandle;

//max number of channels
int SoundManager::maxChannels;

/*
-------------------- Initialization functions for the SoundManager class --------------------
*/

//Initializes all static SoundManager variables
bool SoundManager::initialize( bool debug_flag ){
    setDebug( debug_flag );
    activate();
    setMusicVolume(255);
    setSoundEffectVolume(20);
    setMusicChannel(1);
    setInitialSoundEffectChannel(2);    
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
        printf("\tInitial Sound Effect Channel: %i\n", getInitialSoundEffectChannel());
        printf("\tMusic Channel: %i\n", getMusicChannel());
    }

    return initialized;

}

//Stops Music and frees the music channel, closes fmod
bool SoundManager::destroy( void ){
    stopMusic();
    FSOUND_Sample_Free (musicHandle);
    FSOUND_Close();

    if(isDebug()) printf("SoundManager Destroyed");

    return true;
}

/*
 -------------------- Accessors for the SoundManager class --------------------
*/

//Accessor: active
bool SoundManager::isActive( void ){
    return active;
}

//Accessor: debug
bool SoundManager::isDebug( void ){
    return debug;
}

//Accessor: musicVolume
int SoundManager::getMusicVolume( void ){
    return musicVolume;
}

//Accessor: soundEffectVolume
int SoundManager::getSoundEffectVolume( void ){
    return soundEffectVolume;
}

//Accessor: soundEffectChannel
int SoundManager::getSoundEffectChannel( void ){
    return soundEffectChannel;
}

//Accessor: musicChannel
int SoundManager::getMusicChannel( void ){
    return musicChannel;
}

//Accessor: musicHandle
FSOUND_SAMPLE* SoundManager::getMusicHandle( void ){
    return musicHandle;
}

//Accessor: initialSoundEffectChannel
int SoundManager::getInitialSoundEffectChannel( void ){
    return initialSoundEffectChannel;
}

//Accessor: maxChannels
int SoundManager::getMaxChannels( void ){
    return maxChannels;
}

//Accessor: fmod FSOUND_IsPlaying()
bool SoundManager::isMusicPlaying( void ){
     return FSOUND_IsPlaying(musicChannel);
}


/*
 -------------------- Modifiers for the SoundManager class --------------------
*/

//Modifier: active
void SoundManager::setActive( bool newActive ){
    active = newActive;
}

//Modifier: debug
void SoundManager::setDebug( bool newDebug ){
    debug = newDebug;
}

//Modifier: active
bool SoundManager::toggleActive( void ){
    if(isActive()){
        FSOUND_SetVolume(musicChannel, 0);
        deactivate();
    }else{
        FSOUND_SetVolume(musicChannel, getMusicVolume());
        activate();
    }
    return isActive();
}

//Modifier: debug
bool SoundManager::toggleDebug( void ){
    if(isDebug()) setDebug(false);
    else setDebug(true);
    return isDebug();
}

//Modifier: active
void SoundManager::activate( void ){
    setActive(true);
}

//Modifier: active
void SoundManager::deactivate( void ){
   setActive(false);
}

//Modifier: musicVolume
void SoundManager::setMusicVolume( int newMusicVolume ){
    musicVolume = newMusicVolume;
}

//Modifier: soundEffectVolume
void SoundManager::setSoundEffectVolume( int newSoundEffectVolume ){
    soundEffectVolume = newSoundEffectVolume;
}

//Modifier: soundEffectChannel
void SoundManager::setSoundEffectChannel( int newSoundEffectChannel ){
    soundEffectChannel = newSoundEffectChannel;
}

//Modifier: musicChannel
void SoundManager::setMusicChannel( int newMusicChannel ){
    musicChannel = newMusicChannel;
}

//Modifier: musicHandle
void SoundManager::setMusicHandle( FSOUND_SAMPLE* newMusicHandle ){
    musicHandle = newMusicHandle;
}

//Modifier: initialSoundEffectChannel
void SoundManager::setInitialSoundEffectChannel( int newInitialSoundEffectChannel ){
    initialSoundEffectChannel = newInitialSoundEffectChannel;
}

//Modifier: maxChannels
void SoundManager::setMaxChannels( int newMaxChannels ){
    maxChannels = newMaxChannels;
}


/*
 -------------------- Methods for the SoundManager class --------------------
*/

//Method: Loads music 'filename' onto channel 'musicChannel'
void SoundManager::loadMusic(const char* filename){
    musicHandle = FSOUND_Sample_Load (musicChannel, filename, 0, 0, 0);
    if(isDebug()) printf("Music Loaded on Channel: %i\n", musicChannel);
}

//Method: Plays music 'filename' on channel 'musicChannel'
void SoundManager::playMusic( const char* filename ){
     if(isActive()){
        loadMusic(filename);
        FSOUND_PlaySound (musicChannel, musicHandle);
        FSOUND_SetLoopMode(musicChannel, FSOUND_LOOP_NORMAL);
        if(isDebug())printf("Music Started on Channel: %i\n", musicChannel);
     }
}

//Method: Stops music on channel 'musicChannel'
void SoundManager::stopMusic( void ){
    FSOUND_StopSound(musicChannel);
    if(isDebug()) printf("Music stopped on Channel: %i\n", musicChannel);
}

//Method: Plays sound effect 'filename' on current sound effect channel, then cycles channels
void SoundManager::playSoundEffect( const char* filename ){
    if(isActive()){
        int currentChannel = getSoundEffectChannel(); 
        FSOUND_SAMPLE* soundHandler = FSOUND_Sample_Load (currentChannel, filename, 0, 0, 0);
        FSOUND_SetVolume (currentChannel, getSoundEffectVolume());
        FSOUND_PlaySound (currentChannel, soundHandler);

        if(isDebug()) printf("Playing sound effect on channel %i\n", currentChannel);

        cycleSoundEffectChannel();
    }
}

//Method: Cycles the current sound effect channel
void SoundManager::cycleSoundEffectChannel( void ){
    int nextChannel = getSoundEffectChannel() + 1;
    if(nextChannel > getMaxChannels()){
        nextChannel = getInitialSoundEffectChannel();
    }

    if(isDebug()) printf("Cycling Sound Effect Channel from %i to %i\n", getSoundEffectChannel(), nextChannel);

    setSoundEffectChannel(nextChannel);
}


//Method: Starts a thread for '_fadeMusicOut' to fade out music on channel 'musicChannel'
void SoundManager::fadeMusicOut( void ){
    DWORD threadID;
    HANDLE thread;

    if(isDebug()) printf("Fading music out\n");

    thread = CreateThread(0, 0, _fadeMusicOut, 0, 0, &threadID);
}

//Method: Starts a thread for '_fadeMusicIn' to fade in music on channel 'musicChannel'
void SoundManager::fadeMusicIn( void ){
    DWORD threadID;
    HANDLE thread;

    if(isDebug()) printf("Fading music in\n");

    thread = CreateThread(0, 0, _fadeMusicIn, 0, 0, &threadID);
}

//Method: Starts a thread for '_fadeOutFadeIn' to fade out music on channel 'musicChannel'
//        and then fade in music 'music' on channel 'music channel'
void SoundManager::fadeOutFadeIn( const char* music ){
    DWORD threadID;
    HANDLE thread;
    thread = CreateThread(0, 0, _fadeOutFadeIn, (LPVOID)music, 0, &threadID);
}

//Method: Pauses current thread for 'Delay' milliseconds
void SoundManager::Pause(clock_t Delay){
     clock_t ExitTime; 
     ExitTime=Delay + clock(); 
     while( ExitTime > clock() ) ;
}

//Thread Function: Fades out music on channel 'musicChannel' and fades in 
//                 music 'pvParam' on channel 'musicChannel'
DWORD WINAPI SoundManager::_fadeOutFadeIn(LPVOID pvParam){
    const char* music = (const char*)pvParam;

    int channel = getMusicChannel();

    if(isDebug()) printf("Fading music out\n");

    for(int i = getMusicVolume(); i > 0; i--){
       FSOUND_SetVolume (channel, i);
       Pause(20);
    }
    stopMusic();
    if(isActive()){
        playMusic(music);

        if(isDebug()) printf("Fading music in\n");

        for(int i = 0; i > getMusicVolume(); i++){
           FSOUND_SetVolume (channel, i);
           Pause(20);
        }
    }

    return 0;
}

//Thread Function: Fades out music on channel 'musicChannel'
DWORD WINAPI SoundManager::_fadeMusicOut(LPVOID pvParam){
    int channel = getMusicChannel();
    for(int i = getMusicVolume(); i > 0; i--){
       FSOUND_SetVolume (channel, i);
       Pause(20);
    }
    stopMusic();
    FSOUND_SetVolume (channel, getMusicVolume());

    return 0;
}

//Thread Function: Fades in music 'pvParam' on channel 'musicChannel'
DWORD WINAPI SoundManager::_fadeMusicIn(LPVOID pvParam){
    if(isActive()){
        int channel = getMusicChannel();
        FSOUND_SetVolume (channel, 0);
        for(int i = 0; i > getMusicVolume(); i++){
           FSOUND_SetVolume (channel, i);
           Pause(20);
        }
    }

    return 0;
}
