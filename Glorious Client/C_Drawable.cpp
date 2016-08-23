#include "C_Drawable.hpp"
#include "TextureManager.hpp"
#include <SFML/System.hpp>

C_Drawable::C_Drawable(std::string texturePath, int width, int height, int animationLength) : C_Base(Component::Drawable), size(width, height), imageSpeed(1), animationLength(animationLength) {
	setTexture(*TextureManager::loadTexture(texturePath));
	if (size.x == 0 || size.y == 0) {
		this->size = getTexture()->getSize();
	}
	if (this->animationLength == 0) {
		this->animationLength = getTexture()->getSize().x / size.x;
	}
}

bool C_Drawable::setAnimation(int animationIndex) {
	if (animationIndex < getTexture()->getSize().y / size.y){
		this->animationIndex = animationIndex;
		return true;
	}
	return false;
}

void C_Drawable::draw(sf::RenderWindow* window, sf::Clock * clock) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		setAnimation(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		setAnimation(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		setAnimation(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		setAnimation(3);
	}
	imageIndex += imageSpeed * (clock->getElapsedTime().asSeconds());
	if (imageIndex >= animationLength)
		imageIndex = 0;
	this->setTextureRect(sf::IntRect(std::floor(imageIndex) * size.x, animationIndex * size.y, size.x, size.y));
	window->draw(*this);
}

void C_Drawable::ReadIn(std::stringstream* stream) {

}