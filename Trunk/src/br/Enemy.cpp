
// Author: Pierce Brooks

#include <br/Enemy.hpp>
#include <br/Grid.hpp>
#include <br/Game.hpp>
#include <iostream>

#define MOVE_TIME 0.5f

br::Enemy::Enemy(Game* owner, const sf::Texture* texture, const sf::Vector2u& position) :
    Ownable<Game*>(),
    owner(owner),
    position(position)
{
    std::cout << "ENEMYING" << this << std::endl;
    sprite = new sf::Sprite(*texture);
    turn = 0.0f;
}

br::Enemy::~Enemy()
{
    std::cout << "ENEMIED" << this << std::endl;
}

bool br::Enemy::update(sf::RenderWindow* window, float deltaTime, const sf::Vector2f& scale)
{
    turn += deltaTime;
    while (turn >= MOVE_TIME)
    {
        sf::Vector2u temp = position;
        turn -= MOVE_TIME;
        if (position.x < owner->getPlayer()->getPosition().x)
        {
            ++position.x;
        }
        if (position.x > owner->getPlayer()->getPosition().x)
        {
            --position.x;
        }
        if (position.y < owner->getPlayer()->getPosition().y)
        {
            ++position.y;
        }
        if (position.y > owner->getPlayer()->getPosition().y)
        {
            --position.y;
        }
        if (owner->getLevel()->getUnit(position)->getType() != Grid::Unit::Type::EMPTY)
        {
            position = temp;
        }
    }
    sprite->setScale(scale.x/static_cast<float>(sprite->getTexture()->getSize().x), scale.y/static_cast<float>(sprite->getTexture()->getSize().y));
    sprite->setPosition(static_cast<float>(position.x)*scale.x, static_cast<float>(position.y)*scale.y);
    sprite->move(scale*0.5f);
    window->draw(*sprite);
    return true;
}

br::Game* br::Enemy::getOwner() const
{
    return owner;
}

sf::Sprite* br::Enemy::getSprite() const
{
    return sprite;
}
