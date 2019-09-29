
// Author: Pierce Brooks

#include <br/BallisticallyRogue.hpp>

br::BallisticallyRogue::BallisticallyRogue() :
    Game(sf::Vector2u(75, 45))
{

}

br::BallisticallyRogue::~BallisticallyRogue()
{
    delete random;
    random = nullptr;
}

oublietteer::Random* br::BallisticallyRogue::getRandom()
{
    if (random == nullptr)
    {
        random = new oublietteer::Random();
    }
    return random;
}

oublietteer::Random* br::BallisticallyRogue::random = nullptr;
