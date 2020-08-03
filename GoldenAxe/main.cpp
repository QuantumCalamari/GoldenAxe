#include <SFML/Graphics.hpp>

int windowWidth = 1920;
int windowHeight = 1080;
float moveSpeed = 0.25f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Golden Axe");

	sf::Vector2f playerStart_pos = sf::Vector2f(windowWidth / 2, windowHeight / 2);
	sf::Vector2f enemyStart_pos = sf::Vector2f(windowWidth / 1.5, windowHeight / 1.5);

	sf::CircleShape enemy(40.f, 100.f);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("sprites/archer/spr_ArcherRun_strip_NoBkg.png");

	sf::IntRect rectSourceSprite(1024 / 8, 0, 1024 / 8, 128);
	sf::Sprite playerSprite(playerTexture, rectSourceSprite);
	sf::Clock clock;

	enemy.setFillColor(sf::Color::Red);
	enemy.setOrigin(enemy.getRadius(), enemy.getRadius());
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			playerStart_pos.y += moveSpeed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			playerStart_pos.y -= moveSpeed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			playerStart_pos.x -= moveSpeed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerStart_pos.x += moveSpeed;
		}

		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			if (rectSourceSprite.left == (1024/8)*2)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += 1024 / 8;

			playerSprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}

		playerSprite.setPosition(playerStart_pos.x, playerStart_pos.y);
		enemy.setPosition(enemyStart_pos.x, enemyStart_pos.y);

		window.clear();
		window.draw(playerSprite);
		window.draw(enemy);
		window.display();
	}

	return 0;
}