#pragma once

#include "const.hpp"

/*
NOTE:
The term "playing" represents the scene when the game is 'actually played' (not the starting menu scene, for instance).
This should not be confused with "PLAYING", which represents a state of the "playing" scene.
*/

// States when playing
enum class GameState {
	PLAYING, DIALOGUE, MENU, CINEMATIC
};

class StateManager {
public:
    StateManager() {
        this->SetState(GameState::PLAYING);
    }

    GameState GetState() {
        return currentState;
    }

    void SetState(GameState newState) {
        currentState = newState;
    }

private:
    GameState currentState;
};

static StateManager stateManager;

// All keys of the PLAYING state
static bool playingKeys[MAX_PLAYING_KEYS];
enum {
	MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, SPRINT
};

// All keys of the DIALOGUE state
// ..
// All keys of the MENU state
// ..
// All keys of the CINEMATIC state
// ..