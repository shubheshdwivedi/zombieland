#include "include/GameManager.h"
#include <sstream>

GameManager::GameManager() {

	state = Constants::State::GAME_OVER;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	vm = sf::VideoMode(resolution.x, resolution.y);
	std::ifstream inputFile(Constants::HISCORE_FILE);
	if (inputFile.is_open()) {
		inputFile >> hiScore;
		inputFile.close();
	}
	hudManager.init(resolution, hiScore);
	mainView = sf::View(sf::FloatRect(0, 0, resolution.x, resolution.y));
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);
}

Zombie* GameManager::createHorde(int numOfZombies, sf::IntRect arena) {
		
	Zombie* zombies = new Zombie[numOfZombies];

	int minY = arena.top + 20; int maxY = arena.height - 20;
	int minX = arena.left + 20; int maxX = arena.width - 20;

	for (int i = 0; i < numOfZombies; i++) {
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x = 0, y = 0;

		switch (side) {
			case 0:
				x = minX;
				y = (rand() % maxY) + minY;
				break;

			case 1:
				x = maxX;
				y = (rand() % maxY) + minY;
				break;

			case 2:
				x = (rand() % maxX) + minX;
				y = minY;
				break;

			case 3:
				x = (rand() % maxX) + minX;
				y = maxY;
				break;
		}
		srand((int)time(0) * i * 2);
		int typeOfZombie = (rand() % 3);

		zombies[i].spawn(x, y, typeOfZombie, i);
	}

	return zombies;
}

void GameManager::handleInput(sf::RenderWindow& window) {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Return &&
				state == Constants::State::PLAYING) {
				state = Constants::State::PAUSED;
			}
			else if (event.key.code == sf::Keyboard::Return &&
				state == Constants::State::PAUSED) {
				state = Constants::State::PLAYING;
				clock.restart();
			}
			else if (event.key.code == sf::Keyboard::Return &&
				state == Constants::State::GAME_OVER) {

				state = Constants::State::LEVELING_UP;
				wave = 0;
				score = 0;

				currentBullet = 0;
				bulletsSpare = 24;
				bulletsInClip = 6;
				clipSize = 6;
				fireRate = 1;
				player.resetPlayerStats();
			}

			if (state == Constants::State::PLAYING) {
				if (event.key.code == sf::Keyboard::R) {

					if (bulletsSpare >= clipSize) {
						bulletsInClip = clipSize;
						bulletsSpare -= clipSize;
						reload.play();
					}
					else if (bulletsSpare > 0) {
						bulletsInClip = bulletsSpare;
						bulletsSpare = 0;
						reloadFailed.play();
					}
				}
			}

		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
		window.close();

	if (state == Constants::State::PLAYING) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
			player.moveUp();
		else 
			player.stopUp();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
			player.moveDown();
		else 
			player.stopDown();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
			player.moveLeft();
		else 
			player.stopLeft();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player.moveRight();
		else 
			player.stopRight();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if ((gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds()) > 1000 / fireRate
				&& bulletsInClip > 0) {
				bullets[currentBullet].shoot(
					player.getCenter().x, player.getCenter().y,
					mouseWorldPosition.x, mouseWorldPosition.y);

				currentBullet++;
				if (currentBullet > 99)
					currentBullet = 0;
				lastPressed = gameTimeTotal;

				shoot.play();

				bulletsInClip--;
			}
		}

	}

	if (state == Constants::State::LEVELING_UP) {
		if (event.key.code == sf::Keyboard::Num1) {
			fireRate++;
			state = Constants::State::PLAYING;
		}

		if (event.key.code == sf::Keyboard::Num2) {
			clipSize += clipSize;
			state = Constants::State::PLAYING;
		}

		if (event.key.code == sf::Keyboard::Num3) {
			player.upgradeHealth();
			state = Constants::State::PLAYING;
		}

		if (event.key.code == sf::Keyboard::Num4) {
			player.upgradeSpeed();
			state = Constants::State::PLAYING;
		}

		if (event.key.code == sf::Keyboard::Num5) {
			healthPickup.upgrade();
			state = Constants::State::PLAYING;
		}

		if (event.key.code == sf::Keyboard::Num6) {
			ammoPickup.upgrade();
			state = Constants::State::PLAYING;
		}

		if (state == Constants::State::PLAYING) {
			wave++;
			arena.width = 570 *  wave;
			arena.height = 570 * wave;
			arena.left = 0;
			arena.top = 0;

			int tileSize = 50;
			backgroundManager.buildBackGround(arena);
			player.spawn(arena, resolution, tileSize);

			numOfZombies = 5 * wave;

			delete[] zombies;
			zombies = createHorde(numOfZombies, arena);
			numOfZombiesAlive = numOfZombies;

			healthPickup.setArena(arena);
			ammoPickup.setArena(arena);

			powerup.play();

			clock.restart();
		}
	}
}

