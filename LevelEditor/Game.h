#pragma once
class Game
{
	EventHandler event;
	ShapeManager shapeManager;
	sf::RenderWindow& window;
	sf::Time& dt;

public:
	Game(sf::RenderWindow& window, sf::Time& dt);
	void HandleEvent(sf::Event e);
	void ImGui();
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
};

