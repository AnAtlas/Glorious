
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
sf::Clock updateClock;
Player* player;
float fps;
void renderFunction(std::shared_ptr<sf::RenderWindow> window);

int main() {
	std::shared_ptr<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(320, 480), "SFML Works"));
	//window->setVerticalSyncEnabled(true);
	window->setActive(false);

	std::shared_ptr<EventManager> eventManager(new EventManager());
	std::thread eventThread(&EventManager::eventThread, eventManager);

	player = new Player(eventManager);
	player->addComponent(std::shared_ptr<C_Drawable>(new C_Drawable("pic.png", 48, 48)));

	std::thread renderThread(&renderFunction, window);

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		player->update(&updateClock);
		updateClock.restart();
		sf::sleep(sf::seconds(0.001));
	}
	eventManager->stopThread();
	eventThread.join();
	renderThread.join();
	TextureManager::unloadAllTextures();
	sf::sleep(sf::seconds(0.5f));
	return 0;
}

void renderFunction(std::shared_ptr<sf::RenderWindow> window)
{
	sf::Text fpsText;
	sf::Font fpsFont;
	if (fpsFont.loadFromFile("Vegur-Regular.otf"))
		fpsText.setFont(fpsFont);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(50, 50);
	while (window->isOpen())
	{
		window->clear();
		std::static_pointer_cast<C_Drawable>(player->getComponent(Component::Drawable))->draw(window.get(), &fpsClock);
		window->draw(fpsText);
		window->display();
		fpsText.setString(std::to_string(1 / fpsClock.getElapsedTime().asSeconds()));
		fpsClock.restart();
		sf::sleep(sf::seconds(0.001f));
	}
}