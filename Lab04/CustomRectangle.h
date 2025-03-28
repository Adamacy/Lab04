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
		std::cout << "Scancode pressed: " << static_cast<int>(key) << std::endl;

		if (key == sf::Keyboard::Scancode::W && getPosition().y > topBound_) {
			move({ 0, -std::abs(verticalSpeed_ * elapsed.asSeconds()) });
		}
		else if (key == sf::Keyboard::Scancode::S && getPosition().y + getSize().y < bottomBound_) {
			move({ 0, std::abs(verticalSpeed_ * elapsed.asSeconds()) });
		}
		if (key == sf::Keyboard::Scancode::A && getPosition().x > leftBound_) {
			std::cout << "A pressed, moving left!" << std::endl;
			move({ -std::abs(horizontalSpeed_ * elapsed.asSeconds()), 0 });
		}
		if (key == sf::Keyboard::Scancode::D && getPosition().x + getSize().x < rightBound_) {
			std::cout << "D pressed, moving right!" << std::endl;
			move({ horizontalSpeed_ * elapsed.asSeconds(), 0 });
		}
	}
    bool isClicked(const sf::Vector2i& mouse_position) const {  
       float rectX = getPosition().x;  
       float rectY = getPosition().y;  
       float rectWidth = getSize().x;  
       float rectHeight = getSize().y;  

       // Check if the mouse click is within the bounds of the rectangle  
       if (mouse_position.x >= rectX && mouse_position.x <= rectX + rectWidth &&  
           mouse_position.y >= rectY && mouse_position.y <= rectY + rectHeight) {  
           return true;  
       }  
       return false;  
    }
	void setClicked(bool clicked) { clicked_ = clicked; }
private:
	float verticalSpeed_ = 0;
	float horizontalSpeed_ = 0;
	float topBound_ = 0;
	float bottomBound_ = 0;
	float leftBound_ = 0;
	float rightBound_ = 0;
	bool clicked_ = false;
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