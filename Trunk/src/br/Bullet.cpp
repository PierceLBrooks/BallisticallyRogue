
// Author: Pierce Brooks

#include <br/Bullet.hpp>
#include <br/Game.hpp>
#include <iostream>

br::Bullet::Bullet(Game* owner, const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& velocity, float rotation) :
    sf::Sprite(*texture),
    Ownable<Game*>(),
    velocity(velocity),
    owner(owner)
{
    std::cout << "BULLETING" << this << std::endl;
    setRotation(rotation);
    setPosition(position);
    setOrigin(sf::Vector2f(texture->getSize())*0.5f);
}

br::Bullet::~Bullet()
{
    std::cout << "BULLETED" << this << std::endl;
}

bool br::Bullet::update(sf::RenderWindow* window, float deltaTime)
{
    if (!sf::FloatRect(window->getView().getCenter()-(window->getView().getSize()*0.5f), window->getView().getSize()).contains(getPosition()))
    {
        return false;
    }
    move(velocity*deltaTime);
    window->draw(*this);
    return true;
}

br::Game* br::Bullet::getOwner() const
{
    return owner;
}
