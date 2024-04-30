#pragma once
#include <libtcod.hpp>

#include "point.hpp"

class Actor
{
    public:

        Actor( int x, int y, int ch, tcod::ColorRGB fg, tcod::ColorRGB bg ) : pos( {x, y} ), ch( ch ),
        fg( fg ), bg( bg ) {}

        TCOD_ConsoleTile getConsoleTile() const;
        void render( tcod::Console &console ) const;

    private:
        point pos;  // pos on map
        int ch;  // char of the actor
        tcod::ColorRGB fg;
        tcod::ColorRGB bg;
};
