#include "game.hpp"
#include "menu.hpp"

#include <fstream>
#include <iostream>

#include "SFML/Audio/Music.hpp"

Game::Game() : maps(std::make_shared<std::vector<std::vector<char>>>(26, std::vector<char>(26, 'a'))) {
	texture.loadFromFile("rsc/graphics.png");

	brick.setTexture(texture);
	brick.setTextureRect(sf::IntRect(28 * 32, 0, 16, 16));

	stone.setTexture(texture);
	stone.setTextureRect(sf::IntRect(28 * 32, 1 * 16, 16, 16));

	eagle.setTexture(texture);
	eagle.setTextureRect(sf::IntRect(28 * 32, 2 * 32, 32, 32));

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
		menu.draw(window);
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
					player.moveUp();
				if (event.key.code == sf::Keyboard::Down)
					player.moveDown();
				if (event.key.code == sf::Keyboard::Left)
					player.moveLeft();
				if (event.key.code == sf::Keyboard::Right)
					player.moveRight();
				/*if (event.key.code == sf::Keyboard::Space)
					player.shoot();*/
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
	window->draw(player.getTank());
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
			case 'p': if (playerSet) break; else {
				player.setPosition(col * 16, row * 16);
				playerSet = true;  break;
			}
			case 'e': if (eagleSet) break; else {
				eagle.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(eagle); eagleSet = true; maps->at(col)[row] = 'e'; break;
			}
			case 'b': brick.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(brick); maps->at(col)[row] = 'b'; break;
			case 's': stone.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(stone); maps->at(col)[row] = 's'; break;
			default:
				break;
			}
			col++;
		}
		row++;
		col = 0;
	}
	player.getMap(maps);
	/*for (auto i = 0; i < maps->size(); i++) {
		for (auto j = 0; j < maps->at(i).size(); j++) {
			printf("%c", maps->at(i)[j]);
		}
		printf("\n");
	}*/
}