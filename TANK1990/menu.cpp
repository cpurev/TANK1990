#include "menu.hpp"
Menu::Menu() {}
void Menu::start(int width, int height) {
	if (!font.loadFromFile("rsc/tank_font.ttf")) {/*No font?*/ }

	title.setFont(font);
	title.setCharacterSize(32);
	title.setFillColor(sf::Color::Red);
	title.setString("TANK 1990");
	title.setPosition(width / 6, height/2 - 64);

	if (!font.loadFromFile("rsc/prstartk.ttf")) {/*No font?*/}
	
	items[0].setFont(font);
	items[0].setCharacterSize(12);
	items[0].setFillColor(sf::Color::White);
	items[0].setString("PLAY");
	items[0].setPosition(width / 2 - 16, height / 2 );

	items[1].setFont(font);
	items[1].setCharacterSize(12);
	items[1].setFillColor(sf::Color::White);
	items[1].setString("QUIT");
	items[1].setPosition(width/2 - 16, height/2 + 32);

	item = -1;
}

void Menu::draw(sf::RenderWindow &window) {
	window.draw(title);
	for (auto i = 0; i < MENU_ITEMS; i++) {
		window.draw(items[i]);
	}
}

void Menu::moveUp() {
	if (item - 1 >= 0) {
		items[item].setFillColor(sf::Color::White);
		item--;
		items[item].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown() {
	if (item + 1 < MENU_ITEMS) {
		items[item].setFillColor(sf::Color::White);
		item++;
		items[item].setFillColor(sf::Color::Red);

	}
}
int Menu::getItemIndex() {
	return item;
 }