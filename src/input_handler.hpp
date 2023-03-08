#include <SDL.h>

struct Input {
   bool move(SDL_Event ev) { if (ev.key == SDL_KeyboardEvent::keysym) }
};