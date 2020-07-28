#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GameConstants.h"
#include "BackgroundManager.h"

class GameManager {

	enum class State{
		PAUSED, GAME_OVER, LEVELING_UP, PLAYING
	};

	State state;
	
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

	BackgroundManager backgroundManager;

	public:
		
		GameManager();

		void handleInput(sf::RenderWindow& window);

		void Play();

		

};
