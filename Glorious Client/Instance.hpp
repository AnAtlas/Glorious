#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include "ComponentTypes.hpp"
#include "C_Base.hpp"

static int instanceAmount;

class C_Base;

class Instance : public std::enable_shared_from_this <Instance>
{
protected:
	int instanceId;
	int typeId;
	bool persistant;
	std::shared_ptr<EventManager> eventManager;
	std::map<Component, std::shared_ptr<C_Base>> components;
public:
	Instance(std::shared_ptr<EventManager> eventManager) { 
		instanceAmount++; 
		this->instanceId = instanceAmount; 
		this->eventManager = eventManager;
		typeId = -1; 
		persistant = false; 
	}
	int getId() { return instanceId; }
	int getTypeId() { return typeId; }
	virtual void update() {};
	void addComponent(std::shared_ptr<C_Base> component) { components[component->getType()] = component; component->setOwner(instanceId); component->setEventManager(eventManager); component->setEventBindings(); }
	std::shared_ptr<C_Base> getComponent(Component component) { return components.find(component)->second; }
	virtual void packetBack(sf::Packet* packet) = 0;
	
};