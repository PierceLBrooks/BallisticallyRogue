
// Author: Pierce Brooks

#include <SFML/Window/Mouse.hpp>
#include <br/BallisticallyRogue.hpp>
#include <br/Game.hpp>
#include <iostream>

#define ROOM_COUNT 25
#define TURN_TIME 0.25f
#define PI (22.0f/7.0f)

br::Game::Game(const sf::Vector2u& size)
{
    bulletTexture = new sf::Texture();
    enemyTexture = new sf::Texture();
    bulletTexture->loadFromFile("./Assets/bullet.png");
    enemyTexture->loadFromFile("./Assets/enemy.png");
    pi = PI;
    window = nullptr;
    dungeon = new Dungeon(sf::Vector2u(500, 500), 0);
    grid = new Grid(this, size);
    score = 0;
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
    for (unsigned int i = 0; i != bullets.size(); ++i)
    {
        delete bullets[i];
    }
    bullets.clear();
    for (unsigned int i = 0; i != enemies.size(); ++i)
    {
        delete enemies[i];
    }
    enemies.clear();
    delete bulletTexture;
    delete enemyTexture;
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
    case SHOOT:
        return shoot();
    }
    return false;
}

bool br::Game::shoot()
{
    if (window == nullptr)
    {
        return false;
    }
    if (player->shoot())
    {
        sf::Color color = level->invert(getFloorColor());
        sf::Vector2f position = level->multiply(sf::Vector2f(player->getPosition()), level->getUnitSize());
        sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window))+(window->getView().getCenter()-(window->getView().getSize()*0.5f));
        float direction = level->direction(position, mouse);
        color.a = 255;
        bullets.push_back(new Bullet(this, bulletTexture, position, sf::Vector2f(cosf(direction), sinf(direction))*level->distance(position, mouse), direction*(180.0f/pi)));
        bullets.back()->setColor(color);
        return true;
    }
    return false;
}

bool br::Game::moveLeft()
{
    return movePlayer(sf::Vector2i(-1, 0));
}

bool br::Game::moveRight()
{
    return movePlayer(sf::Vector2i(1, 0));
}

bool br::Game::moveDown()
{
    return movePlayer(sf::Vector2i(0, 1));
}

bool br::Game::moveUp()
{
    return movePlayer(sf::Vector2i(0, -1));
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
    for (unsigned int i = 0; i != bullets.size(); ++i)
    {
        delete bullets[i];
    }
    bullets.clear();
    for (unsigned int i = 0; i != enemies.size(); ++i)
    {
        delete enemies[i];
    }
    enemies.clear();
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
            if (level->getUnit(sf::Vector2u(x, y))->getType() == Grid::Unit::Type::EMPTY)
            {
                if (BallisticallyRogue::getRandom()->getBool(0.01f))
                {
                    enemies.push_back(new Enemy(this, enemyTexture, sf::Vector2u(x, y)));
                }
            }
        }
    }
}

void br::Game::update(sf::RenderWindow* window, float deltaTime, bool mapView)
{
    this->window = window;
    turn += deltaTime;
    while (turn >= TURN_TIME)
    {
        turn -= TURN_TIME;
        player->act(TURN_TIME);
    }
    level->update(window, deltaTime*pi);
    for (int i = 0; i != bullets.size(); ++i)
    {
        if (!bullets[i]->update(window, deltaTime))
        {
            delete bullets[i];
            bullets.erase(bullets.begin()+i);
            --i;
            continue;
        }
        for (int j = 0; j != enemies.size(); ++j)
        {
            if (bullets[i]->getGlobalBounds().intersects(enemies[j]->getSprite()->getGlobalBounds()))
            {
                ++score;
                delete enemies[j];
                enemies.erase(enemies.begin()+j);
                delete bullets[i];
                bullets.erase(bullets.begin()+i);
                --i;
                break;
            }
        }
    }
    for (int i = 0; i != enemies.size(); ++i)
    {
        if (!enemies[i]->update(window, deltaTime, level->getUnitSize()))
        {
            delete enemies[i];
            enemies.erase(enemies.begin()+i);
            --i;
            continue;
        }
    }
    mapSprite->setPosition(window->getView().getCenter()-((window->getView().getSize()*0.5f)));
    if (mapView)
    {
        mapSprite->setScale(sf::Vector2f(2.0f, 2.0f));
    }
    else
    {
        mapSprite->setScale(sf::Vector2f(1.0f, 1.0f));
    }
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
