//menu.hpp
//Game starting menu
//Chuluunbat Purev
//2020-12-4
#ifndef MENU_HEADER
#define MENU_HEADER
#include "SFML/Graphics.hpp"

#define MENU_ITEMS 2

class Menu {
public:
	Menu();
	//Scaling to window
	void start(int width, int height);

	//Keyboard inputs
	void moveUp();
	void moveDown();

	//Get seleceted menu item
	int getItemIndex();

	//Draw the menu
	void run(sf::RenderWindow& window);
private:
	int item;
	sf::Font font;
	sf::Text items[MENU_ITEMS];
	sf::Sprite ttle;
	sf::Texture texture;
};

#endif