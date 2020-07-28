#include "TextureHolder.h"

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder* TextureHolder::getInstance() {
	if (instance == nullptr) {
		instance = new TextureHolder;
	}
	return instance;
}

sf::Texture& TextureHolder::getTexture(std::string textureName) {
	auto keyValuePair = texturesMap.find(textureName);
	if (keyValuePair != texturesMap.end())
		return keyValuePair->second;	
	auto& texture = texturesMap[textureName];
	texture.loadFromFile(textureName);
	return texture;
}
