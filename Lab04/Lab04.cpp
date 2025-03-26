#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CustomRectangle.h"
#include <random>
#include <vector>

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");
	window.setFramerateLimit(60);

	float WIDTH = window.getSize().x;
	float HEIGHT = window.getSize().y;

	CustomRectangleShape rectangle(sf::Vector2f(200, 100), sf::Vector2f(200, 100));
	rectangle.setFillColor(sf::Color(255, 255, 0));
	rectangle.setBounds(0, 0, WIDTH, HEIGHT);
	rectangle.setSpeed(300, 200, sf::degrees(45));

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				rectangle.moveInDirection(elapsed, keyPressed->scancode);
			}
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
					if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
						sf::Vector2i mousePosition = mouseButtonPressed->position;
						if (rectangle.isClicked(mousePosition)) {
							std::cout << "Rectangle clicked!" << std::endl;
						}
					}
				}
			}
		}
		window.clear(sf::Color::Black);

		window.draw(rectangle);

		window.display();
	}
	return 0;
}
