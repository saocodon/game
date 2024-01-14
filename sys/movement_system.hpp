#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "coordinator.hpp"
#include "vec.hpp"
#include "components.hpp"
#include "const.hpp"
#include "../core/keyboard_manager.hpp"

extern Coordinator game_manager;

class MovementSystem : public System {

public:
	void update(SDL_Event ev, PlayingKeyboardManager* kb) {
		switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				kb->playerKeyStates[kb->MOVE_UP] = true;
				break;
			case SDLK_a:
				kb->playerKeyStates[kb->MOVE_LEFT] = true;
				break;
			case SDLK_s:
				kb->playerKeyStates[kb->MOVE_DOWN] = true;
				break;
			case SDLK_d:
				kb->playerKeyStates[kb->MOVE_RIGHT] = true;
				break;
			case SDLK_LSHIFT:
				kb->playerKeyStates[kb->SPRINT] = true;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				kb->playerKeyStates[kb->MOVE_UP] = false;
				break;
			case SDLK_a:
				kb->playerKeyStates[kb->MOVE_LEFT] = false;
				break;
			case SDLK_s:
				kb->playerKeyStates[kb->MOVE_DOWN] = false;
				break;
			case SDLK_d:
				kb->playerKeyStates[kb->MOVE_RIGHT] = false;
				break;
			case SDLK_LSHIFT:
				kb->playerKeyStates[kb->SPRINT] = false;
				break;
			}
			break;
		}
		for (auto const& e : entities) {
			auto& transform = game_manager.getComponent<TransformComponent>(e);
			// keyboard handling has been moved to game.cpp
			if (e == 0) {
				if (kb->playerKeyStates[kb->MOVE_UP] && kb->playerKeyStates[kb->MOVE_DOWN]) transform.velocity.y = 0;
				else {
					transform.velocity.y = (kb->playerKeyStates[kb->MOVE_UP] * -1.0);
					transform.velocity.y += (kb->playerKeyStates[kb->MOVE_DOWN] * 1.0);
				}
				if (kb->playerKeyStates[kb->MOVE_LEFT] && kb->playerKeyStates[kb->MOVE_RIGHT]) transform.velocity.x = 0;
				else {
					transform.velocity.x = (kb->playerKeyStates[kb->MOVE_LEFT] * -1.0);
					transform.velocity.x += (kb->playerKeyStates[kb->MOVE_RIGHT] * 1.0);
				}
				if (kb->playerKeyStates[kb->SPRINT]) {
					transform.velocity.x *= SPRINT_SPEED;
					transform.velocity.y *= SPRINT_SPEED;
				}

				transform.position.x += transform.velocity.x;
				transform.position.y += transform.velocity.y;
			}

			
		}
	}
};