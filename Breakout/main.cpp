#include "Paddle.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(768, 500), "Breakout!");

	Paddle paddle;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		paddle.drawPaddle(window);
		window.display();
	}

	return 0;
}
