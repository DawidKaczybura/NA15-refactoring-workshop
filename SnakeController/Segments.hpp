#include <list>
#include <algorithm>

#include "Segment.hpp"



class Segments
{
private:
    

    
public:

    Segments();
    std::list<Segment> m_segments;
    bool isSegmentAtPosition(int x, int y) const;
};


