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

int Player::draw(sf::RenderWindow* window) {
	window->draw(playerTank);
	if (!isBullet)
		return 0;
	window->draw(bullet);
	exBullet = true;
	bullet.setPosition(bullet.getPosition().x + bulletVelX, bullet.getPosition().y + bulletVelY);
	bulPosition.x += (int)bulletVelX; bulPosition.y += (int)bulletVelY;
	//printf("%f %f\n", bullet.getPosition().x, bullet.getPosition().y);
	if (bullet.getPosition().x > 416 || bullet.getPosition().x < -8 || bullet.getPosition().y > 416 || bullet.getPosition().y < -8) {
		exBullet = false; isBullet = false; return 0;
	}
	if (bulPosition.x < 0 || bulPosition.y < 0)
		return 0;
	if (!trvBullet) {
		trvBullet = true; return 0;
	}
	else
		trvBullet = false;
	if (dirBullet) {
		if (maps->at(bulPosition.x / 16)[bulPosition.y / 16] == 'b' || maps->at((size_t)((bulPosition.x / 16) + 1))[bulPosition.y / 16] == 'b') {
			isBullet = false; exBullet = false;
			maps->at(bulPosition.x / 16)[bulPosition.y / 16] = 'a';
			maps->at((int)((bulPosition.x / 16) + 1))[bulPosition.y / 16] = 'a';
			return (((bulPosition.y / 16) * 26) + bulPosition.x / 16);
		}
		else if (maps->at(bulPosition.x / 16)[bulPosition.y / 16] == 'a' || maps->at((int)((bulPosition.x / 16) + 1))[bulPosition.y / 16] == 'a') 
			return 0;
		else if (maps->at(bulPosition.x / 16)[bulPosition.y / 16] == 'e' || maps->at((int)((bulPosition.x / 16) + 1))[bulPosition.y / 16] == 'e') {
			isBullet = false; exBullet = false; return -1;
		}
		else {
			isBullet = false; exBullet = false;
		}
	}
	else {
		if (maps->at(bulPosition.x / 16)[bulPosition.y / 16] == 'b' || maps->at((bulPosition.x / 16.0f) )[bulPosition.y / 16 + 1 ] == 'b') {
			isBullet = false; exBullet = false;
			maps->at(bulPosition.x / 16)[bulPosition.y / 16] = 'a';
			maps->at((bulPosition.x / 16.) )[bulPosition.y / 16 + 1] = 'a';
			//printf("%d", ((bulPosition.y / 16) * 26) + bulPosition.x / 16);
			return (((bulPosition.y / 16) * 26) + bulPosition.x / 16);
		}
		else if (maps->at(bulPosition.x / 16)[bulPosition.y / 16] == 'a' || maps->at((bulPosition.x / 16.0f))[bulPosition.y / 16 + 1] == 'a')
			return 0;
		else if (maps->at(bulPosition.x / 16)[bulPosition.y / 16] == 'e' || maps->at((bulPosition.x / 16.0f))[bulPosition.y / 16 + 1] == 'e'){
			 isBullet = false; exBullet = false; return -1;
		}
		else {
			isBullet = false; exBullet = false;
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

void Player::getMap(std::shared_ptr<std::vector<std::vector<char>>>& m){
	maps = m;
}
void Player::moveUp() {
	playerTank.setTextureRect(sf::IntRect(24 * 32, 0, 32, 32));
	face = 'U';
	if (!isBullet) {
		dirBullet = true;
		bullet.setTextureRect(sf::IntRect(29 * 32 + 16, 4 * 32, 8, 8));
		bulletVelX = 0; bulletVelY = -8;
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
	face = 'R';
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
	face = 'D';
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
	face = 'L';
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
	float x = 0, y = 0;
	float pathX = position.x / 16, pathY = position.y / 16;
	if (exBullet)
		return;
	isBullet = true;

	index = 0;
	//Bullet fires from center of tank
	bullet.setPosition(position.x + 12, position.y +12);
	bulPosition.x = (int)position.x;
	bulPosition.y = (int)position.y;

	switch (face) {
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
	}
	//printmap();

	//printf("\n\n");
	//printf("%d", bar(&maps));
}