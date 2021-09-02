#pragma once

#include <list>

#include "Segment.hpp"



class Segments
{
private:
    

public:
    std::list<Segment> m_segments;
    bool isSegmentAtPosition(int x, int y) const;
};


