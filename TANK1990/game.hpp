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
#include "player.hpp"
#include <memory>
#define map_vec 

class Game {
public:
	Game();
	void initStage();
	void run();
	void play(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void sidebar(sf::RenderWindow* window);
private:
	Menu menu;
	bool eagleSet = false;
	bool playerSet = false;
	Player player;
	std::vector<sf::Sprite> map;
	std::shared_ptr<std::vector<std::vector<char>>> maps;
	sf::Texture texture;
	sf::Sprite brick;
	sf::Sprite stone;
	sf::Sprite eagle;
	sf::Sprite area;
	sf::Sprite lives;
	sf::Sprite enemy;
	sf::Sprite flag;
	int elives = 20;
	int plives = 10;
	int flives = 1;
	sf::Text fnumber;
	sf::Text pnumber;
	sf::RectangleShape rec;
	sf::Font font;
	sf::Color color;

};

#endif