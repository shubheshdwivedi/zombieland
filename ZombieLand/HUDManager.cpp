#include "include/HUDManager.h"

HUDManager::HUDManager() {
	font.loadFromFile(Constants::FONT_PATH);
}


void HUDManager::setupGameOver(sf::Vector2f resolution) {
	spriteGameOver.setTexture(TextureHolder::getTexture(Constants::BACKGROUND_PNG));
	spriteGameOver.setPosition(0, 0);

		spriteGameOver.setScale(
			resolution.x / spriteGameOver.getLocalBounds().width,
			resolution.y / spriteGameOver.getLocalBounds().height);
}

void HUDManager::setupAmmoIcon() {
	spriteAmmoIcon.setTexture(TextureHolder::getTexture(Constants::AMMO_ICON_PNG));
	spriteAmmoIcon.setPosition(hudView.getSize().x - 200, 0);
}


void HUDManager::setupPausedText() {
	pausedText.setFont(font);
	pausedText.setCharacterSize(65);
	pausedText.setString("Press Enter to continue");
	pausedText.setFillColor(sf::Color::White);
	sf::FloatRect textRect = pausedText.getGlobalBounds();
	pausedText.setPosition(hudView.getCenter().x - textRect.width / 2.0f, 
		hudView.getCenter().y - textRect.height / 2.0f);
}

void HUDManager::setupGameTitle() {
	gameTitle.setFont(font);
	gameTitle.setCharacterSize(125);
	gameTitle.setFillColor(sf::Color::White);
	gameTitle.setString("Zombieland");
	sf::FloatRect textRect = gameTitle.getLocalBounds();
	gameTitle.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	gameTitle.setPosition(hudView.getSize().x / 2.0f, hudView.getSize().y / 2.0f);

}

void HUDManager::setupGameOverText() {
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(45);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString("Press Enter to play");
	sf::FloatRect textRect = gameOverText.getLocalBounds();
	gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	gameOverText.setPosition(hudView.getSize().x / 2.0f, hudView.getSize().y / 2.0f + 150);
}

void HUDManager::setupLevelUpText() {
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(40);
	levelUpText.setFillColor(sf::Color::White);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"Choose a powerup \n\n" <<
		"1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());
}

void HUDManager::setupAmmoText() {
	ammoText.setFont(font);
	ammoText.setCharacterSize(45);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setPosition(hudView.getSize().x -150 , 0);
}

void HUDManager::setupScoreText() {
	scoreText.setFont(font);
	scoreText.setCharacterSize(45);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(20, 0);
}

void HUDManager::setupHiScoreText(int hiScore) {
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(45);
	hiScoreText.setFillColor(sf::Color::White);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());
	sf::FloatRect textRect = hiScoreText.getLocalBounds();
	hiScoreText.setPosition(hudView.getSize().x - textRect.width - 20,
		hudView.getSize().y - textRect.height -20);
}

void HUDManager::setupWaveText() {
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(45);
	waveNumberText.setFillColor(sf::Color::White);
	waveNumberText.setString("Wave: 0");
	sf::FloatRect textRect = waveNumberText.getLocalBounds();
	waveNumberText.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	waveNumberText.setPosition(hudView.getSize().x / 2.0f, 0);
}

void HUDManager::setupZombieRemainingText() {
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(sf::Color::White);
	sf::FloatRect textRect = hiScoreText.getLocalBounds();
	zombiesRemainingText.setPosition( hudView.getCenter().x - textRect.width / 2.0f,
		hudView.getSize().y - textRect.height- 20 );
	zombiesRemainingText.setString("Zombies: 0");

}

void HUDManager::setupHealthBar() {
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setPosition(20, 
		hudView.getSize().y - 80);
}

void HUDManager::init(sf::Vector2f resolution, int hiScore) {
	hudView = sf::View(sf::FloatRect(0, 0, resolution.x, resolution.y));
	setupGameOver(resolution);
	setupGameOverText();
	setupAmmoText();
	setupAmmoIcon();
	setupHealthBar();
	setupLevelUpText();
	setupPausedText();
	setupHiScoreText(hiScore);
	setupWaveText();
	setupZombieRemainingText();
	setupScoreText();
	setupGameTitle();
}

void HUDManager::hudUpdate(float playerHealth, int bulletsInClip, int bulletsSpare, int score, int hiScore,
	int numOfZombiesAlive, int wave) {
	healthBar.setSize(sf::Vector2f(playerHealth, 70));

	framesSinceLastHUDUpdate++;
	if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
	{

		std::stringstream ssAmmo;
		std::stringstream ssScore;
		std::stringstream ssHiScore;
		std::stringstream ssWave;
		std::stringstream ssZombiesAlive;

		ssAmmo << bulletsInClip << "/" << bulletsSpare;
		ammoText.setString(ssAmmo.str());

		ssScore << "Score:" << score;
		scoreText.setString(ssScore.str());

		ssHiScore << "Hi Score:" << hiScore;
		hiScoreText.setString(ssHiScore.str());

		ssWave << "Wave:" << wave;
		waveNumberText.setString(ssWave.str());

		ssZombiesAlive << "Zombies:" << numOfZombiesAlive;
		zombiesRemainingText.setString(ssZombiesAlive.str());

		framesSinceLastHUDUpdate = 0;
	}

}

void HUDManager::drawHUD(sf::RenderWindow& window, Constants::State state) {

	window.setView(hudView);

	if (state == Constants::State::PLAYING) {
		window.draw(spriteAmmoIcon);
		window.draw(ammoText);
		window.draw(scoreText);
		window.draw(hiScoreText);
		window.draw(healthBar);
		window.draw(waveNumberText);
		window.draw(zombiesRemainingText);
	}

	if (state == Constants::State::LEVELING_UP) {
		window.draw(spriteGameOver);
		window.draw(levelUpText);
	}

	if (state == Constants::State::PAUSED) {
		window.draw(pausedText);
	}

	if (state == Constants::State::GAME_OVER) {
		window.draw(spriteGameOver);
		window.draw(gameTitle);
		window.draw(gameOverText);
		window.draw(scoreText);
	}


}
