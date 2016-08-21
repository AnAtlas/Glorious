#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace TextureManager {
	extern std::shared_ptr<sf::Texture> loadTexture(std::string texturePath);
	extern void unloadTexture();
	extern void unloadUnusedTextures();
	extern void unloadAllTextures();
};