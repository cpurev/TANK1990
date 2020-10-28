#include <iostream>
#include "mapDrawer.hpp"


int main() { // create the window
	sf::RenderWindow window(sf::VideoMode(416, 416), "TANK");

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		// draw everything here...
		
		/*texture.loadFromFile("img/tank.png");
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		sprite.setColor(sf::Color::Green);
		sprite.setPosition(100.f , 100.f);
		window.draw(sprite);*/
		drawStage(&window);
		// end the current frame
		window.display();
	}

	return 0;
}