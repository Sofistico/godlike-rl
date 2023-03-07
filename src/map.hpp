#pragma once

struct Tile {
   int x;  // pos x on map
   int y;  // pos y on map
   int z;  // pos z in map
   int cha;  // char of the tile
   bool explored;  // has the player explored this tile?
   bool isWalkable;  // is it walkable?
   bool isTransparent;  // is it transparent?
   TCODColor color;
   Tile(int x, int y, int z, int cha, bool walkable, bool transparent, TCODColor col)
       : explored(false), isWalkable(walkable), isTransparent(transparent) {
      x = x;
      y = y;
      z = z;
      cha = cha;
      color = col;
   }
};

class Map {
  public:
   int height, width;  // the width and height
   int depth;  // z level of the map
  private:
   Tile *tiles;

   TCODMap internalMap;
};
