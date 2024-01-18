#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "../core/components.hpp"
#include "../core/coordinator.hpp"
#include "../core/state_manager.hpp"
#include <SDL.h>

extern Coordinator game_manager;

class AnimationSystem : public System {

public:
	void update() {
		for (auto const& e : entities) {
			auto& sprites = game_manager.getComponent<SpriteComponent>(e);
			auto& transform = game_manager.getComponent<TransformComponent>(e);

			// finally check if player has moved
			if (transform.velocity.x != 0 || transform.velocity.y != 0) sprites.animated = true;
			else {
				sprites.animated = false;
				sprites.frameIndex = 0;
			}

			if (sprites.animated) {
				sprites.frameIndex = SDL_GetTicks() / sprites.animSpeed % sprites.animRects.size();
			}

			if (transform.velocity.x < 0)
				sprites.flips = SDL_FLIP_HORIZONTAL;
			if (transform.velocity.x > 0)
				sprites.flips = SDL_FLIP_NONE;
			// if (transform.velocity.y < 0)
			// if (transform.velocity.y > 0) // TODO
		}
	}
	void render(SDL_Renderer* ren) {
		for (auto const& e : entities) {
			auto& sprites = game_manager.getComponent<SpriteComponent>(e);
			auto& transform = game_manager.getComponent<TransformComponent>(e);
			SDL_Rect srcRect = sprites.animRects[sprites.frameIndex];
			SDL_Rect destRect;
			destRect.x = transform.position.x;
			destRect.y = transform.position.y;
			destRect.w = srcRect.w / 2;
			destRect.h = srcRect.h / 2;
			SDL_RenderCopyEx(ren, sprites.texture, &srcRect, &destRect, NULL, NULL, sprites.flips);
		}
	}
};