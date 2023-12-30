#include "texture_manager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* filename, SDL_Renderer* ren) {
	SDL_Surface* sf = IMG_Load(filename);
	SDL_Texture* t = SDL_CreateTextureFromSurface(ren, sf);
	SDL_FreeSurface(sf);
	return t;
}