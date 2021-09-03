#pragma once

#include <sstream>
#include "SnakePosition.hpp"

namespace Snake
{

struct Dimension
{
    int width;
    int height;

    bool isInside(Position position) const
    {
        return positiveLessThan(position.x, width)
            and positiveLessThan(position.y, height);
    }

    static Dimension readWorldDimension(std::istream& istr)
    {
        Dimension dimension;
        istr >> dimension.width >> dimension.height;
        return dimension;
    }

private:
    bool positiveLessThan(int value, int max) const
    {
        return 0 <= value and value < max;
    }
};

} // namespace Snake
