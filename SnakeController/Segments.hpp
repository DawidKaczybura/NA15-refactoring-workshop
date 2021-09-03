#pragma once

#include <memory>
#include <list>


#include "World.hpp"
#include "Segment.hpp"
#include "IPort.hpp"

class Segments
{
public:
    Segments(IPort& m_displayPort, IPort& m_foodPort, IPort& m_scorePort)
        : m_displayPort(m_displayPort), m_foodPort(m_foodPort), m_scorePort(m_scorePort){};
    
    std::list<Segment> m_segments;
    bool isSegmentAtPosition(int x, int y) const;
    Segment calculateNewHead() const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead, World &world);
    void addHeadSegment(Segment const& newHead);
    void removeTailSegmentIfNotScored(Segment const& newHead, std::pair<int, int> const& m_foodPosition);
    void removeTailSegment();
    Snake::Direction getCurrentDirection();
    void setCurrentDirection(Snake::Direction newDirection);

private:
    Snake::Direction m_currentDirection;
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
};