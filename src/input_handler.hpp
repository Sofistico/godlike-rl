#include <SDL.h>

#include "actor.hpp"
#include "map.hpp"

struct Input {
   static bool move(SDL_Keycode ev, Actor &player, Map *map) {
      int newXPos = player.x;
      int newYPos = player.y;
      switch (ev) {
         case SDLK_KP_8:
         case SDLK_UP:
            newYPos--;
            break;
         case SDLK_KP_2:
         case SDLK_DOWN:
            newYPos++;
            break;
         case SDLK_KP_4:
         case SDLK_LEFT:
            newXPos--;
            break;
         case SDLK_KP_6:
         case SDLK_RIGHT:
            newXPos++;
            break;

         case SDLK_KP_7:
            newXPos--;
            newYPos--;
            break;
         case SDLK_KP_9:
            newXPos++;
            newYPos--;
            break;
         case SDLK_KP_1:
            newXPos--;
            newYPos++;
            break;
         case SDLK_KP_3:
            newXPos++;
            newYPos++;
            break;

         default:
            return false;
      }
      if (map->isWalkable(newXPos, newYPos)) {
         player.x = newXPos;
         player.y = newYPos;
         return true;
      }
      return false;
   }
};