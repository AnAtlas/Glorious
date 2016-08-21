#pragma once
#include <SFML/Network.hpp>
#include <memory>

#include "ComponentTypes.hpp"
static int instanceAmount;

class C_Base;

class Instance : public std::enable_shared_from_this <Instance>
{
protected:
	int id;
	int typeId;
	bool persistant;
	std::map<ComponentType, std::shared_ptr<C_Base>> components;
public:
	Instance() { instanceAmount++; this->id = instanceAmount; typeId = -1; persistant = false; }
	int getId() { return id; }
	int getTypeId() { return typeId; }
};