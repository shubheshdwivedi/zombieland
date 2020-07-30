#include "include/TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder() {
	assert(instance == nullptr);
	instance = this;	
}

sf::Texture& TextureHolder::getTexture(std::string textureName) {
	auto& texturesMap = instance->texturesMap;
	auto keyValuePair = texturesMap.find(textureName);
	if (keyValuePair != texturesMap.end())
		return keyValuePair->second;	
	auto& texture = texturesMap[textureName];
	texture.loadFromFile(textureName);
	return texture;
}
