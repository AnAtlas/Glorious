#include "Player.hpp"
#include "EventManager.hpp"
Player::Player(std::shared_ptr<EventManager> eventMan) : Instance(eventMan), eventManager(eventMan), moving(false) {
	
}

void Player::update(sf::Clock* clock) {
	for (auto iterator = components.begin(); iterator != components.end(); iterator++) {
		iterator->second->update(clock);
	}
	std::shared_ptr<C_Drawable> cDraw = std::static_pointer_cast<C_Drawable>(getComponent(Component::Drawable));
	if (!cDraw->isMoving()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (cDraw->getDirection() != DirectionType::Left)
				eventManager->queueEvent(std::shared_ptr<DirectionChangeEvent>(new DirectionChangeEvent(instanceId, DirectionType::Left)));
			eventManager->queueEvent(std::shared_ptr<MovingEvent>(new MovingEvent(instanceId, DirectionType::Left)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (cDraw->getDirection() != DirectionType::Down)
				eventManager->queueEvent(std::shared_ptr<DirectionChangeEvent>(new DirectionChangeEvent(instanceId, DirectionType::Down)));
			eventManager->queueEvent(std::shared_ptr<MovingEvent>(new MovingEvent(instanceId, DirectionType::Down)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (cDraw->getDirection() != DirectionType::Up)
				eventManager->queueEvent(std::shared_ptr<DirectionChangeEvent>(new DirectionChangeEvent(instanceId, DirectionType::Up)));
			eventManager->queueEvent(std::shared_ptr<MovingEvent>(new MovingEvent(instanceId, DirectionType::Up)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (cDraw->getDirection() != DirectionType::Right)
				eventManager->queueEvent(std::shared_ptr<DirectionChangeEvent>(new DirectionChangeEvent(instanceId, DirectionType::Right)));
			eventManager->queueEvent(std::shared_ptr<MovingEvent>(new MovingEvent(instanceId, DirectionType::Right)));
		}
	}
}