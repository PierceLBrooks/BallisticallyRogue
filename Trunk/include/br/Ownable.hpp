
// Author: Pierce Brooks

#ifndef BR_OWNABLE_HPP
#define BR_OWNABLE_HPP

namespace br
{
    template <typename T>
    class Ownable
    {
        public:
            Ownable() {};
            virtual ~Ownable() {};
            virtual T getOwner() const = 0;
    };
}

#endif // BR_OWNABLE_HPP

