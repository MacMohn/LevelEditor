#pragma once
struct Keys
{
	sf::Keyboard::Key ins = sf::Keyboard::Key::Insert;
	sf::Keyboard::Key enter = sf::Keyboard::Key::Enter;
	sf::Keyboard::Key unknown = sf::Keyboard::Key::Unknown;
};

struct Mouse
{
	sf::Vector2f GetPosition(sf::RenderWindow& window);
};