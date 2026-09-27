#include "pch.h"
#include "EventHandler.h"

std::optional<InputEvent> EventHandler::HandleInput(sf::Event e)
{
	InputEvent inputEvent;
	
	if (auto* key = e.getIf<sf::Event::KeyPressed>())
	{
		inputEvent.key = key->code;
		inputEvent.action = InputAction::Press;
		inputEvent.type = InputType::Keyboard;
		return inputEvent;
	}
	if (auto* key = e.getIf<sf::Event::KeyReleased>())
	{
		inputEvent.key = key->code;
		inputEvent.action = InputAction::Release;
		inputEvent.type = InputType::Keyboard;
		return inputEvent;
	}
	if (auto* mouse = e.getIf<sf::Event::MouseButtonPressed>())
	{
		inputEvent.mouseIsPressed = true;
		inputEvent.mouseButton = mouse->button;
		inputEvent.action = InputAction::Press;
		inputEvent.mousePressPos = sf::Vector2f(mouse->position);
		inputEvent.type = InputType::Mouse;
		inputEvent.key = keys.unknown;
		return inputEvent;
	}
	if (auto* mouse = e.getIf<sf::Event::MouseButtonReleased>())
	{
		inputEvent.mouseIsPressed = false;
		inputEvent.mouseButton = mouse->button;
		inputEvent.action = InputAction::Release;
		inputEvent.mouseReleasePos = sf::Vector2f(mouse->position);
		inputEvent.type = InputType::Mouse;
		inputEvent.key = keys.unknown;
		return inputEvent;
	}
	
	return std::nullopt;
}

