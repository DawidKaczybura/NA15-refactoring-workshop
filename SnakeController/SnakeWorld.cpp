#include "SnakeWorld.hpp"

namespace Snake
{

World::World(SnakeDimension dimension, FoodPosition food)
    : m_foodPosition(food),
      m_dimension(dimension)
{}

void World::setFoodPosition(std::pair<int, int> position)
{
    m_foodPosition.setPosition(position);
}

FoodPosition World::getFoodPosition() const
{
    return m_foodPosition;
}

bool World::contains(Position position) const
{
    return position.x >= 0 
    and position.x < m_dimension.width 
    and position.y >= 0 and position.y < m_dimension.height;
}

} // namespace Snake
