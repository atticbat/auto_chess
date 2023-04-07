#ifndef GAME_SETTINGS_HPP
#define GAME_SETTINGS_HPP

#include "../../raylib-cpp/include/raygui.h"
#include "../sprite.hpp"

typedef struct s_game_settings {
  Vector2 max_dim;
  Vector2 screen_dim;
  float scale;
  Vector2 mouse_point;
  Vector2 settings_dim;
  bool exit_window;
  int frame_count;
  float sprite_size;
  int x_offset;
  game_state state;
  default_run *user;
  bool initialised = false;
  bool new_game = false;
} game_settings;

#endif