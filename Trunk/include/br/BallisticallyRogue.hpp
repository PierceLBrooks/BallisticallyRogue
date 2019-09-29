
// Author: Pierce Brooks

#ifndef BR_HPP
#define BR_HPP

#include <br/Game.hpp>

namespace br
{
    class BallisticallyRogue : public Game
    {
        public:
            BallisticallyRogue();
            virtual ~BallisticallyRogue();
            static oublietteer::Random* getRandom();
        private:
            static oublietteer::Random* random;
    };
}

#endif // BR_HPP
