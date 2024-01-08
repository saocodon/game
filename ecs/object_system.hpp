#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "coordinator.hpp"
#include "../vec.hpp"
#include <SDL.h>

struct Transform {
	Vec position, velocity;
};

struct Sprites {
	SDL_Texture* texture;
	int w, h;
};

class ObjectSystem : public System {
public:
	void update();
	void render();
};