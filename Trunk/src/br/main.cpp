
// Author: Pierce Brooks

#include <br/BallisticallyRogue.hpp>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

typedef br::BallisticallyRogue Application;

void report(const sf::Vector2f& target)
{
    std::cout << target.x << "  " << target.y << std::endl;
}

int main(int argc, char** argv)
{
    sf::Vector2f center;
    float deltaTime;
    Application* application = new Application();
    sf::Clock* clock = new sf::Clock();
    sf::RenderWindow* window = new sf::RenderWindow();
    auto resolutions = sf::VideoMode::getFullscreenModes();
    window->create(resolutions[resolutions.size()/2], "Ballistically Rogue");
    clock->restart();
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
            }
        }
        center = application->getLevel()->multiply(sf::Vector2f(application->getPlayer()->getPosition()), application->getLevel()->getUnitSize());
        //report(center);
        window->clear(sf::Color::Black);
        window->setView(sf::View(center, sf::Vector2f(window->getSize())));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            application->act(br::Game::Action::MOVE_LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            application->act(br::Game::Action::MOVE_RIGHT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            application->act(br::Game::Action::MOVE_UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            application->act(br::Game::Action::MOVE_DOWN);
        }
        deltaTime = clock->restart().asSeconds();
        application->update(window, deltaTime);
        window->display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
        }
    }
    delete clock;
    delete window;
    delete application;
    return 0;
}
