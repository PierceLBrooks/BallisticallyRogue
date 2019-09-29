
// Author: Pierce Brooks

#include <br/Grid.hpp>
#include <br/Game.hpp>

br::Grid::Unit::Unit(Grid* owner, const sf::Vector2u& position) :
    Ownable(),
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
    shape->move(window->getView().getCenter());
    shape->move(-owner->multiply(sf::Vector2f(owner->getOwner()->getPlayer()->getPosition()), shape->getSize()));
    window->draw(*shape);
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
        shape->setFillColor(sf::Color::White);
        return;
    }
    if (type == WALL)
    {
        shape->setFillColor(sf::Color(192, 192, 192));
        return;
    }
    if (type == DOOR)
    {
        shape->setFillColor(sf::Color(64, 64, 64));
        return;
    }
    if (type == PLAYER)
    {
        shape->setFillColor(sf::Color(0, 128, 0));
        return;
    }
}

br::Grid::Grid(Game* owner, const sf::Vector2u& size) :
    sf::Transformable(),
    Ownable(),
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

sf::Vector2f br::Grid::multiply(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x*right.x, left.y*right.y);
}

sf::Vector2f br::Grid::divide(const sf::Vector2f& left, const sf::Vector2f& right)
{
    return sf::Vector2f(left.x/right.x, left.y/right.y);
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
