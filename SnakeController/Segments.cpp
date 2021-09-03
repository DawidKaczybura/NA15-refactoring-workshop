#include "Segments.hpp"

#include "EventT.hpp"

namespace
{
bool isHorizontal(Snake::Direction direction)
{
    return Snake::Direction_LEFT == direction or Snake::Direction_RIGHT == direction;
}

bool isVertical(Snake::Direction direction)
{
    return Snake::Direction_UP == direction or Snake::Direction_DOWN == direction;
}

bool isPositive(Snake::Direction direction)
{
    return (isVertical(direction) and Snake::Direction_DOWN == direction)
        or (isHorizontal(direction) and Snake::Direction_RIGHT == direction);
}

bool perpendicular(Snake::Direction dir1, Snake::Direction dir2)
{
    return isHorizontal(dir1) == isVertical(dir2);
}
} // namespace


bool Segments::isSegmentAtPosition(int x, int y) const
{
    return m_segments.end() !=  std::find_if(m_segments.cbegin(), m_segments.cend(),
        [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
}

Segment Segments::calculateNewHead() const
{
    Segment const& currentHead = m_segments.front();

    Segment newHead;
    newHead.x = currentHead.x + (isHorizontal(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);
    newHead.y = currentHead.y + (isVertical(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);

    return newHead;
}

void Segments::removeTailSegment()
{
    auto tail = m_segments.back();

    Snake::DisplayInd l_evt;
    l_evt.x = tail.x;
    l_evt.y = tail.y;
    l_evt.value = Snake::Cell_FREE;
    m_displayPort.send(std::make_unique<EventT<Snake::DisplayInd>>(l_evt));

    m_segments.pop_back();
}

void Segments::addHeadSegment(Segment const& newHead)
{
    m_segments.push_front(newHead);

    Snake::DisplayInd placeNewHead;
    placeNewHead.x = newHead.x;
    placeNewHead.y = newHead.y;
    placeNewHead.value = Snake::Cell_SNAKE;

    m_displayPort.send(std::make_unique<EventT<Snake::DisplayInd>>(placeNewHead));
}

void Segments::removeTailSegmentIfNotScored(Segment const& newHead, std::pair<int, int> const& m_foodPosition)
{
    if (std::make_pair(newHead.x, newHead.y) == m_foodPosition) {
        m_scorePort.send(std::make_unique<EventT<Snake::ScoreInd>>());
        m_foodPort.send(std::make_unique<EventT<Snake::FoodReq>>());
    } else {
        removeTailSegment();
    }
}

void Segments::updateSegmentsIfSuccessfullMove(Segment const& newHead, World &world)
{
    if (isSegmentAtPosition(newHead.x, newHead.y) or world.isPositionOutsideMap(newHead.x, newHead.y)) {
        m_scorePort.send(std::make_unique<EventT<Snake::LooseInd>>());
    } else {
        addHeadSegment(newHead);
        removeTailSegmentIfNotScored(newHead, world.getFoodPosition());
    }
}