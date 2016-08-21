#include "TextureManager.hpp"

namespace TextureManager {
	std::map<std::string, std::shared_ptr<sf::Texture>> loadedTextures;

	std::shared_ptr<sf::Texture> loadTexture(std::string texturePath) {
		//look through map of loaded textures to see if this texture is already loaded
		//If so, return a pointer to that texture
		auto texIterator = loadedTextures.find(texturePath);
		if (texIterator != loadedTextures.end()) {
			return (*texIterator).second;
		}

		std::shared_ptr<sf::Texture> newTexture(new sf::Texture());
		if (!newTexture->loadFromFile(texturePath)) {
			//ERROR Write stuff here.
		}
		newTexture->setSmooth(false);

		//Add new texture into loaded textures;
		loadedTextures.insert(std::make_pair(texturePath, newTexture));
		return newTexture;
	}
}