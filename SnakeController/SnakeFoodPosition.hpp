#pragma once

namespace Snake
{

struct FoodPosition
{
    int x;
    int y;
    void setPosition(std::pair<int, int> position){
        x = position.first;
        y = position.second;
    }
    bool operator==(FoodPosition const& rhs) const { return x == rhs.x and y == rhs.y; }
};

} // namespace Snake