#pragma once
#include "EventHandler.h"
#include <vector>
#include <variant>

using Shape = std::variant<sf::RectangleShape, sf::CircleShape>;

enum class Mode
{
	None, Add, Select
};
enum class ShapeType
{
	None, Rectangle, Circle
};

struct ShapeData
{
	Shape shape;
	ShapeType type = ShapeType::None;
	sf::Vector2f size = { 0.f, 0.f };
	sf::Color color = sf::Color::Cyan;
	sf::Vector2f origin;
	sf::Vector2f position;
	bool selected = false;

	void setPosition(sf::Vector2f pos)
	{
		std::visit(
			[&](auto& shape)
			{
				shape.setPosition(pos);
				position = shape.getPosition();
			},
			shape
		);
	}
};

class ShapeManager
{
	std::vector<ShapeData> shapeData;
	ShapeData* selectedShape = nullptr;
	ShapeData* mouseOverShape = nullptr;
	ShapeType shapeType = ShapeType::None;
	
	Mode mode = Mode::None;

	sf::RenderWindow* window;

	sf::Vector2f mousePressPos;
	sf::Vector2f mouseReleasePos;

	bool mouseDrag = false;

public:
	void Draw();
	void ImGui();

	Mode GetMode();

	void SetWindow(sf::RenderWindow& w);

	void UpdateClickPosition(const InputEvent& e);
	ShapeData* MouseOverShape(const InputEvent& e);

	void CreateShape(const InputEvent& e);
	ShapeData* SelectShape(const InputEvent& e);
	void MoveShape();
	void ResizeShape();


};

