
// Author: Pierce Brooks

#include <br/Grid.hpp>
#include <br/Game.hpp>
#include <iostream>

br::Grid::Unit::Unit(Grid* owner, const sf::Vector2u& position) :
    Ownable<Grid*>(),
    owner(owner),
    position(position),
    type(INVALID)
{
    shape = nullptr;
}

br::Grid::Unit::~Unit()
{
    delete shape;
}

void br::Grid::Unit::update(sf::RenderWindow* window, float deltaTime)
{
    if (shape == nullptr)
    {
        return;
    }
    shape->rotate(deltaTime);
    shape->setPosition(owner->multiply(sf::Vector2f(position), shape->getSize()));
    window->draw(*shape);
    if (type == PLAYER)
    {
        sf::Sprite* player = owner->getOwner()->getPlayer()->getSprite();
        player->setScale(shape->getSize().x/static_cast<float>(player->getTexture()->getSize().x), shape->getSize().y/static_cast<float>(player->getTexture()->getSize().y));
        player->setPosition(shape->getPosition());
        window->draw(*player);
    }
}

const sf::Vector2u& br::Grid::Unit::getPosition() const
{
    return position;
}

br::Grid* br::Grid::Unit::getOwner() const
{
    return owner;
}

br::Grid::Unit::Type br::Grid::Unit::getType() const
{
    return type;
}

void br::Grid::Unit::setType(Type type)
{
    if (this->type == INVALID)
    {
        delete shape;
        shape = nullptr;
        if (type != INVALID)
        {
            shape = new sf::RectangleShape();
            shape->setSize(owner->getUnitSize());
            shape->setOrigin(owner->getUnitSize()*0.5f);
        }
    }
    this->type = type;
    if (shape == nullptr)
    {
        return;
    }
    shape->setRotation(0.0f);
    if (type == EMPTY)
    {
        setColor(sf::Color::White);
        return;
    }
    if (type == WALL)
    {
        setColor(sf::Color(192, 192, 192));
        return;
    }
    if (type == DOOR)
    {
        setColor(sf::Color(64, 64, 64));
        return;
    }
    if (type == PLAYER)
    {
        setColor(sf::Color(0, 128, 0));
        return;
    }
    if (type == STAIRS)
    {
        setColor(sf::Color::Black);
        return;
    }
}

void br::Grid::Unit::setColor(const sf::Color& color)
{
    if (type == PLAYER)
    {
        shape->setFillColor(color);
        return;
    }
    shape->setFillColor(owner->multiply(color, owner->getOwner()->getFloorColor()));
}

br::Grid::Grid(Game* owner, const sf::Vector2u& size) :
    sf::Transformable(),
    Ownable<Game*>(),
    owner(owner),
    size(size)
{
    unitSize = sf::Vector2f(32.0f, 32.0f);
    for (unsigned int x = 0; x != size.x; ++x)
    {
        units.push_back(std::vector<Unit*>());
        for (unsigned int y = 0; y != size.y; ++y)
        {
            units[x].push_back(new Unit(this, sf::Vector2u(x, y)));
        }
    }
}

br::Grid::~Grid()
{
    for (unsigned int x = 0; x != size.x; ++x)
    {
        for (unsigned int y = 0; y != size.y; ++y)
        {
            delete units[x][y];
        }
        units[x].clear();
    }
    units.clear();
}

float br::Grid::magnitude(const sf::Vector2f& target)
{
    return sqrtf(powf(target.x, 2.0f)+powf(target.y, 2.0f));
}

float br::Grid::distance(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sqrtf(powf(left.x-right.x, 2.0f)+powf(left.y-right.y, 2.0f));
}

float br::Grid::direction(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return atan2f(right.y-left.y, right.x-left.x);
}

sf::Vector2f br::Grid::multiply(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x*right.x, left.y*right.y);
}

sf::Vector2f br::Grid::divide(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x/right.x, left.y/right.y);
}

sf::Color br::Grid::multiply(const sf::Color& left, const sf::Color& right)
{
    return sf::Color(static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.r)/255.0f)*(static_cast<float>(right.r)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.g)/255.0f)*(static_cast<float>(right.g)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.b)/255.0f)*(static_cast<float>(right.b)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.a)/255.0f)*(static_cast<float>(right.a)/255.0f))));
}

sf::Color br::Grid::divide(const sf::Color& left, const sf::Color& right)
{
    return sf::Color(static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.r)/255.0f)/(static_cast<float>(right.r)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.g)/255.0f)/(static_cast<float>(right.g)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.b)/255.0f)/(static_cast<float>(right.b)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*((static_cast<float>(left.a)/255.0f)/(static_cast<float>(right.a)/255.0f))));
}

sf::Color br::Grid::blend(const sf::Color& left, const sf::Color& right)
{
    return sf::Color(static_cast<sf::Uint8>(255.0f*(1.0f-((1.0f-(static_cast<float>(left.r)/255.0f))*(1.0f-(static_cast<float>(right.r)/255.0f))))),
                     static_cast<sf::Uint8>(255.0f*(1.0f-((1.0f-(static_cast<float>(left.g)/255.0f))*(1.0f-(static_cast<float>(right.g)/255.0f))))),
                     static_cast<sf::Uint8>(255.0f*(1.0f-((1.0f-(static_cast<float>(left.b)/255.0f))*(1.0f-(static_cast<float>(right.b)/255.0f))))),
                     static_cast<sf::Uint8>(255.0f*(1.0f-((1.0f-(static_cast<float>(left.a)/255.0f))*(1.0f-(static_cast<float>(right.a)/255.0f))))));
}

sf::Color br::Grid::invert(const sf::Color& target)
{
    return sf::Color(static_cast<sf::Uint8>(255.0f*(1.0f-(static_cast<float>(target.r)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*(1.0f-(static_cast<float>(target.g)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*(1.0f-(static_cast<float>(target.b)/255.0f))),
                     static_cast<sf::Uint8>(255.0f*(1.0f-(static_cast<float>(target.a)/255.0f))));
}

void br::Grid::update(sf::RenderWindow* window, float deltaTime)
{
    for (unsigned int x = 0; x != size.x; ++x)
    {
        for (unsigned int y = 0; y != size.y; ++y)
        {
            units[x][y]->update(window, deltaTime);
        }
    }
}

br::Grid::Unit* br::Grid::getUnit(const sf::Vector2u& position) const
{
    return units[position.x][position.y];
}

br::Game* br::Grid::getOwner() const
{
    return owner;
}

const sf::Vector2u& br::Grid::getSize() const
{
    return size;
}

const sf::Vector2f& br::Grid::getUnitSize() const
{
    return unitSize;
}
