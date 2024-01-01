#pragma once

#include "const.hpp"
#include <set>
#include <unordered_map>
#include <memory>

class System {
public:
	std::set<entity> entities;
};

class SystemManager {
private:
	std::unordered_map<const char*, properties> _properties;
	std::unordered_map<const char*, std::shared_ptr<System>> systems;
public:
	template<typename T>
	std::shared_ptr<T> registerSystem() {
		const char* typeName = typeid(T).name();
		assert(systems.find(typeName) == systems.end() && "Registering system more than once");
		auto system = std::make_shared<T>();
		systems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void setProperties(properties p) {
		const char* typeName = typeid(T).name();
		assert(systems.find(typeName) != systems.end() && "System used before registered");
		_properties.insert({ typeName, p });
	}

	void entityDestroyed(entity e) {
		for (auto const& pair : systems) {
			auto const& system = pair.second;
			system->entities.erase(e);
		}
	}

	void entityPropertiesChanged(entity e, properties p) {
		for (auto const& pair : systems) {
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemProperties = _properties[type];
			// checking if entity properties has the same bits turned on as the system
			if ((p & systemProperties) == systemProperties)
				system->entities.insert(e);
			else
				system->entities.erase(e);
		}
	}
};