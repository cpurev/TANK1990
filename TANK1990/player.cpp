#include "player.hpp"
extern "C" int bar(int *a); // written in assembly!

Player::Player() {
	
	texture.loadFromFile("rsc/texture.png");
	playerTank.setTexture(texture);
	playerTank.setTextureRect(sf::IntRect(24*32, 0, 32, 32));

	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(29 * 32 + 16, 4*32, 8, 8));

}


void Player::setPosition(int x, int y) {
	position = sf::Vector2f((float)x, (float)y);

	playerTank.setPosition(position);
}

void Player::draw(sf::RenderWindow* window) {
	window->draw(playerTank);
	if (!isBullet)
		return;
	window->draw(bullet);
	exBullet = true;
	bullet.setPosition(bullet.getPosition().x + bulletVelX, bullet.getPosition().y + bulletVelY);

	if (bullet.getPosition().x > 416 || bullet.getPosition().x < -8 || bullet.getPosition().y > 416 || bullet.getPosition().y < -8){
		exBullet = false; isBullet = false;
	}
}

void Player::getMap(std::shared_ptr<std::vector<std::vector<char>>>& m){
	maps = m;
}
void Player::moveUp() {
	playerTank.setTextureRect(sf::IntRect(24 * 32, 0, 32, 32));

	if (!isBullet) {
		bullet.setTextureRect(sf::IntRect(29 * 32 + 16, 4 * 32, 8, 8));
		bulletVelX = 0; bulletVelY = -8.5;
	}
	if (position.y - 16 < 0)
		return;
	if (maps->at(position.x / 16)[(position.y - 16 ) / 16] != 'a')
		return;
	if (maps->at((position.x+16) / 16)[(position.y - 16) / 16] != 'a')
		return;

	position = sf::Vector2f(position.x, position.y-16);
	playerTank.setPosition(position);
}
void Player::moveRight() {
	playerTank.setTextureRect(sf::IntRect(25* 32, 0, 32, 32));
	if (!isBullet) {
		bullet.setTextureRect(sf::IntRect(29 * 32 + 24, 4 * 32, 8, 8));
		bulletVelX = 8.5f; bulletVelY = 0;
	}
	if (position.x + 16 > 386)
		return;
	if (maps->at((position.x+32) / 16)[position.y / 16] != 'a')
		return;
	if (maps->at((position.x + 32) / 16)[(position.y+16) / 16] != 'a')
		return;

	position = sf::Vector2f(position.x +16, position.y);
	playerTank.setPosition(position);
}
void Player::moveDown() {
	playerTank.setTextureRect(sf::IntRect(26 * 32, 0, 32, 32));
	if (!isBullet) {
		bullet.setTextureRect(sf::IntRect(30 * 32, 4 * 32, 8, 8));
		bulletVelX = 0; bulletVelY = 8.5f;
	}
	if (position.y + 16 > 386)
		return;
	if (maps->at(position.x / 16)[(position.y + 32) / 16] != 'a')
		return;
	if (maps->at((position.x+16) / 16)[(position.y + 32) / 16] != 'a')
		return;

	position = sf::Vector2f(position.x , position.y + 16);
	playerTank.setPosition(position);
}
void Player::moveLeft() {
	playerTank.setTextureRect(sf::IntRect(27 * 32, 0, 32, 32));
	if (!isBullet) {
		bullet.setTextureRect(sf::IntRect(30 * 32 + 8, 4 * 32, 8, 8));
		bulletVelX = -8.5f; bulletVelY = 0;
	}
	if (position.x - 16 < 0)
		return;
	if (maps->at((position.x-16) / 16)[position.y / 16] != 'a')
		return;
	if (maps->at((position.x - 16) / 16)[(position.y+16) / 16] != 'a')
		return;

	position = sf::Vector2f(position.x - 16, position.y);
	playerTank.setPosition(position);
}

void Player::shoot() {
	if (exBullet)
		return;
	isBullet = true;

	bullet.setPosition(position.x + 12.5f, position.y +12.5f);

	//printf("%d", bar(&maps));
}