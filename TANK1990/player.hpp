//player.hpp
//This class will calculaute tank location and bullet path
//Chuluunbat Purev
//2020-12-4
#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include <SFML/Graphics.hpp>
#include <memory>
class Player {
public:
	Player();

	//Position of the tank
	void setPosition(int x, int y); 

	//Draw tank and bullet
	int draw(sf::RenderWindow* window);

	//Get map
	void getMap(std::shared_ptr<std::vector<std::vector<char>>>& m);
	static std::shared_ptr<std::vector<std::vector<char>>> maps;

	//Keyboard inputs
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void shoot();

	//Debug console print
	void printmap();

	//Get bullet direction TRUE = vertical, FALSE = horizontal
	bool getDir();

	//Color of sidebar
	void setColor(sf::Color color);
private:
	sf::Texture texture;
	sf::Sprite playerTank;
	sf::Sprite bullet;
	//Is bullet fired
	bool isBullet = false;
	//Does bullet exist
	bool exBullet = false;
	//bullet direction
	bool dirBullet = true;
	//bullet is traveling
	bool trvBullet = false;

	//bullet velocity
	float bulletVelX = 0;
	float bulletVelY = -8;

	//Direction tank is facing
	char face = 'U';

	//Bullet path to pass to ASM
	float bulletPath[26] = {};
	float bulletfixed;
	int index = 0;

	//Current Position of tank
	sf::Vector2f position;

	//Current Bullet position
	sf::Vector2i bulPosition;
};

#endif