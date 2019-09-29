
// Author: Pierce Brooks

#ifndef BR_GAME_HPP
#define BR_GAME_HPP

#include <vector>
#include <br/Grid.hpp>
#include <br/Player.hpp>
#include <br/Bullet.hpp>
#include <br/Enemy.hpp>
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
                MOVE_DOWN,
                SHOOT
            };
            Game(const sf::Vector2u& size);
            virtual ~Game();
            bool act(Action action);
            bool shoot();
            bool moveLeft();
            bool moveRight();
            bool moveUp();
            bool moveDown();
            bool movePlayer(const sf::Vector2i& movement);
            bool moveFloor(int direction);
            void go(oublietteer::Room* room);
            void update(sf::RenderWindow* window, float deltaTime, bool mapView);
            oublietteer::Floor* getFloor() const;
            oublietteer::Room* getRoom() const;
            Player* getPlayer() const;
            Grid* getLevel() const;
            sf::Color getFloorColor() const;
            sf::Vector2f getPlayerPosition() const;
        protected:
            float pi;
            float turn;
            int floor;
            unsigned int room;
            unsigned int score;
            Dungeon* dungeon;
            Grid* grid;
            Grid* level;
            Player* player;
            std::vector<Bullet*> bullets;
            std::vector<Enemy*> enemies;
            sf::Texture* bulletTexture;
            sf::Texture* enemyTexture;
            sf::Texture* mapTexture;
            sf::Sprite* mapSprite;
            sf::Image* mapImage;
            sf::RenderWindow* window;
    };
}

#endif // BR_GAME_HPP
