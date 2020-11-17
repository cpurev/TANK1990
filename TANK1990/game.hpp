//game.hpp
//Chuluunbat Purev
//2020-10-27
//Takes 26x26 char text file and draws the map according to it
//a - blank; b - brick; s - stone and so on
#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "menu.hpp"

class Game {
public:
	Game();
	void initStage();
	void run();
	void pauseMenu(int width, int height);
	void play(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
private:
	Menu menu;
	std::vector<sf::Sprite> map;
	sf::Texture brickTex;
	sf::Sprite brick;
	sf::Texture stoneTex;
	sf::Sprite stone;
	sf::Texture tankTex;
	sf::Sprite tank;
};

#endif