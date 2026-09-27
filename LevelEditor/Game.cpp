#include "pch.h"
#include "Game.h"
#include "EventHandler.h"

Game::Game(sf::RenderWindow& window, sf::Time& dt) : window(window), dt(dt)
{
	shapeManager.SetWindow(window);
}

void Game::HandleEvent(sf::Event e)
{
	auto input = event.HandleInput(e);
	if (input)
	{
		shapeManager.UpdateClickPosition(*input);
		shapeManager.CreateShape(*input);
		shapeManager.SelectShape(*input);
	}
}

void Game::ImGui()
{
    shapeManager.ImGui();
}

void Game::Draw(sf::RenderWindow& window)
{
	shapeManager.Draw();
}

void Game::Update(sf::RenderWindow& window)
{
	shapeManager.MoveShape();
}
