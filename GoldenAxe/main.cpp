#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");


	sf::Vector2f start_pos = sf::Vector2f(100.0f, 100.0f);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			start_pos.y -= 0.5f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			start_pos.y += 0.5f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			start_pos.x -= 0.5f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			start_pos.x += 0.5f;
		}

		shape.setPosition(start_pos.x, start_pos.y);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}