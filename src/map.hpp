#pragma once
#include <libtcod.hpp>
#include <vector>

struct Tile {
   bool explored;  // has the player explored this tile?
   bool isWalkable;  // is it walkable?
   bool isTransparent;  // is it transparent?
   Tile(bool walkable, bool transparent) : explored(false), isWalkable(walkable), isTransparent(transparent) {}
   Tile() : explored(false), isWalkable(true), isTransparent(true) {}  // defaults to a floor tile type
};

enum struct Tiles { Floor = 0, Wall };

class Map {
  public:
   int height, width;  // the width and height

   inline bool isTransparent(int x, int y) const;
   bool isInFov(int x, int y) const;
   inline bool isExplored(int x, int y) const;
   inline bool isWalkable(int x, int y) const;

   void render(tcod::Console &console) const;
   void computeFov();
   void addEntity(int x, int y);

   Map(int height, int width);
   ~Map();

  private:
   Tile *tiles;
   TCODMap *internalMap;

   // void dig(int x1, int y1, int x2, int y2);
   // void createRoom(bool first, int x1, int y1, int x2, int y2);
};
