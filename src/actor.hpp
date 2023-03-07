#pragma once
#include <libtcod.hpp>

class actor {
 public:
  int x, y, z;  // pos on map
  int ch;  // char of the actor
  TCODColor color;
};
