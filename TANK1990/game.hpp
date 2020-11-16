//game.hpp
//Chuluunbat Purev
//2020-10-27
//Takes 26x26 char text file and draws the map according to it
//a - blank; b - brick; s - stone and so on
#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML/Graphics.hpp>
#include <string>
#include "menu.hpp"

class Game {
public:
	Game();
	void drawStage(sf::RenderWindow* window);
	void run();
	void pauseMenu(int width, int height);
private:
	Menu menu;
	sf::Texture brickTex;
	sf::Sprite brick;
	sf::Texture stoneTex;
	sf::Sprite stone;
	sf::Texture tankTex;
	sf::Sprite tank;
};

#endif