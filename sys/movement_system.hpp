#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "coordinator.hpp"
#include "vec.hpp"
#include "components.hpp"
#include "const.hpp"

extern Coordinator game_manager;

class MovementSystem : public System {
private:
	bool playerKeyStates[MAX_PLAYER_KEY_STATES];
	enum { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN };
public:
	void update(SDL_Event ev) {
		switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				playerKeyStates[MOVE_UP] = true;
				break;
			case SDLK_a:
				playerKeyStates[MOVE_LEFT] = true;
				break;
			case SDLK_s:
				playerKeyStates[MOVE_DOWN] = true;
				break;
			case SDLK_d:
				playerKeyStates[MOVE_RIGHT] = true;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				playerKeyStates[MOVE_UP] = false;
				break;
			case SDLK_a:
				playerKeyStates[MOVE_LEFT] = false;
				break;
			case SDLK_s:
				playerKeyStates[MOVE_DOWN] = false;
				break;
			case SDLK_d:
				playerKeyStates[MOVE_RIGHT] = false;
				break;
			}
			break;
		}
		for (auto const& e : entities) {
			auto& transform = game_manager.getComponent<TransformComponent>(e);
			// keyboard handling has been moved to game.cpp
			if (e == 0) {
				if (playerKeyStates[MOVE_UP] && playerKeyStates[MOVE_DOWN]) transform.velocity.y = 0;
				else {
					transform.velocity.y = (playerKeyStates[MOVE_UP] * -1.0);
					transform.velocity.y += (playerKeyStates[MOVE_DOWN] * 1.0);
				}
				if (playerKeyStates[MOVE_LEFT] && playerKeyStates[MOVE_RIGHT]) transform.velocity.x = 0;
				else {
					transform.velocity.x = (playerKeyStates[MOVE_LEFT] * -1.0);
					transform.velocity.x += (playerKeyStates[MOVE_RIGHT] * 1.0);
				}
			}

			transform.position.x += transform.velocity.x;
			transform.position.y += transform.velocity.y;
		}
	}
};