#pragma once

#include "const.hpp"

struct PlayingKeyboardManager {
	bool playerKeyStates[MAX_PLAYER_KEY_STATES];
	enum { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, SPRINT };
};
