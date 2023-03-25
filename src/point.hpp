#pragma once
#include <array>

struct Point {
   // Allow this struct to be used in subscript operators as {x, y}.
   operator const std::array<int, 2>() const noexcept { return {x, y}; }
   Point operator+(const Point rhs) const noexcept { return {this->x + rhs.x, this->y + rhs.y}; }
   Point operator-(const Point rhs) const noexcept { return {this->x - rhs.x, this->y - rhs.y}; }
   bool operator==(const Point rhs) const noexcept { return this->x == rhs.x && this->y == rhs.y; }
   bool operator!=(const Point rhs) const noexcept { return !(*this == rhs); }

   int x, y;

   Point(int x, int y) : x(x), y(y) {}
};

template <>
struct std::hash<Point> {
   std::size_t operator()(const Point &pos) const {
      return static_cast<size_t>(pos.x) + static_cast<size_t>(pos.y) * 97;
   }
};
