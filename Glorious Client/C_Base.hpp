#pragma once
#include <sstream>
#include "ComponentTypes.hpp"
#include "EventManager.hpp"
#include "Observer.hpp"

class C_Base : public Observer, public std::enable_shared_from_this <Observer> {
public:
	C_Base(const Component type) : type(type), ownerInstance(0), eventManager(nullptr) {}
	virtual ~C_Base() {}

	Component getType() { return type; }

	friend std::stringstream& operator >> (
		std::stringstream& stream, C_Base& b) {
		b.ReadIn(&stream);
		return stream;
	}

	void setOwner(int instanceId) {
		ownerInstance = instanceId;
	}

	void setEventManager(std::shared_ptr<EventManager> eventManager) {
		this->eventManager = eventManager;
	}
	virtual void ReadIn(std::stringstream* stream) = 0;
	virtual void setEventBindings() = 0;
	virtual void update(sf::Clock* clock) = 0;

protected:
	Component type;
	int ownerInstance;
	std::shared_ptr<EventManager> eventManager;
};