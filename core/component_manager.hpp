#pragma once

#include "component_array.hpp"
#include <memory>

class ComponentManager {
public:
	template<typename T>
	void registerComponent() {
		const char* typeName = typeid(T).name();
		assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once.");
		componentTypes.insert({ typeName, nextComponentType });
		// create a ComponentArray shared pointer & add it to the component arrays map
		componentArrays.insert({ typeName, std::make_shared < ComponentArray<T>>() });
		++nextComponentType;
	}
	template<typename T>
	componentType getComponentType() {
		const char* typeName = typeid(T).name();
		assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use");
		return componentTypes[typeName];
	}
	template<typename T>
	void addComponent(entity e, T component) {
		getComponentArray<T>()->insertData(e, component);
	}
	template<typename T>
	void removeComponent(entity e) {
		getComponentArray<T>()->removeData(e);
	}
	template<typename T>
	T& getComponent(entity e) {
		return getComponentArray<T>()->getData(e);
	}
	void entityDestroyed(entity e) {
		for (auto const& pair : componentArrays) {
			auto const& component = pair.second;
			component->entityDestroyed(e);
		}
	}
private:
	std::unordered_map<const char*, componentType> componentTypes;
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays;
	componentType nextComponentType; // counter (setting IDs for components)
	template <typename T>
	std::shared_ptr<ComponentArray<T>> getComponentArray() {
		const char* typeName = typeid(T).name();
		assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use");
		// return pointer of type IComponentArray
		return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
	}
};