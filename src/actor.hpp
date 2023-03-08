#pragma once
#include <libtcod.hpp>

class Actor {
  public:
   int x, y;  // pos on map
   int ch;  // char of the actor
   TCODColor fg;
   TCODColor bg;
   Actor(int x, int y, int ch, TCODColor fg, TCODColor bg);

   TCOD_ConsoleTile getConsoleTile() const;
};
