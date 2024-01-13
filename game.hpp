#pragma once

#include <memory>
// entity has already been included in 'coordinator.hpp'
// Coordinator has already been included in 'object_system'
// SDL has already been included in 'object_system'
#include "ecs/object_system.hpp"
#include "texture_manager.hpp"

extern Coordinator game_manager;

class Game {
public:
	static SDL_Event ev;
	static SDL_Renderer* renderer;
	static bool keyStates[KEY_STATES];

	Game() {
		memset(keyStates, 0, sizeof keyStates);
	}
	~Game() {}

	void init(const char* title, int x, int y, int w, int h, int flags);
	void handleEvents();
	void update();
	void render();
	void clean();
	
	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	std::shared_ptr<ObjectSystem> objectSystem;
	entity player;
};