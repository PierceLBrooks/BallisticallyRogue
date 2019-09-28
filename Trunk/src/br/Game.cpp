
// Author: Pierce Brooks

#include <br/Game.hpp>

br::Game::Game()
{
    dungeon = new Dungeon(sf::Vector2u(500, 500), 0);
}

br::Game::~Game()
{
    delete dungeon;
}

void br::Game::update(sf::RenderWindow* window, float deltaTime)
{

}
