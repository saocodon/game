#pragma once

#include "const.hpp"
#include <queue>
#include <assert.h>

class EntityManager {
private:
	std::queue<entity> ID;
	std::array<Signature, MAX_ENTITIES> signatures;
public:
	EntityManager() {
		for (entity e = 0; e < MAX_ENTITIES; e++)
			ID.push(e);
	}
	entity createEntity() {
		assert(!ID.empty() && "Entity count reached maximum");
		entity id = ID.front(); ID.pop();
		return id;
	}
	void destroyEntity(entity e) {
		assert(e < MAX_ENTITIES && "EntityManager::destroyEntity(): out of range");
		signatures[e] = 0;
		ID.push(e);
	}
	void setSignature(entity e, Signature signature) {
		signatures[e] = signature;
	}
	Signature getSignature(entity e) {
		assert(e < MAX_ENTITIES && "EntityManager::getSignature(): out of range");
		return signatures[e];
	}
};