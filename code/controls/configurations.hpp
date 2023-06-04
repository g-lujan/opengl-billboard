#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <functional>
#include <variant>
#include <string>

struct Player;

namespace Controls {

  struct Configurations {
    Configurations();

    std::unordered_map<std::string, std::function<std::string(Player *, float, float)>> move_actions;
    std::unordered_map<SDL_Scancode, std::function<std::string(Player *, float, float)>> player_movement;
  };
} // namespace Controls
