#pragma once

#include <memory>
// entity has already been included in 'coordinator.hpp'
// Coordinator has already been included in 'object_system'
// SDL has already been included in 'object_system'
#include "../sys/movement_system.hpp"
#include "../sys/animation_system.hpp"
#include "texture_manager.hpp"

extern Coordinator game_manager;

class Game {
public:
	Game() {
		currentGameState = PLAYING;
	}
	~Game() {}

	void init(const char* title, int x, int y, int w, int h, int flags);
	void handleEvents();
	void update();
	void render();
	void clean();
	
	bool running() { return isRunning; }

private:
	char currentGameState;
	enum { PLAYING, DIALOGUE, MENU };

	bool isRunning;
	SDL_Window* window;
	SDL_Event ev;
	SDL_Renderer* renderer;
	std::shared_ptr<MovementSystem> movementSystem;
	std::shared_ptr<AnimationSystem> animationSystem;
	entity player;
};