#pragma once

#include <utility>
#include "SnakeDimension.hpp"
#include "SnakeFoodPosition.hpp"
#include "SnakePosition.hpp"


namespace Snake
{

class World
{
public:
    //World(SnakeDimension dimension, std::pair<int, int> food);
    World(SnakeDimension dimension, FoodPosition food);

    void setFoodPosition(std::pair<int, int> position);
    FoodPosition getFoodPosition() const;

    bool contains(Position position) const;

private:
    FoodPosition m_foodPosition;
    SnakeDimension m_dimension;
};

} // namespace Snake
