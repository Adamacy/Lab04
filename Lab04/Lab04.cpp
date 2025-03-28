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

	std::vector<CustomRectangleShape> rectangles;

	for (int i = 0; i < 10; i++)
	{
		sf::Vector2f size(120.0, 60.0);
		sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
		rectangles.emplace_back(CustomRectangleShape(size, position));
	}

	for (auto& rec : rectangles)
	{
		rec.setFillColor(sf::Color(0, 255, 0));
		rec.setBounds(0, 0, window.getSize().x, window.getSize().y);
		rec.setSpeed(100, 200, sf::degrees(10));
	}
	CustomRectangleShape* currentlyClicked = nullptr;
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		window.clear(sf::Color::Black);
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			for (auto& rec : rectangles)
			{
				
				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
					if (currentlyClicked) {
						currentlyClicked->moveInDirection(elapsed, keyPressed->scancode);
						std::cout << currentlyClicked->getPosition().x << " " << currentlyClicked->getPosition().y << "\n";
					}
				}
				if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
					if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
						if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
							sf::Vector2i mousePosition = mouseButtonPressed->position;
							if (rec.isClicked(mousePosition)) {
								currentlyClicked = &rec;
								rec.setFillColor(sf::Color(255, 0, 255));
							}
							else {
								rec.setFillColor(sf::Color(0, 255, 0));
							}
						}
					}
				}
			}
		}
		for (auto rec : rectangles) {
			window.draw(rec);
		}
		

		

		window.display();
	}
	return 0;
}
