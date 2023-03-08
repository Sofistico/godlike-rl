#include "actor.hpp"

#include <libtcod.hpp>

Actor::Actor(int x, int y, int ch, TCODColor fg, TCODColor bg) : x(x), y(y), ch(ch), fg(fg), bg(bg) {}

TCOD_ConsoleTile Actor::getConsoleTile() const { return TCOD_ConsoleTile{ch, {fg.r, fg.g, fg.b}, {bg.r, bg.g, bg.b}}; }
