#include "game_object.hpp"
#include "texture_manager.hpp"

GameObject::GameObject(const char* img, SDL_Renderer* ren,
	int srcX, int srcY, int srcW, int srcH, int x, int y) {

	renderer = ren;
	srcRect.x = srcX; srcRect.y = srcY; srcRect.w = srcW; srcRect.h = srcH;
	objTexture = TextureManager::LoadTexture(img, ren);
	xpos = x; ypos = y;
}

void GameObject::Update() {
	xpos++; ypos++;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 64;
	destRect.h = 64;
}

void GameObject::Render() {
	if (srcRect.x == 0 && srcRect.y == 0 && srcRect.w == 0 && srcRect.h == 0)
		SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
	else
		SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}