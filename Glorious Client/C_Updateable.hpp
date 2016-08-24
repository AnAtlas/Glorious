#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "C_Base.hpp"

class C_Updateable : public C_Base
{
private:
public:
	C_Updateable();

	void(*update)(sf::Clock* clock);
	void ReadIn(std::stringstream* stream);
};
