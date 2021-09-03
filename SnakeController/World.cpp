#include "World.hpp"
#include "IEventHandler.hpp"
#include "EventT.hpp"


void World::setMapDimension(std::pair<int, int> m_mapDimension_){
    m_mapDimension = m_mapDimension_;
}
void World::setFoodPosition(std::pair<int,int> m_foodPosition_){
    m_foodPosition = m_foodPosition_;
}

bool World::isPositionOutsideMap(int x, int y) const
{
    return x < 0 or y < 0 or x >= m_mapDimension.first or y >= m_mapDimension.second;
}

void World::sendPlaceNewFood(int x, int y)
{
    setFoodPosition(std::make_pair(x, y));

    Snake::DisplayInd placeNewFood;
    placeNewFood.x = x;
    placeNewFood.y = y;
    placeNewFood.value = Snake::Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<Snake::DisplayInd>>(placeNewFood));
}

void World::sendClearOldFood()
{
    Snake::DisplayInd clearOldFood;
    clearOldFood.x = m_foodPosition.first;
    clearOldFood.y = m_foodPosition.second;
    clearOldFood.value = Snake::Cell_FREE;

    m_displayPort.send(std::make_unique<EventT<Snake::DisplayInd>>(clearOldFood));
}

std::pair<int, int> World::getFoodPosition(){
    return m_foodPosition;
}

void World::updateFoodPosition(int x, int y, std::function<void()> clearPolicy, bool isSegmentAtPosition)
{
    if (isSegmentAtPosition || isPositionOutsideMap(x,y)) {
        m_foodPort.send(std::make_unique<EventT<Snake::FoodReq>>());
        return;
    }

    clearPolicy();
    sendPlaceNewFood(x, y);
}