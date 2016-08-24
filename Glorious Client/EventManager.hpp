#pragma once
#include <vector>
#include <queue>
#include <functional>
#include "EventDefinitions.hpp"
#include "Observer.hpp"

class EventManager {
private:
	std::queue<std::shared_ptr<Event>> queuedEvents;
	std::map<EntityEvent, std::map<int, std::vector<std::shared_ptr<Observer >>> > boundEvents;
	bool shutdown;
public:
	EventManager() : shutdown(false) {}
	~EventManager() {};

	void queueEvent(std::shared_ptr<Event> event) { queuedEvents.push(event); };
	void bindEvent(EntityEvent eventType, int parentInstance, std::shared_ptr<Observer> observer) {
		boundEvents[eventType][parentInstance].push_back(observer);
	}
	void unbindEvent(EntityEvent eventType, int parentInstance) {
		boundEvents[eventType][parentInstance].clear();
		boundEvents[eventType].erase(parentInstance);
	}

	void stopThread() {
		shutdown = true;
	}

	void eventThread() { 
		while (!shutdown) {
			if (!queuedEvents.empty()) {
				std::shared_ptr<Event> event = queuedEvents.front();
				queuedEvents.pop();
				int parent = 0;
				event->getEvent() >> parent;
				std::vector<std::shared_ptr<Observer>>* observers = &boundEvents[event->getType()][parent];
				for (auto itr = observers->begin(); itr != observers->end(); itr++) {
					itr->get()->notify(event);
				}
			}
			else {
				sf::sleep(sf::milliseconds(25));
			}
		} 
		shutdown = true;
	}
};