void GameManager::Play() {

	sf::RenderWindow window(vm, Constants::GAME_TITLE, sf::Style::Fullscreen);

	window.setMouseCursorVisible(false);
	
	while (window.isOpen()) {

		handleInput(window);

		if (state == Constants::State::PLAYING) {
			sf::Time dt = clock.restart();
			gameTimeTotal += dt;
			float dtAsSeconds = dt.asSeconds();

			mouseScreenPosition = sf::Mouse::getPosition();

			mouseWorldPosition = window.mapPixelToCoords(
				sf::Mouse::getPosition(), mainView);

			spriteCrosshair.setPosition(mouseWorldPosition);

			player.update(dtAsSeconds, sf::Mouse::getPosition());

			sf::Vector2f playerPosition(player.getCenter());

			mainView.setCenter(player.getCenter());

			for (int i = 0; i < numOfZombies; i++)
				if (zombies[i].isAlive())
					zombies[i].update(dt.asSeconds(), playerPosition);

			for (int i = 0; i < 100; i++)
				if (bullets[i].isInFlight())
					bullets[i].update(dtAsSeconds);
			
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < numOfZombies; j++) {
					if (bullets[i].isInFlight() &&
						zombies[j].isAlive()) {
						if (bullets[i].getPosition().intersects(zombies[j].getPosition())) {
							bullets[i].stop();

							if (zombies[j].hit()) {
								score += 10;
								if (score >= hiScore) 
									hiScore = score;

								numOfZombiesAlive--;

								if (numOfZombiesAlive == 0) {
									state = Constants::State::LEVELING_UP;
								}
							}
							splat.play();
						}
					}

				}
			} 

			for (int i = 0; i < numOfZombies; i++) {
				if (player.getPosition().intersects(zombies[i].getPosition()) && zombies[i].isAlive()) {

					if (player.hit(gameTimeTotal)) {
						hit.play();
					}

					if (player.getHealth() <= 0) {
						std::ofstream outputFile(Constants::HISCORE_FILE);
						outputFile << hiScore;
						outputFile.close();
						state = Constants::State::GAME_OVER;

					}
				}
			} 

			if (player.getPosition().intersects(healthPickup.getPosition()) && healthPickup.isSpawned()) {
				player.increaseHealthLevel(healthPickup.gotIt());
				pickup.play();
			}


			if (player.getPosition().intersects(ammoPickup.getPosition()) && ammoPickup.isSpawned()) {
				bulletsSpare += ammoPickup.gotIt();
				pickup.play();
			}

			hudManager.hudUpdate(player.getHealth() * 3, bulletsInClip, bulletsSpare, score,
				hiScore, numOfZombiesAlive, wave);
		} 

		if (state == Constants::State::PLAYING) {
			window.clear();

			window.setView(mainView);

			backgroundManager.draw(window);

			for (int i = 0; i < numOfZombies; i++)
				window.draw(zombies[i].getSprite());

			for (int i = 0; i < 100; i++)
				if (bullets[i].isInFlight())
					window.draw(bullets[i].getShape());

			window.draw(player.getSprite());

			if (ammoPickup.isSpawned())
				window.draw(ammoPickup.getSprite());

			if (healthPickup.isSpawned())
				window.draw(healthPickup.getSprite());

			window.draw(spriteCrosshair);
			
		}

		hudManager.drawHUD(window, state);

		window.display();

	}
	
}