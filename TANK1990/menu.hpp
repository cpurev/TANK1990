//menu.hpp
//Game starting menu
#include "SFML/Graphics.hpp"

#define MENU_ITEMS 2

class Menu {
public:
	Menu(int width, int height);
	~Menu();

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