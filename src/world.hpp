#pragma once

#include <vector>

#include "map.hpp"

class World
{
    public:
        void addMap( Map *map );

    private:
        std::vector<Map> maps;
};
