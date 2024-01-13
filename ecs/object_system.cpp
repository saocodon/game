#include "object_system.hpp"
#include "../texture_manager.hpp"
#include "../game.hpp"

extern Coordinator game_manager;
bool Game::keyStates[KEY_STATES];

void ObjectSystem::update() {
	for (auto const& e : entities) {
		auto& transform = game_manager.getComponent<Transform>(e);
		// keyboard handling (temp.)
		if (e == 0) {
			if (Game::ev.type == SDL_KEYDOWN) {
				switch (Game::ev.key.keysym.sym) {
				case SDLK_w:
					Game::keyStates[MOVE_UP] = true;
					break;
				case SDLK_a:
					Game::keyStates[MOVE_LEFT] = true;
					break;
				case SDLK_s:
					Game::keyStates[MOVE_DOWN] = true;
					break;
				case SDLK_d:
					Game::keyStates[MOVE_RIGHT] = true;
					break;
				}
			}
			if (Game::ev.type == SDL_KEYUP) {
				switch (Game::ev.key.keysym.sym) {
				case SDLK_w:
					Game::keyStates[MOVE_UP] = false;
					break;
				case SDLK_a:
					Game::keyStates[MOVE_LEFT] = false;
					break;
				case SDLK_s:
					Game::keyStates[MOVE_DOWN] = false;
					break;
				case SDLK_d:
					Game::keyStates[MOVE_RIGHT] = false;
					break;
				}
			}
		}
		// Smooth movement:
		if (Game::keyStates[MOVE_UP] && Game::keyStates[MOVE_DOWN]) transform.velocity.y = 0;
		else {
			transform.velocity.y = (Game::keyStates[MOVE_UP] * -1.0);
			transform.velocity.y += (Game::keyStates[MOVE_DOWN] * 1.0);
		}
		if (Game::keyStates[MOVE_LEFT] && Game::keyStates[MOVE_RIGHT]) transform.velocity.x = 0;
		else {
			transform.velocity.x = (Game::keyStates[MOVE_LEFT] * -1.0);
			transform.velocity.x += (Game::keyStates[MOVE_RIGHT] * 1.0);
		}

		transform.position.x += transform.velocity.x;
		transform.position.y += transform.velocity.y;
	}
}

void ObjectSystem::render() {
	for (auto const& e : entities) {
		auto& sprites = game_manager.getComponent<Sprites>(e);
		auto& transform = game_manager.getComponent<Transform>(e);
		SDL_Rect destR = { static_cast<int>(std::round(transform.position.x)),
						   static_cast<int>(std::round(transform.position.y)),
						   sprites.w, sprites.h };
		SDL_RenderCopy(Game::renderer, sprites.texture, NULL, &destR);
	}
}