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
	int id;
	int typeId;
	bool persistant;
	std::map<Component, std::shared_ptr<C_Base>> components;
public:
	Instance() { instanceAmount++; this->id = instanceAmount; typeId = -1; persistant = false; }
	int getId() { return id; }
	int getTypeId() { return typeId; }
	void addComponent(std::shared_ptr<C_Base> component) { components[component->getType()] = component; }
	std::shared_ptr<C_Base> getComponent(Component component) { return components.find(component)->second; }
	virtual void packetBack(sf::Packet* packet) = 0;
};