#include "game.hpp"
#include <iostream>
// object_system has already been included in 'game.hpp'

Coordinator game_manager;
SDL_Event Game::ev;
SDL_Renderer* Game::renderer = nullptr;

void Game::init(const char* title, int x, int y, int w, int h, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (!window) return;
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (!renderer) return;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;

		// Do work here
		game_manager.init();
		game_manager.registerComponent<Transform>();
		game_manager.registerComponent<Sprites>();
		objectSystem = game_manager.registerSystem<ObjectSystem>();
		Signature signature;
		// include "transform", "sprites" components into the ObjectSystem system
		signature.set(game_manager.getComponentType<Transform>());
		signature.set(game_manager.getComponentType<Sprites>());
		game_manager.setSystemSignature<ObjectSystem>(signature);

		// get ID for player
		player = game_manager.createEntity();
		// quickly set up a rectangle on screen
		SDL_Rect dstR; dstR.w = dstR.h = 64; dstR.x = dstR.y = 50;
		SDL_Texture* t = TextureManager::LoadTexture("assets/player.png", renderer);
		game_manager.addComponent(player, Sprites{ t, 64, 64 });
		game_manager.addComponent(player, Transform{ Vec(50, 50), Vec(0, 0) });
	}
	else {
		isRunning = false;
	}
}

void Game::handleEvents() {
	SDL_PollEvent(&ev);
	switch (ev.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
	}
}

void Game::update() {
	objectSystem->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	objectSystem->render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}