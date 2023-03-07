#pragma once

struct tile {
  int x;  // pos x on map
  int y;  // pos y on map
  int z;  // pos z in map
  int cha;  // char of the tile
  bool explored;  // has the player explored this tile?
  TCODColor color;
  tile(int x, int y, int z, int cha, TCODColor col) : explored(false) {
    x = x;
    y = y;
    z = z;
    cha = cha;
    color = col;
  }
};
