#pragma once

#include <SDL.h>
#include <stdio.h>

const int FPS = 60;
const int frameDelay = 1000 / FPS;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int w, int h, int flags);
	void handleEvents();
	void update();
	void render();
	void clean();
	
	bool running() { return isRunning; }
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};