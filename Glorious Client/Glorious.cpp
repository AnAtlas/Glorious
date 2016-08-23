
#include "TextureManager.hpp"
#include "Player.hpp"
#include "C_Drawable.hpp"

enum GameState {
	GS_LOGIN,
	GS_NORMAL,
	GS_BATTLE
};


int gameState = GS_LOGIN;
sf::Clock fpsClock;
sf::Text fpsText;
sf::Font fpsFont;
float fps;
void loadTexture() {
}

int main() {
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
	window.setFramerateLimit(60);
	Player * player = new Player();
	std::shared_ptr<C_Drawable> drawable(new C_Drawable("pic.png", 16, 24));
	player->addComponent(drawable);
	fpsFont.loadFromFile("Vegur-Regular.otf");
	fpsText.setFont(fpsFont);
	fpsText.setPosition(10, 50);
	while (window.isOpen()) {
		fpsClock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		std::static_pointer_cast<C_Drawable>(player->getComponent(Component::Drawable))->draw(&window,&fpsClock);
		fpsText.setString(std::to_string(1 /fpsClock.getElapsedTime().asSeconds()));
		window.draw(fpsText);
		window.display();
	}
	return 0;
}