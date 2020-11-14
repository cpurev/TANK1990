#include "mapDrawer.hpp"
#include <fstream>

void drawStage(sf::RenderWindow* window) {
	sf::Texture brickTex;
	brickTex.loadFromFile("rsc/brick.png");
	sf::Sprite brick(brickTex);
	brick.setTextureRect(sf::IntRect(0, 0, 16, 16));

	sf::Texture stoneTex;
	stoneTex.loadFromFile("rsc/stone.png");
	sf::Sprite stone(stoneTex);
	stone.setTextureRect(sf::IntRect(0, 0, 16, 16));

	std::ifstream file("stages/stage1.txt");
	std::string line;
	int col = 0, row = 0;
	while (std::getline(file, line)) {
		for (auto x : line) {
			switch (x) {
			case 'a': break;
			case 'b': brick.setPosition(0.f + col * 16, 0.f + row * 16);
				window->draw(brick);
				break;
			case 's': stone.setPosition(0.f + col * 16, 0.f + row * 16);
				window->draw(stone); break;
			default:
				break;
			}
			col++;
		}
		row++;
		col = 0;
	}

}