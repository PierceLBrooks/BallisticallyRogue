
// Author: Pierce Brooks

#include <oublietteer/Room.hpp>
#include <br/Player.hpp>
#include <br/Game.hpp>
#include <iostream>

br::Player::Player(Game* owner, const sf::Vector2u& position) :
    Ownable(),
    owner(owner),
    position(position)
{
    isActing = false;
}

br::Player::~Player()
{

}

void br::Player::act()
{
    isActing = false;
}

void br::Player::move(const sf::Vector2i& movement)
{
    if (isActing)
    {
        return;
    }
    sf::Vector2i position = sf::Vector2i(this->position);
    position += movement;
    if ((position.x >= 0) && (position.y >= 0) && (position.x < owner->getRoom()->getSize().x) && (position.y < owner->getRoom()->getSize().y))
    {
        if (owner->getLevel()->getUnit(sf::Vector2u(position))->getType() == Grid::Unit::Type::WALL)
        {
            return;
        }
        if ((this->position.x == 0) || (this->position.y == 0) || (this->position.x == owner->getRoom()->getSize().x-1) || (this->position.y == owner->getRoom()->getSize().y-1))
        {
            owner->getLevel()->getUnit(this->position)->setType(Grid::Unit::Type::DOOR);
        }
        else
        {
            owner->getLevel()->getUnit(this->position)->setType(Grid::Unit::Type::EMPTY);
        }
        this->position = sf::Vector2u(position);
        if (owner->getLevel()->getUnit(this->position)->getType() == Grid::Unit::Type::DOOR)
        {
            oublietteer::Room* room = owner->getRoom();
            for (unsigned int i = 0; i != room->getNeighborCount(); ++i)
            {
                if (std::get<1>(room->getNeighbor(i)) == this->position)
                {
                    oublietteer::Room* neighbor = std::get<0>(room->getNeighbor(i));
                    for (unsigned int j = 0; j != neighbor->getNeighborCount(); ++j)
                    {
                        if (std::get<0>(neighbor->getNeighbor(j)) == room)
                        {
                            this->position = std::get<1>(neighbor->getNeighbor(j));
                            break;
                        }
                    }
                    owner->go(neighbor);
                    break;
                }
            }
            return;
        }
        if (owner->getLevel()->getUnit(this->position)->getType() == Grid::Unit::Type::STAIRS)
        {
            oublietteer::Room* room = owner->getRoom();
            sf::Vector2u stairs = this->position;
            if ((room->getIndex()%2 != 0) || (owner->getFloor()->getIdentifier() == 0))
            {
                owner->moveFloor(1);
            }
            else
            {
                owner->moveFloor(-1);
            }
            room = owner->getFloor()->getRoom(0);
            owner->go(room);
            this->position = sf::Vector2u(sf::Vector2f(room->getSize())*0.5f);
            while ((owner->getLevel()->getUnit(this->position)->getType() != Grid::Unit::Type::EMPTY) || (owner->getLevel()->distance(sf::Vector2f(this->position), sf::Vector2f(stairs)) < 5.0f))
            {
                ++this->position.x;
                ++this->position.y;
            }
            owner->getLevel()->getUnit(this->position)->setType(Grid::Unit::Type::PLAYER);
            return;
        }
        owner->getLevel()->getUnit(this->position)->setType(Grid::Unit::Type::PLAYER);
        isActing = true;
    }
}

br::Game* br::Player::getOwner() const
{
    return owner;
}

const sf::Vector2u& br::Player::getPosition() const
{
    return position;
}

void br::Player::setPosition(const sf::Vector2u& position)
{
    this->position = position;
}
