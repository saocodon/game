#pragma once

#include <SDL.h>
#include <vector>
#include "vec.hpp"

struct SpriteComponent {
	SDL_Texture* texture;
	std::vector<SDL_Rect> animRects;
	// frameCount = animRects.size()
	int frameIndex, animSpeed;
	bool animated;
	SDL_RendererFlip flips;
};


struct TransformComponent {
	Vec position, velocity;
};