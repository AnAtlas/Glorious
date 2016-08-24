#include "C_Drawable.hpp"
#include "TextureManager.hpp"
#include <SFML/System.hpp>

C_Drawable::C_Drawable(std::string texturePath, int width, int height, int animationLength) : C_Base(Component::Drawable), 
		size(width, height), imageSpeed(0), animationLength(animationLength), moving(false), speed(96), tileX(0), tileY(1) {
	setTexture(*TextureManager::loadTexture(texturePath));
	if (size.x == 0 || size.y == 0) {
		this->size = getTexture()->getSize();
	}
	if (this->animationLength == 0) {
		this->animationLength = getTexture()->getSize().x / size.x;
	}
	setOrigin(0, size.y - 16);
	setPosition(tileX * 32, tileY * 32);
}

void C_Drawable::setEventBindings() {
	eventManager->bindEvent(EntityEvent::DirectionChange, ownerInstance, shared_from_this());
	eventManager->bindEvent(EntityEvent::Moving, ownerInstance, shared_from_this());
}

bool C_Drawable::setAnimation(int animationIndex) {
	if (animationIndex < getTexture()->getSize().y / size.y){
		this->animationIndex = animationIndex;
		return true;
	}
	return false;
}

void C_Drawable::update(sf::Clock* clock) {
	if (moving) {
		switch (direction) {
		case DirectionType::Left:
			setPosition(getPosition().x - speed * clock->getElapsedTime().asSeconds() , getPosition().y);
			if (getPosition().x <= tileX * 32) {
				setPosition(tileX * 32, tileY * 32);
				moving = false;
			}
			break;
		case DirectionType::Up:
			setPosition(getPosition().x, getPosition().y - speed * clock->getElapsedTime().asSeconds());
			if (getPosition().y <= tileY * 32) {
				setPosition(tileX * 32, tileY * 32);
				moving = false;
			}
			break;
		case DirectionType::Down:
			setPosition(getPosition().x, getPosition().y + speed * clock->getElapsedTime().asSeconds());
			if (getPosition().y >= tileY * 32) {
				setPosition(tileX * 32, tileY * 32);
				moving = false;
			}
			break;
		case DirectionType::Right:
			setPosition(getPosition().x + speed * clock->getElapsedTime().asSeconds(), getPosition().y);
			if (getPosition().x >= tileX * 32) {
				setPosition(tileX * 32, tileY * 32);
				moving = false;
			}
			break;
		}
		if (!moving) {
			imageSpeed = 0;
		}
	}
}

bool C_Drawable::isMoving() {
	return moving;
}
DirectionType C_Drawable::getDirection() {
	return direction;
}

void C_Drawable::draw(sf::RenderWindow* window, sf::Clock * clock) {
	imageIndex += imageSpeed * (clock->getElapsedTime().asSeconds());
	if (imageIndex >= animationLength)
		imageIndex = 0;
	this->setTextureRect(sf::IntRect((int)std::floor(imageIndex) * size.x, animationIndex * size.y, size.x, size.y));
	window->draw(*this);
}

void C_Drawable::ReadIn(std::stringstream* stream) {

}

void C_Drawable::notify(std::shared_ptr<Event> event) {
	switch (event->getType()) {
	case EntityEvent::DirectionChange:
		if (!moving) {
			int x, dir = 0;
			event->getEvent() >> x >> dir;
			direction = (DirectionType)dir;
			setAnimation(direction);
		}
		break;
	case EntityEvent::Moving:
		if (!moving) {
			int x, dir = 0;
			event->getEvent() >> x >> dir;
			direction = (DirectionType)dir;
			switch (direction) {
			case DirectionType::Left:
				tileX--;
				break;
			case DirectionType::Up:
				tileY--;
				break;
			case DirectionType::Down:
				tileY++;
				break;
			case DirectionType::Right:
				tileX++;
				break;
			}
			moving = true;
			imageSpeed = speed / 16;
		}
	}
}