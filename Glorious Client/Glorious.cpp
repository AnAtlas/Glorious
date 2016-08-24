
#include "TextureManager.hpp"
#include "Player.hpp"
#include "C_Drawable.hpp"
#include <thread>

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

int main() {
	sf::RenderWindow window(sf::VideoMode(320, 480), "SFML Works");
	window.setFramerateLimit(144);
	std::shared_ptr<EventManager> eventManager(new EventManager());
	std::thread eventThread(&EventManager::eventThread, eventManager);

	Player * player = new Player(eventManager);
	std::shared_ptr<C_Drawable> drawable(new C_Drawable("pic.png", 48, 48));
	player->addComponent(drawable);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		player->update(&fpsClock);
		std::static_pointer_cast<C_Drawable>(player->getComponent(Component::Drawable))->draw(&window,&fpsClock);
		fpsClock.restart();
		window.display();
	}
	eventManager->stopThread();
	eventThread.detach();
	TextureManager::unloadAllTextures();
	sf::sleep(sf::seconds(0.5f));
	return 0;
}