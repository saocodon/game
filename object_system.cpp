#include "object_system.hpp"
#include "texture_manager.hpp"

extern Coordinator game_manager;

void ObjectSystem::init(const char* img, SDL_Renderer* ren, int x, int y) {
	
	renderer = ren;
	for (auto const& e : entities) {
		auto sprites = game_manager.getComponent<Sprites>(e);
		sprites.texture = TextureManager::LoadTexture(img, renderer);
		SDL_Rect d; d.w = d.h = 64; d.x = x; d.y = y;
		sprites.dst = d;
	}
}

void ObjectSystem::update() {
	for (auto const& e : entities) {
		// TODO: returned nullptr
		// does size(entities) = 0?
		auto& transform = game_manager.getComponent<Transform>(e);
		auto& sprites = game_manager.getComponent<Sprites>(e);
		transform.x++; transform.y++;
		sprites.dst.x++; sprites.dst.y++;
	}
}