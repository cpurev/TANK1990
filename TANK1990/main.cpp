#include <iostream>
#include <SFML/Graphics.hpp>

int main() { // create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK");

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
		sf::Texture texture;
		texture.loadFromFile("sbrick.png");
		sf::Sprite sprite(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 20));
		for (auto i = 0; i < window.getSize().x / 32; i++) {
			for (auto j = 0; j < window.getSize().y / 20; j++) {
				sprite.setPosition(0.f + i * 32, 0.f + j * 20);
				window.draw(sprite);
			}
		}

		// end the current frame
		window.display();
	}

	return 0;
}