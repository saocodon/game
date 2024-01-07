#include "object_system.hpp"
#include "texture_manager.hpp"
#include <set>

extern Coordinator game_manager;

void ObjectSystem::update() {
	for (auto const& e : entities) {
		auto& transform = game_manager.getComponent<Transform>(e);
		transform.x++; transform.y++;
	}
}