#include "game.hpp"
#include "menu.hpp"

#include <fstream>
#include <iostream>

#include "SFML/Audio/Music.hpp"

Game::Game() : maps(std::make_shared<std::vector<std::vector<char>>>(26, std::vector<char>(26, 'a'))) {
	texture.loadFromFile("rsc/texture.png");

	brick.setTexture(texture);
	brick.setTextureRect(sf::IntRect(29 * 32, 0, 16, 16));

	stone.setTexture(texture);
	stone.setTextureRect(sf::IntRect(29 * 32, 4 * 32 + 16, 16, 16));

	eagle.setTexture(texture);
	eagle.setTextureRect(sf::IntRect(29 * 32 + 16, 0, 32, 32));

	lives.setTexture(texture);
	lives.setTextureRect(sf::IntRect(29 * 32 + 16, 2 * 32 + 16, 16, 16));
	lives.setPosition((float)(424.0f), (float)(184.0f));


	flag.setTexture(texture);
	flag.setTextureRect(sf::IntRect(29 * 32 + 16, 4 * 32 + 16, 16, 16));
	for (float i = 0; i < elives / 2; i++) {
		for (float j = 0; j < 2; j++) {
			flag.setPosition((float)(424.0f + j * 16.0f), (float)(8.0f + i * 16.0f));
			enemy.push_back(flag);
		}
	}

	flag.setTextureRect(sf::IntRect(30 * 32 + 16, 2 * 32, 32, 32));
	flag.setPosition((float)(424.0f), (float)(216.0f));

	if (!font.loadFromFile("rsc/prstartk.ttf")) {/*No font?*/ }

	pnumber.setFont(font);
	pnumber.setString(std::to_string(plives));
	pnumber.setCharacterSize(8);
	pnumber.setFillColor(sf::Color::Black);
	pnumber.setPosition((float)(444.0f), (float)(186.0f));

	fnumber.setFont(font);
	fnumber.setString(std::to_string(flives));
	fnumber.setCharacterSize(12);
	fnumber.setFillColor(sf::Color::Black);
	fnumber.setPosition((float)(435.0f), (float)(238.0f));

	over.setFont(font);
	over.setString("GAME OVER!");
	over.setCharacterSize(36);
	over.setFillColor(sf::Color::Red);
	over.setPosition((float)(50.0f), (float)(198.0f));

	rec.setSize(sf::Vector2f(48, 416));
	color.r = 110; color.b = 110; color.g = 110;
	rec.setPosition(416, 0);
	rec.setFillColor(color);
}
void Game::run() {
	int a = 0, b = 0;
	menu.start(416 + 48, 416);
	sf::RenderWindow window(sf::VideoMode(416 + 48, 416), "TANK");
	sf::Music music;
	if (!music.openFromFile("rsc/game_start.wav"))
		std::cout<< "Music Error\n"; // error
	music.play();
	window.setFramerateLimit(60);
	// Start menu
	menu.run(window);
	play(&window);
}
void Game::play(sf::RenderWindow* window) {
	initStage();
	while (window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && flives >= 1) {
				if (event.key.code == sf::Keyboard::Up)
					player.moveUp();
				if (event.key.code == sf::Keyboard::Down)
					player.moveDown();
				if (event.key.code == sf::Keyboard::Left)
					player.moveLeft();
				if (event.key.code == sf::Keyboard::Right)
					player.moveRight();
				if (event.key.code == sf::Keyboard::Space)
					player.shoot();
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (flives < 1) {
			eagle.setTextureRect(sf::IntRect(29 * 32 + 16, 32, 32, 32));
			fnumber.setString(std::to_string(flives));
		}
		window->clear();
		draw(window);
		window->display();
	}
}
void Game::sidebar(sf::RenderWindow* window) {
	window->draw(rec);

	for (auto i : enemy) {
		window->draw(i);
	}

	window->draw(lives);

	window->draw(pnumber);

	window->draw(flag);

	window->draw(fnumber);
}
void Game::draw(sf::RenderWindow* window) {
	//window->draw(map[660]);
	if (flives >= 1) {
		int b = player.draw(window);
		if (b == -1) {
			flives--; return;
		}
		if (b != 0) {
			map[b] = area;
			if (player.getDir()) {
				map[(int)(b + 1)].setColor(sf::Color::Transparent);
			}
			else {

				map[(int)(b + 26)].setColor(sf::Color::Transparent);
			}
		}
	}
	window->draw(eagle);
	for (auto i : map)
		window->draw(i);
	sidebar(window);
	if (flives < 1)
		window->draw(over);
	/*for (auto i = 0; i < 26; i++) {
		for (auto j = 0; j < 26; j++) {
			switch (maps->at(i)[j])
				case 'a':window->draw(map[i * 26 + j]);
					break;
				case 'b':

		}
	}*/
}
void Game::initStage() {

	std::ifstream file("stages/stage1.txt");
	std::string line;
	int col = 0, row = 0;
	while (std::getline(file, line)) {
		for (auto x : line) {
			switch (x) {
			case 'p': if (playerSet) {
				map.push_back(area); 
				break;
			}
					else {
				player.setPosition(col * 16, row * 16);
				playerSet = true;  break;
			}
			case 'e': if (eagleSet) {
				/*map.push_back(eagle);*/ maps->at(col)[row] = 'e';  break;
			}
					else {
				eagle.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(eagle); eagleSet = true; maps->at(col)[row] = 'e'; break;
			}
			case 'b': brick.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(brick); maps->at(col)[row] = 'b'; break;
			case 's': stone.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(stone); maps->at(col)[row] = 's'; break;
			default:
				map.push_back(area);
				break;
			}
			col++;
		}
		row++;
		col = 0;
	}
	player.getMap(maps);
	//printf("%f ", map->at(208).getPosition().x);
	/*for (auto i = 0; i < 26; i++) {
		for (auto j = 0; j < 26; j++) {
			printf("%f ", map[i * 26 + j].getPosition().x);
		}
		printf("\n");
	}*/
}