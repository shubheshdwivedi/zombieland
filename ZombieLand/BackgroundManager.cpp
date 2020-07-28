#include "BackgroundManager.h"

BackgroundManager::BackgroundManager() {
	backgroundTexture.loadFromFile(Constants::BACKGROUND_SHEET_PNG);
}

int BackgroundManager::buildBackGround(sf::IntRect arenaSize) {

	background.setPrimitiveType(sf::Quads);
	background.resize(worldHeight * worldWidth * QUAD_VERTS);

	// TODO : NEEDS REFACTOR
	worldHeight = arenaSize.height / TILE_SIZE;
	worldWidth = arenaSize.width / TILE_SIZE;
	background.resize(worldHeight * worldWidth * QUAD_VERTS);

	int w = 0, h = 0;
	for (w = 0; w < worldWidth; w++) {
		for (h = 0; h < worldHeight; h++) {
			background[currentVertex + 0].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			background[currentVertex + 1].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			background[currentVertex + 2].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			background[currentVertex + 3].position = sf::Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {			
				background[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
				background[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
				background[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
				background[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
			}
			else {
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				background[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + verticalOffset);
				background[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, 0 + verticalOffset);
				background[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				background[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE + verticalOffset);
			}

			currentVertex += QUAD_VERTS;
		}

	}
	return TILE_SIZE;
}

void BackgroundManager::draw(sf::RenderWindow& window) {
	window.draw(background, &backgroundTexture);
}
