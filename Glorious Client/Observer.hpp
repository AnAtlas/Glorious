#pragma once
#include <memory>
#include "EventDefinitions.hpp"

class Observer {
public:
	virtual void notify(std::shared_ptr<Event> event) = 0;
};