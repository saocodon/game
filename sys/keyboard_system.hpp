#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "../core/const.hpp"
#include "../core/coordinator.hpp"
#include "../core/state_manager.hpp"
#include <SDL.h>

// Update keyboard input
class KeyboardSystem : public System {

public:
	void update(SDL_Event ev) {
		switch (stateManager.GetState()) {

		//PLAYING
		case GameState::PLAYING:
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.sym) {
				case SDLK_w:
					playingKeys[MOVE_UP] = true;
					break;
				case SDLK_a:
					playingKeys[MOVE_LEFT] = true;
					break;
				case SDLK_s:
					playingKeys[MOVE_DOWN] = true;
					break;
				case SDLK_d:
					playingKeys[MOVE_RIGHT] = true;
					break;
				case SDLK_LSHIFT:
					playingKeys[SPRINT] = true;
					break;
				case SDLK_ESCAPE:
					stateManager.SetState(GameState::MENU);
					break;
				}
				break;
			}

		/*case GameState::MENU:
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.sym) {
				case SDLK_ESCAPE:
					stateManager.SetState(GameState::PLAYING);
					break;
				}
				break;
			}*/
		}
		switch (ev.type) {
		case SDL_KEYUP:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				playingKeys[MOVE_UP] = false;
				break;
			case SDLK_a:
				playingKeys[MOVE_LEFT] = false;
				break;
			case SDLK_s:
				playingKeys[MOVE_DOWN] = false;
				break;
			case SDLK_d:
				playingKeys[MOVE_RIGHT] = false;
				break;
			case SDLK_LSHIFT:
				playingKeys[SPRINT] = false;
				break;
			}
			break;
		}
	}

};
