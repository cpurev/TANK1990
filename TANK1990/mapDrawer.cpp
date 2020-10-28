#include "mapDrawer.hpp"
#include <fstream>

void drawStage(sf::RenderWindow* window) {
	sf::Texture texture;
	texture.loadFromFile("img/brick.png");
	sf::Sprite sprite(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	sf::Texture texture1;
	texture1.loadFromFile("img/stone.png");
	sf::Sprite sprite1(texture1);
	sprite1.setTextureRect(sf::IntRect(0, 0, 16, 16));

	std::ifstream file("stages/stage1.txt");
	std::string line;
	int col = 0, row = 0;
	while (std::getline(file, line)) {
		for (auto x : line) {
			switch (x) {
			case 'a': break;
			case 'b': sprite.setPosition(0.f + col * 16, 0.f + row * 16);
				window->draw(sprite);
				break;
			case 's': sprite1.setPosition(0.f + col * 16, 0.f + row * 16);
				window->draw(sprite1); break;
			default:
				break;
			}
			col++;
		}
		row++;
		col = 0;
	}

}