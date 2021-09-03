#pragma once

namespace Snake
{

struct SnakeDimension
{
    int width;
    int height;

    bool operator==(SnakeDimension const& rhs) const { return width == rhs.width and height == rhs.height; }
};

} // namespace Snake