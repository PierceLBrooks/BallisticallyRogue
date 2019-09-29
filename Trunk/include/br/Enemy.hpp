
// Author: Pierce Brooks

#ifndef BR_ENEMY_HPP
#define BR_ENEMY_HPP

#include <br/Ownable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace br
{
    class Game;

    class Enemy : public Ownable<Game*>
    {
        public:
            Enemy(Game* owner, const sf::Texture* texture, const sf::Vector2u& position);
            virtual ~Enemy();
            bool update(sf::RenderWindow* window, float deltaTime, const sf::Vector2f& scale);
            Game* getOwner() const;
            sf::Sprite* getSprite() const;
        private:
            float turn;
            Game* owner;
            sf::Sprite* sprite;
            sf::Vector2u position;
    };
}

#endif // BR_BULLET_HPP
