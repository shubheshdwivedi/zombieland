#pragma once

#include <SFML/Graphics.hpp>
#include <map>

// needs to be synchronized, singleton
class TextureHolder {

	std::map<std::string, sf::Texture> texturesMap;
	static TextureHolder* instance;

	public:

		TextureHolder();
		static sf::Texture& getTexture(std::string textureName);
};
