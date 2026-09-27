#include "pch.h"
#include "Inputs.h"

sf::Vector2f Mouse::GetPosition(sf::RenderWindow& window)
{
    sf::Vector2i m = sf::Mouse::getPosition(window);
    return sf::Vector2f(m);
}
