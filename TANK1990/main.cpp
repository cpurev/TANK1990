#include <iostream>
#include "mapDrawer.hpp"
#include "menu.hpp"


int main() { // create the window
	sf::RenderWindow window(sf::VideoMode(416, 416), "TANK");
	Menu menu(window.getSize().x, window.getSize().y);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up)
					menu.moveUp();
				if (event.key.code == sf::Keyboard::Down)
					menu.moveDown();
				if (event.key.code == sf::Keyboard::Return) {
					if (menu.getItemIndex() == 1)
						window.close();
				}
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		menu.draw(window);

		window.display();
	}

	return 0;
}