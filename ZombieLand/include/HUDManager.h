#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <sstream>
#include "GameConstants.h"

class HUDManager {
	sf::View hudView;

	sf::Sprite spriteGameOver;
	sf::Sprite spriteAmmoIcon;
	sf::Text pausedText;
	sf::Text gameOverText;
	sf::Text levelUpText;
	sf::Text ammoText;
	sf::Text scoreText;
	sf::Text hiScoreText;
	sf::Text zombiesRemainingText;
	sf::Text gameTitle;

	sf::Text waveNumberText;
	sf::RectangleShape healthBar;

	int framesSinceLastHUDUpdate = 0;

	int fpsMeasurementFrameInterval = 1000;

	int windowWidth = 0;
	int windowHeight = 0;

	void setupGameOver(sf::Vector2f resolution);
	void setupGameOverText();
	void setupAmmoText();
	void setupAmmoIcon();
	void setupHealthBar();
	void setupLevelUpText();
	void setupPausedText();
	void setupHiScoreText(int hiScore);
	void setupWaveText();
	void setupZombieRemainingText();
	void setupScoreText();
	void setupGameTitle();

	sf::Font font;
	public: 

		HUDManager();

		void init(sf::Vector2f resolution, int hiScore);

		void hudUpdate(float playerHealth, int bulletsInClip, int bulletsSpare, int score, int hiScore,
			int numOfZombiesAlive, int wave);

		void drawHUD(sf::RenderWindow& window, Constants::State state);
};
