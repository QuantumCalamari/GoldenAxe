#include <SFML/Graphics.hpp>

int windowWidth = 960;
int windowHeight = 540;
float gravity = 0.5f;
float ground = windowHeight - 200.f;

sf::Vector2f playerStart_pos = sf::Vector2f(windowWidth / 2, ground);
sf::Vector2f enemyStart_pos = sf::Vector2f(windowWidth / 1.5, ground);
sf::Vector2f playerVelocity = sf::Vector2f(0, 0); // initial velocity
sf::Vector2f playerAcceleration = sf::Vector2f(0, 0); // initial acceleration

void movePlayer() {
	if (playerStart_pos.y > ground) {
		playerVelocity.y += gravity;
	}
	else if (playerStart_pos.y < ground) {
		playerStart_pos.y = ground;
	}

	playerVelocity.x += playerAcceleration.x;
	playerVelocity.y += playerAcceleration.y;

	playerStart_pos.x += playerVelocity.x;
	playerStart_pos.y += playerVelocity.y;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Golden Axe");

	sf::CircleShape enemy(20.f, 50.f);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("sprites/archer/spr_ArcherRun_strip_NoBkg.png");
	int playerSpriteFrameN = 8; // number of frames in sprite
	
	sf::IntRect rectSourceSprite(playerTexture.getSize().x / playerSpriteFrameN, 0, playerTexture.getSize().x / playerSpriteFrameN, playerTexture.getSize().y);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			playerVelocity.x = -1;
		}
		else {
			playerVelocity.x = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerVelocity.x = 1;
		}
		else {
			playerVelocity.x = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			playerVelocity.y = -50;
		}
		else {
			playerVelocity.y = 0;
		}

		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			if (rectSourceSprite.left == (playerTexture.getSize().x / playerSpriteFrameN)*2)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += playerTexture.getSize().x / playerSpriteFrameN;

			playerSprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}

		movePlayer();
		playerSprite.setPosition(playerStart_pos.x, playerStart_pos.y);
		enemy.setPosition(enemyStart_pos.x, enemyStart_pos.y);

		window.clear();
		window.draw(playerSprite);
		window.draw(enemy);
		window.display();
	}

	return 0;
}