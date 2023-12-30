#pragma once

#include "game.hpp"

class GameObject {
public:
	GameObject(const char* img, SDL_Renderer* ren, int srcX, int srcY, int srcW, int srcH, int x, int y);
	~GameObject();

	void Update();
	void Render();
private:
	int xpos, ypos;
	SDL_Texture* objTexture;
	//srcRect is the portion of your source image
	//destRect is the portion on your window that you want to render
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};