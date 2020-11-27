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

	eagleTex.loadFromFile("rsc/graphics.png");
	eagle.setTexture(eagleTex);
	eagle.setPosition((float)(50), (float)(50));
	eagle.setTextureRect(sf::IntRect(896, 64, 32, 32));
	map.push_back(eagle);

}
void Game::run() {
	int a = 0, b = 0;
	menu.start(416, 416);
	sf::RenderWindow window(sf::VideoMode(416, 416), "TANK");
	sf::Music music;
	if (!music.openFromFile("rsc/game_start.wav"))
		std::cout<< "Music Error\n"; // error
	music.play();
	window.setFramerateLimit(60);
	// Start menu
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
					if (menu.getItemIndex() == 0)
						play(&window);
					else
						window.close();
				}
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(eagle);
		//menu.draw(window);
		window.display();
	}
}
void Game::play(sf::RenderWindow* window) {
	initStage();
	while (window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up)
					menu.moveUp();
				if (event.key.code == sf::Keyboard::Down)
					menu.moveDown();
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window->close();
		}
		window->clear();
		draw(window);
		window->display();
	}
}

void Game::draw(sf::RenderWindow* window) {
	for (auto i : map){
		window->draw(i);
	}
}
void Game::initStage() {

	std::ifstream file("stages/stage1.txt");
	std::string line;
	int col = 0, row = 0;
	while (std::getline(file, line)) {
		for (auto x : line) {
			switch (x) {
			case 'e': break;
			case 'b': brick.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(brick); break;
			case 's': stone.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(stone); break;
			default:
				break;
			}
			col++;
		}
		row++;
		col = 0;
	}

}