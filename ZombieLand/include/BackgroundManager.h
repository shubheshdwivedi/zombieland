#pragma once
#include <SFML/Graphics.hpp>
#include "GameConstants.h"
#include "TextureHolder.h"

class BackgroundManager {

	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int QUAD_VERTS = 4;

	int worldHeight = 0;
	int worldWidth = 0;
	int currentVertex = 0;

	sf::VertexArray background;

	sf::Texture backgroundTexture = TextureHolder::getTexture(Constants::BACKGROUND_SHEET_PNG);

	public:
	
		int buildBackGround(sf::IntRect arena);

		void draw(sf::RenderWindow& window);

};
