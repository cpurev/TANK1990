#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include <SFML/Graphics.hpp>
#include <memory>
class Player {
public:
	Player();
	void setPosition(int x, int y); 
	int draw(sf::RenderWindow* window);
	void getMap(std::shared_ptr<std::vector<std::vector<char>>>& m);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void shoot();
	void printmap();
	bool getDir();
	void setColor(sf::Color color);
	static std::shared_ptr<std::vector<std::vector<char>>> maps;
private:
	sf::Texture texture;
	sf::Sprite playerTank;
	sf::Sprite bullet;
	bool isBullet = false;
	bool exBullet = false;
	bool dirBullet = true;
	bool trvBullet = false;
	float bulletVelX = 0;
	float bulletVelY = -8;
	char face = 'U';
	float bulletPath[26] = {};
	float bulletfixed;
	int index = 0;
	sf::Vector2f position;
	sf::Vector2i bulPosition;
};

#endif