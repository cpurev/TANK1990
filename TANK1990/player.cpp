#include "player.hpp"

Player::Player() {
	playerTex.loadFromFile("rsc/tank.png");
	playerTank.setTexture(playerTex);
	playerTank.setTextureRect(sf::IntRect(0, 0, 32, 32));


}

void Player::setPosition(int x, int y) {
	position = sf::Vector2f((float)x, (float)y);

	playerTank.setPosition(position);
}

sf::Sprite Player::getTank() {
	return playerTank;
}