
// Author: Pierce Brooks

#include <br/BallisticallyRogue.hpp>
#include <br/Game.hpp>
#include <iostream>

#define ROOM_COUNT 25
#define TURN_TIME 0.25f
#define PI (22.0f/7.0f)

br::Game::Game(const sf::Vector2u& size)
{
    dungeon = new Dungeon(sf::Vector2u(500, 500), 0);
    grid = new Grid(this, size);
    floor = 0;
    room = 0;
    moveFloor(0);
    level = nullptr;
    go(getRoom());
    player = new Player(this, sf::Vector2u(1, 1));
    level->getUnit(player->getPosition())->setType(Grid::Unit::Type::PLAYER);
    turn = 0.0f;
}

br::Game::~Game()
{
    delete mapTexture;
    delete mapSprite;
    delete mapImage;
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
    movePlayer(sf::Vector2i(-1, 0));
    return true;
}

bool br::Game::moveRight()
{
    movePlayer(sf::Vector2i(1, 0));
    return true;
}

bool br::Game::moveDown()
{
    movePlayer(sf::Vector2i(0, 1));
    return true;
}

bool br::Game::moveUp()
{
    movePlayer(sf::Vector2i(0, -1));
    return true;
}

bool br::Game::movePlayer(const sf::Vector2i& movement)
{
    player->move(movement);
    return true;
}

bool br::Game::moveFloor(int direction)
{
    floor += direction;
    if (dungeon->createFloor(floor))
    {
        for (unsigned int i = 0; i != ROOM_COUNT; ++i)
        {
            //std::cout << i << std::endl;
            getFloor()->addRoom(false);
        }
    }
    std::cout << floor << std::endl;
    delete mapSprite;
    delete mapTexture;
    delete mapImage;
    mapImage = getFloor()->getImage();
    mapTexture = new sf::Texture();
    mapTexture->loadFromImage(*mapImage);
    mapSprite = new sf::Sprite(*mapTexture);
    //mapSprite->setOrigin(sf::Vector2f(mapImage->getSize())*0.5f);
    return true;
}

void br::Game::go(oublietteer::Room* room)
{
    if (room == nullptr)
    {
        return;
    }
    for (unsigned int i = 0; i != getFloor()->getRoomCount(); ++i)
    {
        if (getFloor()->getRoom(i) == room)
        {
            std::cout << i << std::endl;
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
            if (sf::Vector2u(x, y) == sf::Vector2u(sf::Vector2f(room->getSize())*0.5f))
            {
                if ((this->room == 0) || (this->room%2 != 0))
                {
                    level->getUnit(sf::Vector2u(x, y))->setType(Grid::Unit::Type::STAIRS);
                    continue;
                }
            }
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
    mapSprite->setPosition(window->getView().getCenter()-((window->getView().getSize()*0.5f)));
    window->draw(*mapSprite);
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

sf::Color br::Game::getFloorColor() const
{
    switch (floor%6)
    {
    case 0:
        return sf::Color::Red;
    case 1:
        return sf::Color::Green;
    case 2:
        return sf::Color::Blue;
    case 3:
        return sf::Color::Yellow;
    case 4:
        return sf::Color::Magenta;
    case 5:
        return sf::Color::Cyan;
    }
    return sf::Color::White;
}
