#pragma once
#include "actor.hpp"
#include "map.hpp"
#include "point.hpp"

struct Actions {
   static bool moveActor(Actor &actor, Point pos, Map *currentMap) {
      if (currentMap->isWalkable(pos.x, pos.y)) {
         actor.pos = pos;
         return true;
      }
      return false;
   }
};