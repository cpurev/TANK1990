#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include <SFML/Graphics.hpp>
#include <memory>
class Player {
public:
	Player();
	void setPosition(int x, int y);
	sf::Sprite getTank();
	void getMap(std::vector<std::vector<char>>& m);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void shoot();
private:
	sf::Texture playerTex;
	sf::Sprite playerTank;
	sf::Vector2f position;
	std::vector<sf::Sprite> map;
	std::shared_ptr<std::vector<std::vector<char>>> maps;
};

#endif