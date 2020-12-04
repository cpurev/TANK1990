//game.hpp
//Chuluunbat Purev
//2020-10-27
//Takes 26x26 char text file and draws and updates the map according to it
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
	//Draw stage
	void initStage();
	 
	//Menu draw
	void run();
	//Game draw
	void play(sf::RenderWindow* window);

	//Draw all the sprites
	void draw(sf::RenderWindow* window);

	//Draw side panel with info
	void sidebar(sf::RenderWindow* window);

	//Calculate enemy movement ~ Currently all random
	void calcEnemy(sf::RenderWindow* window);

	//Erase map sprite
	void eraseMapSprite(int i,bool f);
private:
	Menu menu;
	bool eagleSet = false;
	bool playerSet = false;
	Player player;
	Player enemies[2];
	std::vector<sf::Sprite> map;
	std::shared_ptr<std::vector<std::vector<char>>> maps;
	int elives = 20;
	int plives = 10;
	int flives = 1;
	sf::Sprite brick;
	sf::Sprite stone;
	sf::Sprite eagle;
	sf::Sprite area;
	sf::Sprite lives;
	std::vector<sf::Sprite> enemyCount;
	sf::Texture texture;
	sf::Sprite flag;
	sf::Text fnumber;
	sf::Text pnumber;
	sf::Text over;
	sf::RectangleShape rec;
	sf::Font font;
	sf::Color color;
	sf::Clock clock;

};

#endif