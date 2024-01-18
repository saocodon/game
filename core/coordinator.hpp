#pragma once

#include "component_manager.hpp"
#include "system_manager.hpp"
#include "entity_manager.hpp"

class Coordinator {
private:
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<SystemManager> systemManager;

public:
	void init() {
		// create unique pointers to each manager
		componentManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		systemManager = std::make_unique<SystemManager>();
	}
	entity createEntity() {
		return entityManager->createEntity();
	}
	void destroyEntity(entity e) {
		entityManager->destroyEntity(e);
		componentManager->entityDestroyed(e);
		systemManager->entityDestroyed(e);
	}
	// component methods
	template <typename T>
	void registerComponent() {
		componentManager->registerComponent<T>();
	}
	template <typename T>
	void addComponent(entity e, T component) {
		componentManager->addComponent(e, component);
		auto signature = entityManager->getSignature(e);
		// set property: componentManager->getComponentType() of type T
		signature.set(componentManager->getComponentType<T>(), true);
		entityManager->setSignature(e, signature);
		// called when add a component
		systemManager->entitySignatureChanged(e, signature);
	}
	template <typename T>
	T& getComponent(entity e) {
		// get all components of e
		return componentManager->getComponent<T>(e);
	}
	template <typename T>
	componentType getComponentType() {
		// get ID for component type T
		return componentManager->getComponentType<T>();
	}
	// system methods
	template <typename T>
	std::shared_ptr<T> registerSystem() {
		return systemManager->registerSystem<T>();
	}
	template <typename T>
	void setSystemSignature(Signature signature) {
		systemManager->setSignature<T>(signature);
	}
};