#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(int x, int y);
	void update();
	void draw(sf::RenderWindow& window);
	void setVelocity(sf::Vector2f vec);
private:
	float speed;
	sf::CircleShape circle;
	sf::Vector2f position;
	sf::Vector2f velocity;
};

Player::Player(int x, int y) : position(x, y), velocity(0, 0), circle(50, 20), speed(10)
{
	circle.setOrigin(sf::Vector2f(50, 50));
}

class Program
{
public:
	Program(int width, int height);
	int mainLoop();
	//void draw();
	void eventHandler(sf::Event events);
private:
	Player p1;
	sf::RenderWindow window;
	int w, h;
};

Program::Program(int width, int height) : w(width), h(height), window(sf::VideoMode(width, height), "Golden Axe", p1(width/2, height/2))
{

}

int Program::mainLoop()
{
	sf::Event events;
	sf::Clock clock;

	if (!window.isOpen())
	{
		std::cout << "Window not open" << std::endl;
		return EXIT_FAILURE;
	}

	while (window.isOpen())
	{
		while (window.pollEvent(events))
		{
			if (events.type == sf::Event::EventType::Closed)
			{
				window.close();
			}

			eventHandler(events);
		}

		if (clock.getElapsedTime().asSeconds() > 1 / 60.0) // update player 60 times/s
		{
			p1.update();
			clock.restart();
		}

		// Clear window
		window.clear(sf::Color::Black);

		// Draw here
		p1.draw(window);

		// Display window
		window.display();
	}

}

void Program::eventHandler(sf::Event events)
{
	if (events.type == sf::Event::EventType::KeyPressed)
	{
		switch (events.key.code)
		{
			case sf::Keyboard::A: // left
			{
				p1.setVelocity({ -1.0, 0 });
				std::cout << "Left" << std::endl;
				break;
			}
			case sf::Keyboard::D: // right
			{
				p1.setVelocity({ -1.0, 0 });
				std::cout << "Right" << std::endl;
				break;
			}
			case sf::Keyboard::W:// up
			{
				p1.setVelocity({ 0, -1.0 });
				std::cout << "Up" << std::endl;
				break;
			}
			case sf::Keyboard::S:// down
			{
				p1.setVelocity({ 0, 1.0 });
				std::cout << "Down" << std::endl;
				break;
			}
		}
	}

	else if (events.type == sf::Event::EventType::KeyReleased)
	{
		p1.setVelocity({ 0.0, 0.0 });
	}

	if (events.type == sf::Event::EventType::MouseMoved)
	{
		sf::Vector2i vec = sf::Mouse::getPosition(window);
		std::cout << vec.x << " " << vec.y << std::endl;
	}
}

void Player::update()
{
	position.x += speed*velocity.x;
	position.y += speed*velocity.y;

	circle.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(circle);
}

void Player::setVelocity(sf::Vector2f vec)
{
	velocity = vec;
}

int main()
{
	Program p(1920, 1080);
	return p.mainLoop();
}