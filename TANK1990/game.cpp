#include "game.hpp"
#include "menu.hpp"

#include <fstream>
#include <iostream>

#include "SFML/Audio/Music.hpp"

Game::Game() {
	brickTex.loadFromFile("rsc/brick.png");
	brick.setTexture(brickTex);
	brick.setTextureRect(sf::IntRect(0, 0, 16, 16));

	stoneTex.loadFromFile("rsc/stone.png");
	stone.setTexture(stoneTex);
	stone.setTextureRect(sf::IntRect(0, 0, 16, 16));

	tankTex.loadFromFile("rsc/tank.png");
	tank.setTexture(tankTex);
	tank.setTextureRect(sf::IntRect(0, 0, 32, 32));

}

void Game::run() {
	menu.start(416,416);
	sf::RenderWindow window(sf::VideoMode(416, 416), "TANK");
	sf::Music music;
	if (!music.openFromFile("rsc/game_start.wav"))
		std::cout<< "Music Error\n"; // error
	music.play();
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up)
					menu.moveUp();
				if (event.key.code == sf::Keyboard::Down)
					menu.moveDown();
				if (event.key.code == sf::Keyboard::Return) {
					if (menu.getItemIndex() == 1)
						window.close();
				}
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		menu.draw(window);

		window.display();
	}

}
void Game::drawStage(sf::RenderWindow* window) {

	std::ifstream file("stages/stage1.txt");
	std::string line;
	int col = 0, row = 0;
	while (std::getline(file, line)) {
		for (auto x : line) {
			switch (x) {
			case 'a': break;
			case 'b': brick.setPosition(0.f + col * 16, 0.f + row * 16);
				window->draw(brick);
				break;
			case 's': stone.setPosition(0.f + col * 16, 0.f + row * 16);
				window->draw(stone); break;
			default:
				break;
			}
			col++;
		}
		row++;
		col = 0;
	}

}