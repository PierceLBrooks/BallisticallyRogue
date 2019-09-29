
// Author: Pierce Brooks

#ifndef BR_PLAYER_HPP
#define BR_PLAYER_HPP

#include <br/Ownable.hpp>
#include <SFML/System/Vector2.hpp>

namespace br
{
    class Game;

    class Player : public Ownable<Game*>
    {
        public:
            Player(Game* owner, const sf::Vector2u& position);
            virtual ~Player();
            void act();
            void move(const sf::Vector2i& movement);
            Game* getOwner() const;
            const sf::Vector2u& getPosition() const;
            void setPosition(const sf::Vector2u& position);
        private:
            Game* owner;
            sf::Vector2u position;
            bool isActing;
    };
}

#endif // BR_PLAYER_HPP
