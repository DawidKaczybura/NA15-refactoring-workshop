#pragma once
#include <sstream>

namespace Snake
{

struct Position
{
    int x;
    int y;

    bool operator==(Position const& rhs) const { return x == rhs.x and y == rhs.y; }

    static Position readPosition(std::istream& istr)
    {
        Position position;
        istr >> position.x >> position.y;
        return position;
    }
};

} // namespace Snake
