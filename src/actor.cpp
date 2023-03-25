#include "actor.hpp"

#include <libtcod.hpp>

TCOD_ConsoleTile Actor::getConsoleTile() const { return TCOD_ConsoleTile{ch, {fg.r, fg.g, fg.b}, {bg.r, bg.g, bg.b}}; }

void Actor::render(tcod::Console &console) const {
   //    console.at({x, y}) = getConsoleTile();
   console.at({pos.x, pos.y}).fg = fg;
   console.at({pos.x, pos.y}).bg = bg;
   console.at({pos.x, pos.y}).ch = ch;
}
