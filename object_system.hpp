#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "coordinator.hpp"
#include <SDL.h>

struct Transform {
	int x, y;
};

struct Sprites {
	SDL_Rect dst;
	SDL_Texture* texture;
};

class ObjectSystem : public System {
public:
	void init(const char* img, SDL_Renderer* ren, int x, int y);
	void update();
private:
	SDL_Renderer* renderer;
};