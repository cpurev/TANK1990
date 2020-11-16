//menu.hpp
//Game starting menu
#ifndef MENU_HEADER
#define MENU_HEADER
#include "SFML/Graphics.hpp"

#define MENU_ITEMS 2

class Menu {
public:
	Menu();
	void start(int width, int height);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getItemIndex();
private:
	int item;
	sf::Font font;
	sf::Text items[MENU_ITEMS];
	sf::Text title;
};

#endif