#pragma once

#include "SDL_image.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren) {
		SDL_Surface* sf = IMG_Load(filename);
		SDL_Texture* t = SDL_CreateTextureFromSurface(ren, sf);
		SDL_FreeSurface(sf);
		return t;
	}
};