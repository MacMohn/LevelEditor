#pragma once

enum class InputType
{
	Keyboard, Mouse, None
};

enum class InputAction
{
	Press, Release, None
};

struct InputEvent
{
	InputType type = InputType::None;
	InputAction action = InputAction::None;
	sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;
	sf::Mouse::Button mouseButton;
	sf::Vector2f mousePressPos;
	sf::Vector2f mouseReleasePos;
	sf::Vector2f mousePos;
	bool mouseIsPressed = false;

};

struct EventHandler
{
	Keys keys;
	std::optional<InputEvent> HandleInput(sf::Event e);
};

