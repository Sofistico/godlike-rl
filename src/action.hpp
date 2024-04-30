#pragma once
#include "actor.hpp"
#include "map.hpp"
#include "point.hpp"

struct Actions {
    static bool moveActor( Actor &actor, point pos, std::shared_ptr<Map> currentMap ) {
        if( currentMap->isWalkable( pos.x, pos.y ) ) {
            actor.pos = pos;
            return true;
        }
        return false;
    }
};