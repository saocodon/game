#pragma once

#include "const.hpp"
#include <array>
#include <unordered_map>
#include <assert.h>

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void entityDestroyed(entity e) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
private:
	// just a wrapper of original arrays
	std::array<T, MAX_ENTITIES> componentArray;
	// better than arrays because search time is O(1)
	std::unordered_map<entity, size_t> entityToIndex;
	size_t arraySize;
public:
	void insertData(entity e, T component) {
		assert(entityToIndex.find(e) == entityToIndex.end() && "Component of entity existed");
		size_t newIndex = arraySize;
		entityToIndex[e] = newIndex;
		componentArray[newIndex] = component;
		++arraySize;
	}
	void removeData(entity e) {
		assert(entityToIndex.find(e) != entityToIndex.end() && "Removing non-existent component");
		// copy element at end into the place of the deleted element to maintain density
		size_t indexOfRemovedElement = entityToIndex[e];
		componentArray[indexOfRemovedElement] = componentArray[arraySize - 1];
		// update map
		entityToIndex[arraySize - 1] = indexOfRemovedElement; // TODO?
		entityToIndex.erase(e);
		--arraySize;
	}
	T& getData(entity e) {
		assert(entityToIndex.find(e) != entityToIndex.end() && "Retrieving non-existent component");
		// return entityToIndex[e]-th element of type T of componentArray[]
		return componentArray[entityToIndex[e]];
	}
	// redefining virtual method
	void entityDestroyed(entity e) override {
		if (entityToIndex.find(e) != entityToIndex.end())
			removeData(e);
	}
};