#pragma once
#include <SFML/Graphics.hpp>
#include "GameConstants.h"

class BackgroundManager {

	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int QUAD_VERTS = 4;

	int worldHeight = 0;
	int worldWidth = 0;
	int currentVertex = 0;

	sf::VertexArray background;

	sf::Texture backgroundTexture;

	public:

		BackgroundManager();
	
		int buildBackGround(sf::IntRect arena);

		void draw(sf::RenderWindow& window);

};
