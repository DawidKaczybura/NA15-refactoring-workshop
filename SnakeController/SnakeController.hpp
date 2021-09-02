#pragma once

#include <list>
#include <memory>
#include <functional>
#include <stdexcept>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

#include "Segment.hpp"
//#include "Segments.hpp"



class Event;
class IPort;

namespace Snake
{
struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class World
{
public:
    World(IPort& m_displayPort):m_displayPort(m_displayPort){};
    void setMapDimension(std::pair<int, int> m_mapDimension);
    void setFoodPosition(std::pair<int,int> m_foodPosition);
    std::pair<int, int> getFoodPosition();
    bool isPositionOutsideMap(int x, int y) const;
    void sendClearOldFood();
    
private:
    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
    IPort& m_displayPort;
};

class Segments
{
public:
    Segments(IPort& m_displayPort, IPort& m_foodPort, IPort& m_scorePort)
        : m_displayPort(m_displayPort), m_foodPort(m_foodPort), m_scorePort(m_scorePort){};
    Direction m_currentDirection;
    std::list<Segment> m_segments;
    bool isSegmentAtPosition(int x, int y) const;
    Segment calculateNewHead() const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead, World &world);
    void addHeadSegment(Segment const& newHead);
    void removeTailSegmentIfNotScored(Segment const& newHead, std::pair<int, int> const& m_foodPosition);
    void removeTailSegment();
private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
};

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    Segments segments = Segments(m_displayPort, m_foodPort, m_scorePort);
    World world = World(m_displayPort);
    

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>, World world);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    //void sendClearOldFood();
    void sendPlaceNewFood(int x, int y);

    bool m_paused;
};

} // namespace Snake
