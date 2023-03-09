#include "map.hpp"

Map::Map(int height, int width) : width(width), height(height) {
   tiles = new Tile[height * width];
   internalMap = new TCODMap(width, height);

   for (int x = 0; x < height; x++) {
      for (int y = 0; y < width; y++) {
         if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
            tiles[x + y * width].isTransparent = false;
            tiles[x + y * width].isWalkable = false;
            internalMap->setProperties(x, y, false, false);
         } else {
            tiles[x + y * width].isTransparent = true;
            tiles[x + y * width].isWalkable = true;
            internalMap->setProperties(x, y, true, true);
         }
      }
   }
};

Map::~Map() {
   delete internalMap;
   delete[] tiles;
}

inline bool Map::isTransparent(int x, int y) const { return tiles[x + y * width].isTransparent; }

bool Map::isInFov(int x, int y) const {
   if (internalMap->isInFov(x, y)) {
      tiles[x + y * width].explored = true;
      return true;
   }
   return false;
}

inline bool Map::isExplored(int x, int y) const { return tiles[x + y * width].explored; }

inline bool Map::isWalkable(int x, int y) const { return tiles[x + y * width].isWalkable; }

void Map::render(tcod::Console &console) const {
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
   for (auto actor : actors) {
      actor->render(console);
   }
}

void Map::computeFov() { internalMap->computeFov(player->x, player->y, 5); }

void Map::addEntity(Actor *actor) {
   int x = actor->x;
   int y = actor->y;
   if (isWalkable(x, y)) {
      actors.push_back(actor);
   }
}