#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include <SFML/Graphics.hpp>
#include <memory>
class Player {
public:
	Player();
	void setPosition(int x, int y); 
	void draw(sf::RenderWindow* window);
	void getMap(std::shared_ptr<std::vector<std::vector<char>>>& m);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void shoot();
private:
	sf::Texture texture;
	sf::Sprite playerTank;
	sf::Sprite bullet;
	bool isBullet = false;
	bool exBullet = false;
	float bulletVelX = 0;
	float bulletVelY = -8.5f;
	sf::Vector2f position;
	std::shared_ptr<std::vector<std::vector<char>>> maps;
};

#endif