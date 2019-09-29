
// Author: Pierce Brooks

#ifndef BR_GAME_HPP
#define BR_GAME_HPP

#include <vector>
#include <br/Grid.hpp>
#include <br/Player.hpp>
#include <oublietteer/Room.hpp>
#include <oublietteer/Floor.hpp>
#include <oublietteer/Oubliette.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

typedef oublietteer::Oubliette Dungeon;

namespace br
{
    class Game
    {
        public:
            enum Action
            {
                NONE,
                MOVE_LEFT,
                MOVE_RIGHT,
                MOVE_UP,
                MOVE_DOWN
            };
            Game(const sf::Vector2u& size);
            virtual ~Game();
            bool act(Action action);
            bool moveLeft();
            bool moveRight();
            bool moveUp();
            bool moveDown();
            bool movePlayer(const sf::Vector2i& movement);
            bool moveFloor(int direction);
            void go(oublietteer::Room* room);
            void update(sf::RenderWindow* window, float deltaTime);
            oublietteer::Floor* getFloor() const;
            oublietteer::Room* getRoom() const;
            Player* getPlayer() const;
            Grid* getLevel() const;
            sf::Color getFloorColor() const;
        protected:
            float turn;
            int floor;
            unsigned int room;
            Dungeon* dungeon;
            Grid* grid;
            Grid* level;
            Player* player;
            sf::Texture* mapTexture;
            sf::Sprite* mapSprite;
            sf::Image* mapImage;
    };
}

#endif // BR_GAME_HPP
