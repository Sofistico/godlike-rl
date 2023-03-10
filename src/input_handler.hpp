#include <SDL.h>

#include "action.hpp"
#include "actor.hpp"
#include "map.hpp"
#include "point.hpp"

struct Input {
   static bool move(SDL_Keycode ev, Actor &player, Map *map) {
      int newXPos = player.pos.x;
      int newYPos = player.pos.y;
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
      return Actions::moveActor(player, {newXPos, newYPos}, map);
   }
};