#include "TextureManager.hpp"


enum GameState {
	GS_LOGIN,
	GS_NORMAL,
	GS_BATTLE
};


int gameState = GS_LOGIN;

int main() {

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
	sf::Sprite sprite;
	std::shared_ptr<sf::Texture> texture;
	texture = TextureManager::loadTexture("pic.png");
	sprite.setTexture(*texture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}