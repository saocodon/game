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
	std::unordered_map<const char*, Signature> signatures;
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
	void setSignature(Signature signature) {
		const char* typeName = typeid(T).name();
		assert(systems.find(typeName) != systems.end() && "System used before registered");
		signatures.insert({ typeName, signature });
	}

	void entityDestroyed(entity e) {
		for (auto const& pair : systems) {
			auto const& system = pair.second;
			system->entities.erase(e);
		}
	}

	void entitySignatureChanged(entity e, Signature signature) {
		for (auto const& pair : systems) {
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = signatures[type];
			// checking if entity signature has the same bits turned on as the system
			if ((signature & systemSignature) == systemSignature)
				system->entities.insert(e);
			else
				system->entities.erase(e);
		}
	}
};