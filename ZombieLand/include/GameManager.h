#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GameConstants.h"
#include "BackgroundManager.h"
#include "Zombie.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "SpawnManager.h"
#include "HUDManager.h"
#include <fstream>
#include "SoundManager.h";

class GameManager {

	Constants::State state;

	TextureHolder textureHolder;
	
	sf::Vector2f resolution;
	sf::VideoMode vm;

	sf::Clock clock;
	sf::Time gameTimeTotal;

	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mouseScreenPosition;

	Player player;

	sf::IntRect arena;

	sf::View mainView;

	sf::Event event;

	sf::Font font;

	BackgroundManager backgroundManager;

	HUDManager hudManager;

	int score = 0;
	int hiScore = 0;

	int numOfZombies = 10;
	int numOfZombiesAlive = 10;
	Zombie* zombies = NULL;

	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	sf::Time lastPressed;

	sf::Sprite spriteCrosshair;
	sf::Texture textureCrosshair = TextureHolder::getTexture(Constants::CROSSHAIR_PNG);

	SpawnManager healthPickup =  SpawnManager(1);
	SpawnManager ammoPickup = SpawnManager(2);

	SoundManager hit = SoundManager(Constants::SOUND_HIT);
	SoundManager shoot = SoundManager(Constants::SOUND_SHOOT);
	SoundManager reload = SoundManager(Constants::SOUND_RELOAD);
	SoundManager reloadFailed = SoundManager(Constants::SOUND_RELOAD_FAILED);
	SoundManager pickup = SoundManager(Constants::SOUND_PICKUP);
	SoundManager powerup = SoundManager(Constants::SOUND_POWERUP);
	SoundManager splat = SoundManager(Constants::SOUND_SPLAT);

	int wave = 0;

	public:
		
		GameManager();

		void handleInput(sf::RenderWindow& window);

		Zombie* createHorde(int numOfZombies, sf::IntRect arena);

		void Play();	

};
