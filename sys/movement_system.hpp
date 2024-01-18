#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "../core/coordinator.hpp"
#include "../core/vec.hpp"
#include "../core/components.hpp"
#include "../core/const.hpp"
#include "../core/state_manager.hpp"

extern Coordinator game_manager;

class MovementSystem : public System {

public:

	void update(SDL_Event ev) {

		for (auto const& e : entities) {
			auto& transform = game_manager.getComponent<TransformComponent>(e);
			if (e == 0) {
				if (playingKeys[MOVE_UP] && playingKeys[MOVE_DOWN]) transform.velocity.y = 0;
				else {
					transform.velocity.y = (playingKeys[MOVE_UP] * -1.0);
					transform.velocity.y += (playingKeys[MOVE_DOWN] * 1.0);
				}
				if (playingKeys[MOVE_LEFT] && playingKeys[MOVE_RIGHT]) transform.velocity.x = 0;
				else {
					transform.velocity.x = (playingKeys[MOVE_LEFT] * -1.0);
					transform.velocity.x += (playingKeys[MOVE_RIGHT] * 1.0);
				}
				if (playingKeys[SPRINT]) {
					transform.velocity.x *= SPRINT_SPEED;
					transform.velocity.y *= SPRINT_SPEED;
				}

				transform.position.x += transform.velocity.x;
				transform.position.y += transform.velocity.y;
			}

			
		}
	}
};