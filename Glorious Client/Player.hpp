#pragma once
#include "Instance.hpp"
#include "C_Drawable.hpp"

class EventManager;

class Player : public Instance
{
private:
	std::shared_ptr<EventManager> eventManager;
	bool moving;
public:
	Player(std::shared_ptr<EventManager> eventManager);
	void packetBack(sf::Packet* packet) {}
	void update(sf::Clock * clock);
};