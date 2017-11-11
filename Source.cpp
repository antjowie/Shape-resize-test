#include <SFML\Graphics.hpp>
#include <iostream>

int main()
{
	std::cout
		<< "Instructions" << "\n\n"

		<< "Hold left mouse button to extend the shape size.\n"
		<< "Hold right mouse button to shrink the shape size.\n"; 

	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(1280, 720),"SFML - Shape resize test");

	sf::Texture tex;
	tex.loadFromFile("texture.png");
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(32, 32));
	shape.setTexture(&tex);

	shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height);
	
	window.setFramerateLimit(60);

	clock.restart();
	elapsedTime = clock.restart();

	while (window.isOpen())
	{
		elapsedTime = clock.restart();
		while(window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				break;
			default:
				break;
			}

		shape.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2f newSize{ shape.getSize() };
			newSize.y += 100.f * elapsedTime.asSeconds();
			shape.setSize(newSize);
			sf::IntRect temp{ shape.getTextureRect() };
			temp.height = newSize.y;
			shape.setTextureRect(temp);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			sf::Vector2f newSize{ shape.getSize() };
			newSize.y -= 100.f * elapsedTime.asSeconds();
			shape.setSize(newSize);
			sf::IntRect temp{ shape.getTextureRect() };
			temp.height = newSize.y;
			shape.setTextureRect(temp);
		}

		window.clear();
		window.draw(shape);
		window.display();

	}

	return 0;
}