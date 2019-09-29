
// Author: Pierce Brooks

#ifndef BR_PLAYER_HPP
#define BR_PLAYER_HPP

#include <br/Ownable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace br
{
    class Game;

    class Player : public Ownable<Game*>
    {
        public:
            Player(Game* owner, const sf::Vector2u& position);
            virtual ~Player();
            bool shoot();
            void act(float deltaTime);
            void move(const sf::Vector2i& movement);
            Game* getOwner() const;
            sf::Sprite* getSprite() const;
            const sf::Vector2u& getPosition() const;
            void setPosition(const sf::Vector2u& position);
        private:
            Game* owner;
            sf::Texture* texture;
            sf::Sprite* sprite;
            sf::Vector2u position;
            bool isActing;
            float turn;
    };
}

#endif // BR_PLAYER_HPP
