#include "game.hpp"
#include "menu.hpp"

#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/Audio/Music.hpp"

extern "C" int bar(std::vector<sf::Sprite>& map); // written in assembly!

Game::Game() : maps(std::make_shared<std::vector<std::vector<char>>>(26, std::vector<char>(26, 'a'))) {
	texture.loadFromFile("rsc/texture.png");

	area.setTexture(texture);
	area.setTextureRect(sf::IntRect(29 * 32, 0, 16, 16));
	area.setColor(sf::Color::Transparent);

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
			enemyCount.push_back(flag);
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

	//CAN BE DYNAMIC ~~~ BOT SPAWN LOCATION
	enemies[0].setPosition(4 * 16, 0);
	enemies[0].setColor(sf::Color::White);
	enemies[0] = player;

	enemies[1].setPosition(20 * 16, 0);
	//enemies[1]=player;
	enemies[1].setColor(sf::Color::White);

}
void Game::run() {
	int a = 0, b = 0;
	menu.start(416 + 48, 416);
	sf::RenderWindow window(sf::VideoMode(416 + 48, 416), "TANK");
	/*sf::Music music;
	if (!music.openFromFile("rsc/game_start.wav"))
		std::cout<< "Music Error\n"; // error
	music.play();*/
	window.setFramerateLimit(60);
	// Start menu
	menu.run(window);
	play(&window);
}
void Game::play(sf::RenderWindow* window) {
	//Load the stage after menu
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
		//If no eagle lives left
		if (flives < 1) {
			eagle.setTextureRect(sf::IntRect(29 * 32 + 16, 32, 32, 32));
			fnumber.setString(std::to_string(flives));
		}
		window->clear();
		draw(window);
		window->display();
	}
}

void Game::eraseMapSprite(int i, bool f) {
	//i = index of sprite to delete in vector
	//i == 0 nothing to erase
	if (i == 0)
		return;

	//eagle hit
	if (i == -1) {
		flives--; return;
	}
	//erase sprites from drawing vector
	if (i > 0) {
		map[i] = area;
		if (f) {
			printf("%d\n", i + 1);
			map[i + 1] = area;
		}
		else {
			printf("%d\n", i + 26);
			map[i + 26] = area;
		}
	}

}
void Game::calcEnemy(sf::RenderWindow* window) {
	//if eagle destroyed stop movement
	if (flives < 1)
		return;

	//random movement every 1 second
	srand(time(0));
	int move = (rand() % 4) + 1;
	if (clock.getElapsedTime().asSeconds() > 1.0f) {
		if (move == 4) enemies[0].moveDown();
		if (move == 3) enemies[0].moveUp();
		if (move == 2) enemies[0].moveRight();
		if (move == 1) enemies[0].moveLeft();

		move = (rand() % 4) + 1;
		if (move == 4) enemies[1].moveDown();
		if (move == 3) enemies[1].moveUp();
		if (move == 2) enemies[1].moveRight();
		if (move == 1) enemies[1].moveLeft();
		enemies[0].shoot(); enemies[1].shoot();
		clock.restart();
	}
	//update the map
	eraseMapSprite(enemies[0].draw(window), enemies[0].getDir());
	eraseMapSprite(enemies[1].draw(window), enemies[1].getDir());

	//draw bullets and tank
	enemies[0].draw(window);
	enemies[1].draw(window);
}

//Drawing side bar contents
void Game::sidebar(sf::RenderWindow* window) {
	window->draw(rec);

	for (auto i : enemyCount) {
		window->draw(i);
	}

	window->draw(lives);

	window->draw(pnumber);

	window->draw(flag);

	window->draw(fnumber);
}
void Game::draw(sf::RenderWindow* window) {
	//if game is not over calculate sprite to erase
	if (flives >= 1) {
		eraseMapSprite(player.draw(window), player.getDir());
	}
	//Enemy calcualte sprite to erase
	calcEnemy(window);

	//Draw eagle
	window->draw(eagle);

	//Draw rest of map
	for (auto i : map)
		window->draw(i);

	//Draw sidebar
	sidebar(window);

	//If the game is over draw over text
	if (flives < 1)
		window->draw(over);
}
void Game::initStage() {

	std::ifstream file("stages/stage1.txt");
	std::string line;
	int col = 0, row = 0;
	while (std::getline(file, line)) {
		for (auto x : line) {
			switch (x) {
			case 'p': if (playerSet) {
				area.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(area); 
				break;
			}
					else {
				area.setPosition((float)(col * 16), (float)(row * 16));
				player.setPosition(col * 16, row * 16);
				playerSet = true;  break;
			}
			case 'e': if (eagleSet) {
				area.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(area); maps->at(col)[row] = 'e';  break;
			}
					else {
				area.setPosition((float)(col * 16), (float)(row * 16));
				eagle.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(area); eagleSet = true; maps->at(col)[row] = 'e'; break;
			}
			case 'b': brick.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(brick); maps->at(col)[row] = 'b'; break;
			case 's': stone.setPosition((float)(col * 16), (float)(row * 16));
				map.push_back(stone); maps->at(col)[row] = 's'; break;
			default:
				area.setPosition((float)(col * 16), (float)(row * 16));
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