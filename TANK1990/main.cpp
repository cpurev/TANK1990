#include <iostream>
#include "mapDrawer.hpp"


int main() { // create the window
	sf::RenderWindow window(sf::VideoMode(416, 416), "TANK");

	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("rsc/tank_font.ttf"))
		return EXIT_FAILURE;
	sf::Text text("TANK", font, 50);
	text.setFillColor(sf::Color::Red);
	text.setLetterSpacing(3.0f);
	text.setPosition(60.f, 100.f);

	sf::Font font1;
	if (!font1.loadFromFile("rsc/prstartk.ttf"))
		return EXIT_FAILURE;
	sf::Text text1("PLAYER 1", font1, 16);
	text1.setFillColor(sf::Color::White);
	text1.setPosition(150.f, 200.f);

	sf::Texture texture;
	texture.loadFromFile("rsc/tank.png");
	sf::Sprite sprite(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setColor(sf::Color::Green);
	sprite.rotate(90.f);
	sprite.setScale(0.5f, 0.7f);
	sprite.setPosition(140.f , 200.f);
	
	bool flash = true;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{

				}
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		// draw everything here...
		if (flash) {
			window.draw(sprite);
			flash = false;
		}
		else
			flash = true;
		window.draw(text);
		window.draw(text1);
		//drawStage(&window);
		// end the current frame
		window.display();
	}

	return 0;
}