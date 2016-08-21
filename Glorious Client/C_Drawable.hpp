#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "C_Base.hpp"

class C_Drawable : public C_Base, public sf::Sprite
{
private:
	int width, height;
	int textureXPosition, textureYPosition;
	int animationIndex;
	float imageIndex;
	float imageSpeed;
public:
	C_Drawable(std::string texturePath);
	C_Drawable(std::string texturePath, int width, int height);

	virtual void draw(std::shared_ptr<sf::RenderWindow> window, float deltaTime);
};