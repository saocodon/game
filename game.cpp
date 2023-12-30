#include "game.hpp"
#include "texture_manager.hpp"
#include "game_object.hpp"

GameObject* player;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int x, int y, int w, int h, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("Subsystems initialized\n");
		window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (window)
			printf("Window created\n");
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			printf("Renderer created\n");
		}
		isRunning = true;
		// Do work here
		player = new GameObject("assets/player.png", renderer, 0, 0, 0, 0, 0, 0);
	}
	else {
		isRunning = false;
	}
}

void Game::handleEvents() {
	SDL_Event ev;
	SDL_PollEvent(&ev);
	switch (ev.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	player->Update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned\n");
}