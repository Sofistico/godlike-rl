#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif  // __EMSCRIPTEN__
#include <SDL.h>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <libtcod.hpp>
#include <memory>

#include "actor.hpp"
#include "input_handler.hpp"
#include "map.hpp"

#if defined(_MSC_VER)
#pragma warning(disable : 4297)  // Allow "throw" in main().  Letting the compiler handle termination.
#endif

static tcod::Console g_console;  // The global console object.
static tcod::Context g_context;  // The global libtcod context.
static std::shared_ptr<Map> g_map;
static std::shared_ptr<Actor> g_player;

/// Return the data directory.
static auto get_data_dir() -> std::filesystem::path {
   static auto root_directory = std::filesystem::path{"."};  // Begin at the working directory.
   while (!std::filesystem::exists(root_directory / "data")) {
      // If the current working directory is missing the data dir then it will assume it exists in any parent directory.
      root_directory /= "..";
      if (!std::filesystem::exists(root_directory)) {
         throw std::runtime_error("Could not find the data directory.");
      }
   }
   return root_directory / "data";
};

/// Game loop.
static void main_loop() {
   // set up map and some basic tiles
   // Rendering.
   // tcod::print(g_console, {0, 0}, "Hello World", TCOD_ColorRGB{255, 255, 255}, std::nullopt);
   // g_console.clear();
   // Handle input.
   SDL_Event event;
#ifndef __EMSCRIPTEN__
   // Block until events exist.  This conserves resources well but isn't compatible with animations or Emscripten.
   SDL_WaitEvent(nullptr);
#endif
   while (SDL_PollEvent(&event)) {
      switch (event.type) {
         case SDL_KEYDOWN:
            if (Input::move(event.key.keysym.sym, *g_player, g_map)) {
               g_map->computeFov();
               g_console.clear();
               g_map->render(g_console);
               g_context.present(g_console);
            }

            break;
         case SDL_QUIT:
            std::exit(EXIT_SUCCESS);
            break;
      }
   }
}

/// Main program entry point.
int main(int argc, char **argv) {
   try {
      auto params = TCOD_ContextParams{};
      params.tcod_version = TCOD_COMPILEDVERSION;
      params.argc = argc;
      params.argv = argv;
      params.renderer_type = TCOD_RENDERER_SDL2;
      params.vsync = 1;
      params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
      params.window_title = "Godlike Roguelike";

      auto tileset = tcod::load_tilesheet(get_data_dir() / "dejavu16x16_gs_tc.png", {32, 8}, tcod::CHARMAP_TCOD);
      params.tileset = tileset.get();

      g_console = tcod::Console{80, 40};
      params.console = g_console.get();

      g_context = tcod::Context(params);
      g_map = std::shared_ptr<Map>{new Map(10, 10)};
      g_player = std::make_shared<Actor>(5, 5, '@', tcod::ColorRGB{255, 255, 255}, tcod::ColorRGB{0, 0, 0});
      g_map->addEntity(g_player);
      g_map->player = g_player;
      g_map->computeFov();
      g_map->render(g_console);
      g_context.present(g_console);
      g_console.clear();

#ifdef __EMSCRIPTEN__
      emscripten_set_main_loop(main_loop, 0, 0);
#else
      while (true) main_loop();
#endif
   } catch (const std::exception &exc) {
      std::cerr << exc.what() << "\n";
      throw;
   }
}
