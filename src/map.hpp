#pragma once
#include <libtcod.hpp>
#include <memory>
#include <vector>

#include "actor.hpp"

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
   std::shared_ptr<Actor> player;
   // MapId level;

   inline bool isTransparent(int x, int y) const;
   bool isInFov(int x, int y) const;
   inline bool isExplored(int x, int y) const;
   inline bool isWalkable(int x, int y) const;

   void render(tcod::Console &console) const;
   void computeFov();
   void addEntity(std::shared_ptr<Actor> actor);

   Map(int height, int width);
   ~Map();

  private:
   Tile *tiles;
   std::shared_ptr<TCODMap> internalMap;
   std::vector<std::shared_ptr<Actor>> actors;

   // void dig(int x1, int y1, int x2, int y2);
   // void createRoom(bool first, int x1, int y1, int x2, int y2);
};

struct MapId {
   bool operator==(const MapId rhs) const noexcept { return this->name == rhs.name; }
   bool operator!=(const MapId rhs) const noexcept { return !(*this == rhs); }

   std::string name;
};

template <>
struct std::hash<MapId> {
   std::size_t operator()(const MapId &id) const {
      return std::hash<decltype(id.name)>{}(id.name) ^ std::hash<decltype(id.name)>{}(id.name);
   }
};
