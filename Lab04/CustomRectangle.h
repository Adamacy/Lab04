#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomRectangleShape : public sf::RectangleShape {
public:
	CustomRectangleShape(sf::Vector2f size, sf::Vector2f position) : sf::RectangleShape(size) {
		setPosition(position);
	}
	void setSpeed(float horizontalSpeed, float verticalSpeed, sf::Angle rotation = sf::degrees(0)) {
		verticalSpeed_ = verticalSpeed;
		horizontalSpeed_ = horizontalSpeed;
		rotation_ = rotation;
	}
	void animate(const sf::Time& elapsed) {
		move({ horizontalSpeed_ * elapsed.asSeconds(), verticalSpeed_ * elapsed.asSeconds() });
		rotate(rotation_ * elapsed.asSeconds());
		bounce();
	}
	void setBounds(float topBound, float leftBound, float rightBound, float bottomBound) {
		topBound_ = topBound;
		bottomBound_ = bottomBound;
		leftBound_ = leftBound;
		rightBound_ = rightBound;
	}
	void moveInDirection(const sf::Time& elapsed, const sf::Keyboard::Scancode& key) {
		if (key == sf::Keyboard::Scancode::W) {
			std::cout << "Forward" << "\n";  // Check if this prints
			move({ 0, -std::abs(verticalSpeed_ * elapsed.asSeconds()) });
		}
		if (key == sf::Keyboard::Scancode::S) {
			std::cout << "Backward" << "\n";
			move({ 0, std::abs(verticalSpeed_ * elapsed.asSeconds()) });
		}
		if (key == sf::Keyboard::Scancode::A) {
			std::cout << "Left" << "\n";
			move({ -std::abs(horizontalSpeed_ * elapsed.asSeconds()), 0 });
		}
		if (key == sf::Keyboard::Scancode::D) {
			std::cout << "Right" << "\n";
			move({ horizontalSpeed_ * elapsed.asSeconds(), 0 });
		}
		bounce();
	}

private:
	float verticalSpeed_ = 0;
	float horizontalSpeed_ = 0;
	float topBound_ = 0;
	float bottomBound_ = 0;
	float leftBound_ = 0;
	float rightBound_ = 0;
	sf::Angle rotation_ = sf::degrees(0);
	void bounce() {
		if (getPosition().x < leftBound_) {
			horizontalSpeed_ = std::abs(horizontalSpeed_);
		}
		else if (getPosition().x + getSize().x > rightBound_) {
			horizontalSpeed_ = -std::abs(horizontalSpeed_);
		}
		if (getPosition().y < topBound_) {
			verticalSpeed_ = std::abs(verticalSpeed_);
		}
		else if (getPosition().y + getSize().y > bottomBound_) {
			verticalSpeed_ = -std::abs(verticalSpeed_);
		}
	}
};