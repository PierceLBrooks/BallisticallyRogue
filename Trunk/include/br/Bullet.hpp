
// Author: Pierce Brooks

#ifndef BR_BULLET_HPP
#define BR_BULLET_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <br/Ownable.hpp>

namespace br
{
    class Game;

    class Bullet : public sf::Sprite, Ownable<Game*>
    {
        public:
            Bullet(Game* owner, const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& velocity, float rotation);
            virtual ~Bullet();
            bool update(sf::RenderWindow* window, float deltaTime);
            Game* getOwner() const;
        private:
            sf::Vector2f velocity;
            Game* owner;
    };
}

#endif // BR_BULLET_HPP
