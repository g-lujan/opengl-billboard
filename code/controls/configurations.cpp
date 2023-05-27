#include "configurations.hpp"
#include "../player/player.hpp"

static void move_left(Player *player, float angle, float displacement);
static void move_right(Player *player, float angle, float displacement);
static void move_up(Player *player, float angle, float displacement);
static void move_down(Player *player, float angle, float displacement);

Controls::Configurations::Configurations()
{
  move_actions["move_left"] = move_left;
  move_actions["move_right"] = move_right;
  move_actions["move_up"] = move_up;
  move_actions["move_down"] = move_down;

  // defaults
  player_movement[SDL_SCANCODE_A] = move_actions["move_left"];
  player_movement[SDL_SCANCODE_D] = move_actions["move_right"];
  player_movement[SDL_SCANCODE_W] = move_actions["move_up"];
  player_movement[SDL_SCANCODE_S] = move_actions["move_down"];
}

static void move_left(Player *player, float angle, float displacement)
{
  player->position.x -= displacement * glm::cos(angle - glm::radians(90.f));
  player->position.z -= displacement * glm::sin(angle - glm::radians(90.f));
}

static void move_right(Player *player, float angle, float displacement)
{
  player->position.x += displacement * glm::cos(angle - glm::radians(90.f));
  player->position.z += displacement * glm::sin(angle - glm::radians(90.f));
}

static void move_up(Player *player, float angle, float displacement)
{
  player->position.x -= displacement * glm::cos(angle);
  player->position.z -= displacement * glm::sin(angle);
}

static void move_down(Player *player, float angle, float displacement)
{
  player->position.x += displacement * glm::cos(angle);
  player->position.z += displacement * glm::sin(angle);
}
