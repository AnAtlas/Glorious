#include "TextureManager.hpp"


enum GameState {
	GS_LOGIN,
	GS_NORMAL,
	GS_BATTLE
};


int gameState = GS_LOGIN;

void loadTexture() {
	sf::Sprite sprite;
	sprite.setTexture(*TextureManager::loadTexture("pic.png"));
	std::shared_ptr<sf::Texture> tex;
}

int main() {

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
	
	loadTexture();
	TextureManager::unloadUnusedTextures();
	loadTexture();
	
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(sprite);
		window.display();
	}
	return 0;
}