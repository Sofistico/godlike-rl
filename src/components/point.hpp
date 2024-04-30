#pragma once
#include <array>

struct point {
    // Allow this struct to be used in subscript operators as {x, y}.
    operator const std::array<int, 2>() const noexcept {
        return {x, y};
    }
    point operator+( const point rhs ) const noexcept {
        return {this->x + rhs.x, this->y + rhs.y};
    }
    point operator-( const point rhs ) const noexcept {
        return {this->x - rhs.x, this->y - rhs.y};
    }
    bool operator==( const point rhs ) const noexcept {
        return this->x == rhs.x && this->y == rhs.y;
    }
    bool operator!=( const point rhs ) const noexcept {
        return !( *this == rhs );
    }

    int x, y;

    point( int x, int y ) : x( x ), y( y ) {}
};

template <>
struct std::hash<point> {
    std::size_t operator()( const point &pos ) const {
        return static_cast<size_t>( pos.x ) + static_cast<size_t>( pos.y ) * 97;
    }
};
