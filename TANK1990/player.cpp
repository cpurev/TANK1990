#include "player.hpp"

Player::Player() {

	texture.loadFromFile("rsc/texture.png");
	playerTank.setTexture(texture);
	playerTank.setTextureRect(sf::IntRect(4 * 32, 0, 32, 32));

	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(29 * 32 + 16, 4*32, 8, 8));

}
void Player::setColor(sf::Color color) {
	playerTank.setColor(color);
}


void Player::setPosition(int x, int y) {
	position = sf::Vector2f((float)x, (float)y);

	playerTank.setPosition(position);
}

int Player::draw(sf::RenderWindow* window) {
	//Draw tank
	window->draw(playerTank);
	//If bullet is there dont draw bullet
	if (!isBullet)
		return 0;
	window->draw(bullet);
	//Bullet exists
	exBullet = true;
	//Calculate bullet position
	bullet.setPosition(bullet.getPosition().x + bulletVelX, bullet.getPosition().y + bulletVelY);
	bulPosition.x += (int)bulletVelX; bulPosition.y += (int)bulletVelY;

	//If bullet is out of map
	if (bullet.getPosition().x > 416 || bullet.getPosition().x < -8 || bullet.getPosition().y > 416 || bullet.getPosition().y < -8) {
		exBullet = false; isBullet = false; return 0;
	}
	
	//Avoid negative index 
	if (bulPosition.x < 0 || bulPosition.y < 0)
		return 0;

	//Velocity is 8 but we want it to go by 16
	//Every 2nd time it will go throught
	if (!trvBullet) {
		trvBullet = true; return 0;
	}
	else
		trvBullet = false;

	//Current bullet position in x and y
	int x = bulPosition.x / 16, y = bulPosition.y / 16;

	//Bullet direction
	if (dirBullet) {
		//Up or down
		if (maps->at(x)[y] == 'b' || maps->at((size_t)(x + 1))[y] == 'b') {
			isBullet = false; exBullet = false;
			maps->at(x)[y] = 'a';
			maps->at(x + 1)[y] = 'a';
			//Pass index of sprite to delete in game.cpp
			return ((y * 26) + x);
		}
		else if (maps->at(x)[y] == 'a' || maps->at(x + 1)[y] == 'a') // if its area go on
			return 0;
		else if (maps->at(x)[y] == 'e' || maps->at(x + 1)[y] == 'e') { // if its eagle decrease eagle life
			printf("%d %d\n", x, y);
			isBullet = false; exBullet = false; return -1;
		}
		else { // if its stone or any other object bullet explodes
			isBullet = false; exBullet = false; return 0;
		}
	}
	else {
		//Same as horizantal but changing y value instead
		if (maps->at(x)[y] == 'b' || maps->at(x )[y + 1 ] == 'b') {
			isBullet = false; exBullet = false;
			maps->at(x)[y] = 'a';
			maps->at(x)[y + 1] = 'a';
			//printf("%d", ((bulPosition.y / 16) * 26) + bulPosition.x / 16);
			return ((y * 26) + x);
		}
		else if (maps->at(x)[y] == 'a' || maps->at(x)[y + 1] == 'a')
			return 0;
		else if (maps->at(x)[y] == 'e' || maps->at(x)[y + 1] == 'e'){
			printf("%d %d\n", x, y);
			 isBullet = false; exBullet = false; return -1;
		}
		else {
			isBullet = false; exBullet = false; return 0;
		}
	}
	return 0;
}

bool Player::getDir() {
	return dirBullet;
}
void Player::printmap() {
	for (auto i = 0; i < 26; i++) {
		for (auto j = 0; j < 26; j++) {
			printf("%c ", maps->at(j)[i]);
		}
		printf("\n");
	}
}
std::shared_ptr<std::vector<std::vector<char>>> Player::maps = nullptr;

void Player::getMap(std::shared_ptr<std::vector<std::vector<char>>>& m){
	maps = m;
}
void Player::moveUp() {
	playerTank.setTextureRect(sf::IntRect(24 * 32, 0, 32, 32));
	//face = 'U';
	//This avoids bullet changing texture after fired
	if (!isBullet) {
		dirBullet = true;
		bullet.setTextureRect(sf::IntRect(29 * 32 + 16, 4 * 32, 8, 8));
		bulletVelX = 0; bulletVelY = -8;
	}
	//Map boundry
	if (position.y - 16 < 0)
		return;
	//if the next area is not empty return
	if (maps->at(position.x / 16)[(position.y - 16 ) / 16] != 'a')
		return;
	if (maps->at((position.x+16) / 16)[(position.y - 16) / 16] != 'a')
		return;

	//set new positions
	position = sf::Vector2f(position.x, position.y-16);
	playerTank.setPosition(position);
}
void Player::moveRight() {
	playerTank.setTextureRect(sf::IntRect(25* 32, 0, 32, 32));
	//face = 'R';
	//This avoids bullet changing texture after fired
	if (!isBullet) {
		dirBullet = false;
		bullet.setTextureRect(sf::IntRect(29 * 32 + 24, 4 * 32, 8, 8));
		bulletVelX = 8; bulletVelY = 0;
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
	//face = 'D';
	//This avoids bullet changing texture after fired
	if (!isBullet) {
		dirBullet = true;
		bullet.setTextureRect(sf::IntRect(30 * 32, 4 * 32, 8, 8));
		bulletVelX = 0; bulletVelY = 8;
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
	//face = 'L';
	//This avoids bullet changing texture after fired
	if (!isBullet) {
		dirBullet = false;
		bullet.setTextureRect(sf::IntRect(30 * 32 + 8, 4 * 32, 8, 8));
		bulletVelX = -8; bulletVelY = 0;
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
	//Values for bullet position
	float x = 0, y = 0;
	float pathX = position.x / 16, pathY = position.y / 16;

	//if bullet exists dont make another
	if (exBullet)
		return;

	//bullet is 
	isBullet = true;

	index = 0;
	//Bullet fires from center of tank
	//Set the position of starting bullet position
	bullet.setPosition(position.x + 12, position.y +12);
	bulPosition.x = (int)position.x;
	bulPosition.y = (int)position.y;

	/*switch (face) {
	case 'U': x = 0; y = -1; break;
	case 'R': x = 1; y = 0; break;
	case 'D': x = 0; y = 1; break;
	case 'L': x = -1; y = 0; break;
	default: break;
	}
	//printf("%f %f\n", pathX, pathY);
	int i = 0;
	while (maps->at(pathX)[pathY] == 'a') {
		pathX += x; pathY += y;
		if (pathX >= 26 || pathY >= 26)
			break;
		if (pathX < 0 || pathY < 0)
			break;

		if (y == 0) {
			bulletPath[i] = pathX; bulletfixed = pathY;
		}
		else {
			bulletPath[i] = pathY; bulletfixed = pathX;
		}
		i++;
		index++;
	}*/
	//printmap();

	//printf("\n\n");
	//printf("%d", bar(&maps));
}