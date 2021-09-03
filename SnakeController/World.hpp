#pragma once


#include "SnakeInterface.hpp"
#include "IPort.hpp"
#include <memory>
#include <functional>


class World
{
public:
    World(IPort& m_displayPort, IPort& m_foodPort)
        :m_displayPort(m_displayPort), m_foodPort(m_foodPort){};

    void setMapDimension(std::pair<int, int> m_mapDimension);
    void setFoodPosition(std::pair<int,int> m_foodPosition);
    std::pair<int, int> getFoodPosition();

    bool isPositionOutsideMap(int x, int y) const;
    void sendClearOldFood();
    
    void sendPlaceNewFood(int x, int y);
    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy, bool isSegmentAtPosition);
    
private:

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
    IPort& m_displayPort;
    IPort& m_foodPort;
};