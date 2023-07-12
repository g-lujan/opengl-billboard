#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <functional>
#include <unordered_map>
#include <string>

struct Player;

namespace Controls {

  struct Configurations {
    Configurations();

    std::unordered_map<std::string, std::function<std::string(Player *, float, float)>> move_actions;
    std::array<std::function<std::string(Player *, float, float)>, SDL_NUM_SCANCODES> player_movement;
  };
} // namespace Controls
