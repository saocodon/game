#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "coordinator.hpp"
#include "vec.hpp"
#include "components.hpp"
#include "const.hpp"

extern Coordinator game_manager;

class MovementSystem : public System {
private:
	bool keyStates[4];
	enum { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN };
public:
	void update(SDL_Event ev) {
		switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				keyStates[MOVE_UP] = true;
				break;
			case SDLK_a:
				keyStates[MOVE_LEFT] = true;
				break;
			case SDLK_s:
				keyStates[MOVE_DOWN] = true;
				break;
			case SDLK_d:
				keyStates[MOVE_RIGHT] = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				keyStates[MOVE_UP] = false;
				break;
			case SDLK_a:
				keyStates[MOVE_LEFT] = false;
				break;
			case SDLK_s:
				keyStates[MOVE_DOWN] = false;
				break;
			case SDLK_d:
				keyStates[MOVE_RIGHT] = false;
				break;
			}
			break;
		}
		for (auto const& e : entities) {
			auto& transform = game_manager.getComponent<TransformComponent>(e);
			// keyboard handling has been moved to game.cpp
			if (e == 0) {
				// Smooth movement:
				if (keyStates[MOVE_UP] && keyStates[MOVE_DOWN]) transform.velocity.y = 0;
				else {
					transform.velocity.y = (keyStates[MOVE_UP] * -1.0);
					transform.velocity.y += (keyStates[MOVE_DOWN] * 1.0);
				}
				if (keyStates[MOVE_LEFT] && keyStates[MOVE_RIGHT]) transform.velocity.x = 0;
				else {
					transform.velocity.x = (keyStates[MOVE_LEFT] * -1.0);
					transform.velocity.x += (keyStates[MOVE_RIGHT] * 1.0);
				}
			}

			transform.position.x += transform.velocity.x;
			transform.position.y += transform.velocity.y;
		}
	}
};