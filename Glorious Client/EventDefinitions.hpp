#pragma once
#include <string>
#include <map>
#include <SFML/Network.hpp>

#include "Directions.hpp"

enum class EntityEvent {
	FriendLoggedIn, FriendLoggedOut,
	Colliding_X, Colliding_Y, EnteredRoom, LeftRoom,
	DirectionChange,
	Moving,
	DepthChange, Became_Idle
};

class Event {
protected:
	EntityEvent type;
	sf::Packet parameters;
public:
	EntityEvent getType() { return type; }
	sf::Packet getEvent() { return parameters; }
};

class FriendLoggedInEvent : public Event {

public:
	FriendLoggedInEvent(int instanceId, std::string name) {
		type = EntityEvent::FriendLoggedIn;
		parameters << name;
	}

};

class DirectionChangeEvent : public Event {
public:
	DirectionChangeEvent(int instanceId, DirectionType direction) {
		type = EntityEvent::DirectionChange;
		parameters << instanceId << direction;
	}
};

class MovingEvent : public Event {
public:
	MovingEvent(int instanceId, DirectionType direction) {
		type = EntityEvent::Moving;
		parameters << instanceId << direction;
	}
};