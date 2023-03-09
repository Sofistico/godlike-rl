#include <SDL.h>

#include "actor.hpp"

struct Input {
   static bool move(SDL_Keycode ev, Actor &player) {
      switch (ev) {
         case SDLK_UP:
            player.y++;
            return true;

         default:
            return false;
      }
   }
};