#pragma once
#include <libtcod.hpp>

#include "point.hpp"

class Actor {
  public:
   Point pos;  // pos on map
   int ch;  // char of the actor
   tcod::ColorRGB fg;
   tcod::ColorRGB bg;
   Actor(int x, int y, int ch, tcod::ColorRGB fg, tcod::ColorRGB bg);

   TCOD_ConsoleTile getConsoleTile() const;
   void render(tcod::Console &console) const;
};
