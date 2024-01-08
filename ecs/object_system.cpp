#include "object_system.hpp"
#include "../texture_manager.hpp"
#include "../game.hpp"

extern Coordinator game_manager;

void ObjectSystem::update() {
	for (auto const& e : entities) {
		auto& transform = game_manager.getComponent<Transform>(e);
		// keyboard handling (temp.)
		if (e == 0) {
			if (Game::ev.type == SDL_KEYDOWN) {
				switch (Game::ev.key.keysym.sym) {
				case SDLK_w:
					transform.velocity.y = -1;
					break;
				case SDLK_a:
					transform.velocity.x = -1;
					break;
				case SDLK_s:
					transform.velocity.y = 1;
					break;
				case SDLK_d:
					transform.velocity.x = 1;
					break;
				}
			}
			if (Game::ev.type == SDL_KEYUP) {
				switch (Game::ev.key.keysym.sym) {
					case SDLK_w:
						transform.velocity.y = 0;
						break;
					case SDLK_a:
						transform.velocity.x = 0;
						break;
					case SDLK_s:
						transform.velocity.y = 0;
						break;
					case SDLK_d:
						transform.velocity.x = 0;
						break;
				}
			}
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