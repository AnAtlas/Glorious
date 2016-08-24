#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Observer.hpp"
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
	DirectionType direction;
	bool moving;
	float speed;
	int tileX, tileY;
	int counter;
public:
	C_Drawable(std::string texturePath, int width = 0, int height = 0, int animationLength = 0);
	~C_Drawable() {}
	bool setAnimation(int animationIndex);
	DirectionType getDirection();
	bool isMoving();
	virtual void draw(sf::RenderWindow * window, sf::Clock* clock);
	void ReadIn(std::stringstream* stream);
	void setEventBindings();
	void notify(std::shared_ptr<Event> event);
	void update(sf::Clock* clock);
};