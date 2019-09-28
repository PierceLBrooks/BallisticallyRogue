
// Author: Pierce Brooks

#ifndef BR_GAME_HPP
#define BR_GAME_HPP

#include <oublietteer/Oubliette.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

typedef oublietteer::Oubliette Dungeon;

namespace br
{
    class Game
    {
        public:
            Game();
            virtual ~Game();
            void update(sf::RenderWindow* window, float deltaTime);
        protected:
            Dungeon* dungeon;
    };
}

#endif // BR_GAME_HPP
