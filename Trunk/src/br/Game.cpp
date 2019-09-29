
// Author: Pierce Brooks

#include <br/Game.hpp>
#include <iostream>

#define TURN_TIME 0.025f
#define PI (22.0f/7.0f)

br::Game::Game(const sf::Vector2u& size)
{
    dungeon = new Dungeon(sf::Vector2u(500, 500), 0);
    grid = new Grid(this, size);
    dungeon->createFloor(0);
    floor = 0;
    room = 0;
    for (unsigned int i = 0; i != 50; ++i)
    {
        getFloor()->addRoom(false);
    }
    level = nullptr;
    go(getRoom());
    player = new Player(this, sf::Vector2u(1, 1));
    level->getUnit(player->getPosition())->setType(Grid::Unit::Type::PLAYER);
    turn = 0.0f;
}

br::Game::~Game()
{
    sf::Image* image = getFloor()->getImage();
    image->saveToFile("./br.png");
    delete image;
    delete grid;
    delete level;
    delete dungeon;
    delete player;
}

bool br::Game::act(Action action)
{
    switch (action)
    {
    case MOVE_LEFT:
        return moveLeft();
    case MOVE_RIGHT:
        return moveRight();
    case MOVE_UP:
        return moveUp();
    case MOVE_DOWN:
        return moveDown();
    }
    return false;
}

bool br::Game::moveLeft()
{
    player->move(sf::Vector2i(-1, 0));
    return true;
}

bool br::Game::moveRight()
{
    player->move(sf::Vector2i(1, 0));
    return true;
}

bool br::Game::moveDown()
{
    player->move(sf::Vector2i(0, 1));
    return true;
}

bool br::Game::moveUp()
{
    player->move(sf::Vector2i(0, -1));
    return true;
}

void br::Game::go(oublietteer::Room* room)
{
    std::cout << getRoom() << " -> " << room << std::endl;
    if (room == nullptr)
    {
        return;
    }
    for (unsigned int i = 0; i != getFloor()->getRoomCount(); ++i)
    {
        if (getFloor()->getRoom(i) == room)
        {
            this->room = i;
            break;
        }
    }
    if (level != nullptr)
    {
        delete level;
    }
    level = new Grid(this, room->getSize());
    for (unsigned int x = 0; x != room->getSize().x; ++x)
    {
        for (unsigned int y = 0; y != room->getSize().y; ++y)
        {
            if ((x == 0) || (y == 0) || (x == room->getSize().x-1) || (y == room->getSize().y-1))
            {
                level->getUnit(sf::Vector2u(x, y))->setType(Grid::Unit::Type::WALL);
            }
            else
            {
                level->getUnit(sf::Vector2u(x, y))->setType(Grid::Unit::Type::EMPTY);
            }
            for (unsigned int i = 0; i != room->getNeighborCount(); ++i)
            {
                if (std::get<1>(room->getNeighbor(i)) == sf::Vector2u(x, y))
                {
                    level->getUnit(sf::Vector2u(x, y))->setType(Grid::Unit::Type::DOOR);
                }
            }
        }
    }
}

void br::Game::update(sf::RenderWindow* window, float deltaTime)
{
    turn += deltaTime;
    while (turn >= TURN_TIME)
    {
        turn -= TURN_TIME;
        player->act();
    }
    level->update(window, deltaTime*PI);
}

oublietteer::Floor* br::Game::getFloor() const
{
    return dungeon->getFloor(floor);
}

oublietteer::Room* br::Game::getRoom() const
{
    return getFloor()->getRoom(room);
}

br::Player* br::Game::getPlayer() const
{
    return player;
}

br::Grid* br::Game::getLevel() const
{
    return level;
}
