#pragma once

#include "const.hpp"

/*
NOTE:
The term "playing" represents the scene when the game is 'actually played' (not the menu scene, for instance).
This should not be confused with "PLAYING", which represents a state of "playing".
*/

// States when playing
static gamestate currentGameState;
enum { PLAYING, DIALOGUE, MENU, CINEMATIC };

// All keys of the PLAYING state
static bool playingKeys[MAX_PLAYING_KEYS];
enum { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, SPRINT };

// All keys of the DIALOGUE state
// ..
// All keys of the MENU state
// ..
// All keys of the CINEMATIC state
// ..