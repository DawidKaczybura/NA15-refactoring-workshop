#pragma once

#include <utility>
#include "SnakeDimension.hpp"
#include "SnakePosition.hpp"


namespace Snake
{

class World
{
public:
    World(SnakeDimension dimension, Position foodPosition);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

private:
    Position m_foodPosition;
    SnakeDimension m_dimension;
};

} // namespace Snake
