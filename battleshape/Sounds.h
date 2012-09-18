/*------------------------------------------------------------------------------
Project: BattleShape
Author: Shadowcat Productions
Description: This is the header file for SOUND_EFFECT and MUSIC.
------------------------------------------------------------------------------*/

/*
 -------------------- Includes for SOUND_EFFECT and MUSIC --------------------
*/
#include <stdlib.h>

#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

class SOUND_EFFECT {
public:
    //Sound Effects
    static const char* SHOT;    
    static const char* SHOT2;   
    static const char* PENETRATING_SHOT;
    static const char* EXPLOSION_ENERGY;
    static const char* EXPLOSION_LARGE;
    static const char* EXPLOSION_ENORMOUS;
    static const char* EXPLOSION_1;
    static const char* EXPLOSION_2;
    static const char* EXPLOSION_3;
    static const char* EXPLOSION_4;
    static const char* NUKE;
    static const char* LAY_MINE;
    static const char* NEW_PHASE;
    static const char* SHIELD_HIT;
    static const char* FACTORY_SHOT;
    static const char* UPGRADE_COLLECTION;
    static const char* PLAYER_RESPAWN;
    static const char* THRUSTER;
    static const char* BOING;

    static const char* MOUSEOVER_1;
    static const char* PAUSE;
};

#endif

#ifndef MUSIC_H
#define MUSIC_H

class MUSIC {
public:
    //Music
    static const char* GAME_MUSIC;
    static const char* MENU_MUSIC;

};

#endif
