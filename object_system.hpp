#pragma once

// system_manager has already been included in 'coordinator.hpp'
#include "coordinator.hpp"
#include <SDL.h>

struct Transform {
	int x, y;
};

struct Sprites {
	SDL_Texture* texture;
};

class ObjectSystem : public System {
public:
	void update();
};