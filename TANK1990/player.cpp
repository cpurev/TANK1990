#include "player.hpp"

Player::Player() {
	
	playerTex.loadFromFile("rsc/texture.png");
	playerTank.setTexture(playerTex);
	playerTank.setTextureRect(sf::IntRect(24*32, 0, 32, 32));

}


void Player::setPosition(int x, int y) {
	position = sf::Vector2f((float)x, (float)y);

	playerTank.setPosition(position);
}

sf::Sprite Player::getTank() {
	return playerTank;
}

void Player::moveUp() {
	playerTank.setTextureRect(sf::IntRect(24 * 32, 0, 32, 32));

	position = sf::Vector2f(position.x, position.y-16);
	playerTank.setPosition(position);
}
void Player::moveRight() {
	playerTank.setTextureRect(sf::IntRect(25* 32, 0, 32, 32));

	position = sf::Vector2f(position.x +16, position.y);
	playerTank.setPosition(position);
}
void Player::moveDown() {
	playerTank.setTextureRect(sf::IntRect(26 * 32, 0, 32, 32));

	position = sf::Vector2f(position.x , position.y + 16);
	playerTank.setPosition(position);
}
void Player::moveLeft() {
	playerTank.setTextureRect(sf::IntRect(27 * 32, 0, 32, 32));

	position = sf::Vector2f(position.x - 16, position.y);
	playerTank.setPosition(position);
}