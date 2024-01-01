#pragma once

#include "const.hpp"
#include <queue>
#include <assert.h>

class EntityManager {
private:
	std::queue<entity> ID;
	properties _properties[MAX_ENTITIES];
public:
	EntityManager() {
		for (entity e = 0; e < MAX_ENTITIES; e++)
			ID.push(e);
		memset(_properties, 0, sizeof(_properties));
	}
	entity createEntity() {
		assert(!ID.empty() && "Entity count reached maximum");
		entity id = ID.front(); ID.pop();
		return id;
	}
	void destroyEntity(entity e) {
		assert(e < MAX_ENTITIES && "EntityManager::destroyEntity(): out of range");
		_properties[e] = 0;
		ID.push(e);
	}
	void setProperties(entity e, properties p) {
		_properties[e] = p;
	}
	properties getProperties(entity e) {
		assert(e < MAX_ENTITIES && "EntityManager::getProperties(): out of range");
		return _properties[e];
	}
};