#include "pch.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");
    sf::Clock clock;
    sf::Time dt;

    sf::Cursor cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::SizeHorizontal).value();
    window.setMouseCursor(cursor);

    Game game(window, dt);
   
    ImGui::SFML::Init(window);
    
    while (window.isOpen())
    {
        dt = clock.restart();
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();

            game.HandleEvent(*event);
        }

        ImGui::SFML::Update(window, dt);
        game.ImGui();
        window.clear();
        game.Update(window);
        game.Draw(window);
        ImGui::SFML::Render(window);
        window.display();
    }
}