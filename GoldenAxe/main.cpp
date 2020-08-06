#include <SFML/Graphics.hpp>

int windowWidth = 960;
int windowHeight = 540;
float gravity = 0.5f;

// Ground
sf::RectangleShape ground(sf::Vector2f(windowWidth, 32)); // would be better if this didn't exist, currently used to offset player start pos as can't get sprite load to work outside main loop

// Test enemy
sf::RectangleShape enemy(sf::Vector2f(20, 50));

sf::Vector2f playerStart_pos = sf::Vector2f(windowWidth / 2, windowHeight - ground.getSize().y - 76); // 76 should be found from player sprite height
sf::Vector2f enemyStart_pos = sf::Vector2f(windowWidth / 1.5, windowHeight - ground.getSize().y);
sf::Vector2f playerVelocity = sf::Vector2f(0, 0); // initial velocity
sf::Vector2f playerAcceleration = sf::Vector2f(0, 0); // initial acceleration

void movePlayer() {
	if (playerStart_pos.y > windowHeight - ground.getSize().y) {
		playerVelocity.y += gravity;
	}
	else if (playerStart_pos.y < windowHeight - ground.getSize().y) {
		playerStart_pos.y = windowHeight - ground.getSize().y - 76; // 76 should be found from player sprite height
	}

	playerVelocity.x += playerAcceleration.x;
	playerVelocity.y += playerAcceleration.y;

	playerStart_pos.x += playerVelocity.x;
	playerStart_pos.y += playerVelocity.y;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Golden Axe");
	sf::Clock clock;
	window.setFramerateLimit(120);

	ground.setFillColor(sf::Color::Green);
	enemy.setFillColor(sf::Color::Red);
	enemy.setOrigin(enemy.getSize().x, enemy.getSize().y);
	
	// Player Texture
	sf::Texture playerTexture;
	playerTexture.loadFromFile("sprites/archer/spr_ArcherRun_strip_NoBkg.png");
	int playerSpriteFrameN = 8; // number of frames in sprite
	sf::IntRect rectPlayerSprite(playerTexture.getSize().x / playerSpriteFrameN, 0, playerTexture.getSize().x / playerSpriteFrameN, playerTexture.getSize().y);
	sf::Sprite playerSprite(playerTexture, rectPlayerSprite);
	
	// Ground Texture
	sf::Texture groundTexture;
	groundTexture.loadFromFile("sprites/Ground_crop.png");
	sf::IntRect rectGroundSprite(groundTexture.getSize().x, 0, windowWidth, groundTexture.getSize().y);
	groundTexture.setRepeated(true);
	sf::Sprite groundSprite(groundTexture, rectGroundSprite);
	

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			playerVelocity.x = -2;
		}
		else {
			playerVelocity.x = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerVelocity.x = 2;
		}
		else {
			playerVelocity.x = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			playerVelocity.y = -50;
		}
		else {
			playerVelocity.y = 0;
		}

		if (clock.getElapsedTime().asSeconds() > 0.2f) {
			if (rectPlayerSprite.left == (playerTexture.getSize().x / playerSpriteFrameN)*2)
				rectPlayerSprite.left = 0;
			else
				rectPlayerSprite.left += playerTexture.getSize().x / playerSpriteFrameN;

			playerSprite.setTextureRect(rectPlayerSprite);
			clock.restart();
		}

		movePlayer();
		ground.setPosition(0, windowHeight - ground.getSize().y);
		groundSprite.setPosition(0, windowHeight - groundTexture.getSize().y);
		playerSprite.setPosition(playerStart_pos);
		enemy.setPosition(enemyStart_pos);

		window.clear();
		window.draw(groundSprite);
		window.draw(playerSprite);
		window.draw(enemy);
		window.display();
	}

	return 0;
}