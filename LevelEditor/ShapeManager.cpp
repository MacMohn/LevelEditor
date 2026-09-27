#include "pch.h"
#include "ShapeManager.h"

void ShapeManager::ImGui()
{
//
	ImGui::Begin("STATE");
	if (mode == Mode::Add)
	{
		ImGui::Text("Add");
	}
	else if (mode == Mode::Select)
	{
		ImGui::Text("Select");
	}
	if (shapeType == ShapeType::Rectangle)
	{
		ImGui::Text("Rectangle");
	}
	else if (shapeType == ShapeType::Circle)
	{
		ImGui::Text("Circle");
	}
	ImGui::End();
//
	ImGui::BeginChild("Shape Manager");
	if (ImGui::Button("Select", { 100, 40 }))
	{
		mode = Mode::Select;
	}
	else if (ImGui::Button("Add", { 100, 40 }))
	{
		mode = Mode::Add;
	}
	if (ImGui::Button("Rectangle", { 100, 40 }))
	{
		shapeType = ShapeType::Rectangle;
	}
	else if (ImGui::Button("Circle", { 100, 40 }))
	{
		shapeType = ShapeType::Circle;
	}
	else if (ImGui::Button("None"))
	{
		mode = Mode::None;
		shapeType = ShapeType::None;
	}
	ImGui::EndChild();

//
	ImGui::Begin("Mouse");
	ImGui::Text("MouseClick X: %f", mousePressPos.x);
	ImGui::Text("MouseClick Y: %f", mousePressPos.y);
	ImGui::Text("MouseRelease X: %f", mouseReleasePos.x);
	ImGui::Text("MouseRelease Y: %f", mouseReleasePos.y);
	if (selectedShape != nullptr)
	{
		ImGui::Text("shapePos X: %f", selectedShape->position.x);
		ImGui::Text("shapePos Y: %f", selectedShape->position.y);
	}
	ImGui::End();
//
}

void ShapeManager::UpdateClickPosition(const InputEvent& e)
{
	if (e.type == InputType::Mouse)
	{
		if (e.action == InputAction::Press)
		{
			mousePressPos = e.mousePressPos;
		}
		else if (e.action == InputAction::Release)
		{
			mouseReleasePos = e.mouseReleasePos;
		}
	}
}

ShapeData* ShapeManager::MouseOverShape(const InputEvent& e)
{
	return nullptr;
}

Mode ShapeManager::GetMode()
{
	return mode;
}

void ShapeManager::SetWindow(sf::RenderWindow& w)
{
	window = &w;
}

void ShapeManager::CreateShape(const InputEvent& e)
{

	if (mode != Mode::Add || e.action == InputAction::Press) { return; }

	float mouseDeltaX = mouseReleasePos.x - mousePressPos.x;
	float mouseDeltaY = mouseReleasePos.y - mousePressPos.y;
	if (shapeType == ShapeType::Circle && !e.mouseIsPressed)
	{
		ShapeData circle;
		circle.shape = sf::CircleShape{};
		circle.type = ShapeType::Circle;

		auto& shape = std::get<sf::CircleShape>(circle.shape);
		shape.setPosition(mousePressPos);
		shape.setRadius(mouseDeltaX);
		shape.setFillColor(circle.color);

		circle.size = { mouseDeltaX, mouseDeltaX };
		circle.position = shape.getPosition();

		shapeData.push_back(circle);
		std::cout << "YES";
	}
	else if 
	   (shapeType == ShapeType::Rectangle && !e.mouseIsPressed)
	{
		ShapeData rect;
		rect.shape = sf::RectangleShape();
		rect.type = ShapeType::Rectangle;

		auto& shape = std::get<sf::RectangleShape>(rect.shape);
		shape.setPosition(mousePressPos);
		shape.setSize({ mouseDeltaX, mouseDeltaY });
		shape.setFillColor(rect.color);
		shape.setOutlineColor(sf::Color::Magenta);
		shape.setOutlineThickness(-10.f);


		rect.position = shape.getPosition();
		rect.size = shape.getSize();

		shapeData.push_back(rect);
	}
	
}

ShapeData* ShapeManager::SelectShape(const InputEvent& e)
{
	if (mode != Mode::Select) {return nullptr; }
	
	for (auto& d : shapeData)
	{
		bool shapeContainsMouse = std::visit(
			[&](auto& shape)
			{
				return shape.getGlobalBounds().contains(mousePressPos);
			},
			d.shape
		);
		if (shapeContainsMouse && e.mouseIsPressed)
		{
			d.selected = true;
			selectedShape = &d;
			return &d;
		}
		else
		{
			d.selected = false;
		}
	}
	selectedShape = nullptr;
	return nullptr;
}

void ShapeManager::MoveShape()
{
	if (!selectedShape)
	{
		return;
	}
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
	if (selectedShape->type == ShapeType::Rectangle)
	{
		sf::Vector2f newPos = { mousePos.x - selectedShape->size.x / 2, mousePos.y - selectedShape->size.y / 2 };
		selectedShape->setPosition(newPos);
	}
	else if (selectedShape->type == ShapeType::Circle)
	{
		sf::Vector2f newPos = { mousePos.x - selectedShape->size.x, mousePos.y - selectedShape->size.y};
		selectedShape->setPosition(newPos);

	}
}

void ShapeManager::ResizeShape()
{

	for (auto& d : shapeData)
	{
		bool shapeContainsMouse = std::visit(
			[&](auto& shape)
			{
				return shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)));
			},
			d.shape
		);
		if (shapeContainsMouse)
		{
			mouseOverShape = &d;
		}
	}
	if (sf::Mouse::getPosition(*window).x)
	{

	}
	/*
		if mouse on edge of shape, within a few pixels
		change cursor
	*/
}

void ShapeManager::Draw()
{
	for (auto& d : shapeData)
	{
		std::visit(
			[&](auto& shape)
			{
				window->draw(shape);
			},
			d.shape
		);
	}
}
