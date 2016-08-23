#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "C_Base.hpp"

class C_Drawable : public C_Base, public sf::Sprite
{
private:
	sf::Vector2u size;
	int textureXPosition, textureYPosition;
	int animationIndex;
	int animationLength;
	float imageIndex;
	float imageSpeed;
public:
	C_Drawable(std::string texturePath, int width = 0, int height = 0, int animationLength = 0);

	bool setAnimation(int animationIndex);

	virtual void draw(sf::RenderWindow * window, sf::Clock* clock);
	void ReadIn(std::stringstream* stream);
};