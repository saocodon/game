#include "game.hpp"
#include <iostream>

Coordinator game_manager;

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
		game_manager.registerComponent<TransformComponent>();
		game_manager.registerComponent<SpriteComponent>();
		movementSystem = game_manager.registerSystem<MovementSystem>();
		animationSystem = game_manager.registerSystem<AnimationSystem>();
		keyboardSystem = game_manager.registerSystem<KeyboardSystem>();
		Signature signature;

		// include components into systems
		signature.set(game_manager.getComponentType<TransformComponent>());
		signature.set(game_manager.getComponentType<SpriteComponent>());
		game_manager.setSystemSignature<AnimationSystem>(signature);
		signature.reset(game_manager.getComponentType<SpriteComponent>());
		game_manager.setSystemSignature<MovementSystem>(signature);

		// get ID for player
		player = game_manager.createEntity();
		// TODO adapt Sprite component
		SDL_Rect dstR; dstR.w = dstR.h = 64; dstR.x = dstR.y = 50;
		SDL_Texture* t = TextureManager::LoadTexture("assets/player2.png", renderer);
		std::vector<SDL_Rect> animRects = {
			SDL_Rect{ 0, 0, 85, 169 },
			SDL_Rect{ 91, 0, 90, 169 },
			SDL_Rect{ 187, 0, 97, 169 },
			SDL_Rect{ 290, 0, 108, 169 },
			SDL_Rect{ 404, 0, 96, 175 }
		};
		game_manager.addComponent(player, SpriteComponent{ t, animRects, 0, 130, true, SDL_FLIP_NONE });
		game_manager.addComponent(player, TransformComponent{ Vec(50, 50), Vec(0, 0) });
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
	animationSystem->update();
	keyboardSystem->update(ev);
	movementSystem->update(ev);
}

void Game::render() {
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	animationSystem->render(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}