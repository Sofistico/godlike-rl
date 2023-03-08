#include "map.hpp"

Map::Map(int height, int width) : width(width), height(height) {
   tiles = new Tile[height * width];
   internalMap = new TCODMap(width, height);

   for (int x = 0; x < height; x++) {
      for (int y = 0; y < width; y++) {
         if ((x + 1) % 1 == 1) {
            internalMap->setProperties(x, y, true, true);
         } else {
            internalMap->setProperties(x, y, false, false);
         }
      }
   }
};

Map::~Map() {
   delete internalMap;
   delete[] tiles;
}

bool Map::isTransparent(int x, int y) const { return tiles[x + y * width].isTransparent; }

bool Map::isInFov(int x, int y) const {
   if (internalMap->isInFov(x, y)) {
      tiles[x + y * width].explored = true;
      return true;
   }
   return false;
}

bool Map::isExplored(int x, int y) const { return tiles[x + y * width].explored; }

bool Map::isWalkable(int x, int y) const { return tiles[x + y * width].isWalkable; }

void Map::render(tcod::Console &console) const {
   static const TCODColor darkWall(0, 0, 100);
   static const TCODColor darkGround(50, 50, 150);
   static const TCODColor lightWall(130, 110, 50);
   static const TCODColor lightGround(200, 180, 50);

   for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
         if (isInFov(x, y)) {
            console.at({x, y}) = isWalkable(x, y)
                                     ? TCOD_ConsoleTile{'.', tcod::ColorRGB{128, 128, 128}, tcod::ColorRGB{0, 0, 0}}
                                     : TCOD_ConsoleTile{'#', tcod::ColorRGB{128, 128, 128}, tcod::ColorRGB{0, 0, 0}};
         }

         else if (isExplored(x, y)) {
            console.at({x, y}) = isWalkable(x, y)
                                     ? TCOD_ConsoleTile{'.', tcod::ColorRGB{50, 50, 100}, tcod::ColorRGB{0, 0, 0}}
                                     : TCOD_ConsoleTile{'#', tcod::ColorRGB{0, 0, 100}, tcod::ColorRGB{0, 0, 0}};
         }
      }
   }
}

void Map::computeFov() { internalMap->computeFov(0, 0, 10); }

void Map::addEntity(int x, int y) {}