
// Author: Pierce Brooks

#ifndef BR_GRID_HPP
#define BR_GRID_HPP

#include <br/Ownable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace br
{
    class Game;

    class Grid : public sf::Transformable, Ownable<Game*>
    {
        public:
            class Unit : public Ownable<Grid*>
            {
                public:
                    enum Type
                    {
                        INVALID,
                        EMPTY,
                        PLAYER,
                        WALL,
                        DOOR,
                        ENEMY,
                        TYPE_SENTINEL
                    };
                    Unit(Grid* owner, const sf::Vector2u& position);
                    virtual ~Unit();
                    void update(sf::RenderWindow* window, float deltaTime);
                    const sf::Vector2u& getPosition() const;
                    Grid* getOwner() const;
                    Type getType() const;
                    void setType(Type type);
                private:
                    friend Grid;
                    Type type;
                    sf::Vector2u position;
                    sf::RectangleShape* shape;
                    Grid* owner;
            };
            Grid(Game* owner, const sf::Vector2u& size);
            virtual ~Grid();
            static sf::Vector2f multiply(const sf::Vector2f& left, const sf::Vector2f& right);
            static sf::Vector2f divide(const sf::Vector2f& left, const sf::Vector2f& right);
            void update(sf::RenderWindow* window, float deltaTime);
            Unit* getUnit(const sf::Vector2u& position) const;
            Game* getOwner() const;
            const sf::Vector2u& getSize() const;
        private:
            friend Unit;
            const sf::Vector2f& getUnitSize() const;
            std::vector<std::vector<Unit*>> units;
            sf::Vector2u size;
            sf::Vector2f unitSize;
            Game* owner;
    };
}

#endif // BR_GRID_HPP
