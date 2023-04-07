#include "auto_chess.hpp"

char **draft_controls(std::multimap<gui_type, gui_base *> *gui,
                      std::map<int, sprite_multi *> *sprites,
                      game_settings *settings, char **unit_db) {
  if (!(settings->initialised)) {
    del_sprites(gui);
    del_gui(gui);
    unit_db = del_db(unit_db);
    if (settings->new_game)
      enter_new_game(gui, &(settings->user), settings->scale);
    else
      enter_load(gui, &(settings->user), settings->scale);
    settings->initialised = true;
  }
  return (unit_db);
}

char **settings_controls(std::multimap<gui_type, gui_base *> *gui,
                         std::map<int, sprite_multi *> *sprites,
                         game_settings *settings, char **unit_db) {
  if (!(settings->initialised)) {
    del_sprites(gui);
    del_gui(gui);
    unit_db = del_db(unit_db);
    enter_settings(gui, *settings);
    settings->initialised = true;
  }
  settings->scale = settings->screen_dim.x / settings->max_dim.x;
  return (unit_db);
}

game_state loading_controls(std::multimap<gui_type, gui_base *> *gui,
                            game_settings settings) {
  if (settings.frame_count > 60) {
    enter_menu(gui);
    return (MENU);
  }
  return (LOADING);
}

char **menu_controls(std::multimap<gui_type, gui_base *> *gui,
                     game_settings *settings, char **unit_db) {
  if (!(settings->initialised)) {
    del_sprites(gui);
    del_gui(gui);
    unit_db = del_db(unit_db);
    enter_menu(gui);
    settings->initialised = true;
  }
  return (unit_db);
}

char **simulation_controls(std::multimap<gui_type, gui_base *> *gui,
                           std::map<int, sprite_multi *> *sprites,
                           game_settings *settings,
                           std::multimap<particle_type, particle *> *particles,
                           char **unit_db) {
  if (!(settings->initialised)) {
    del_sprites(gui);
    del_gui(gui);
    unit_db = del_db(unit_db);
    enter_simulation(gui, sprites, settings);
    settings->initialised = true;
  }
  simulation(particles, sprites, settings, gui);
  return (unit_db);
}

char **database_controls(std::multimap<gui_type, gui_base *> *gui,
                         game_settings *settings, char **unit_db) {
  if (!(settings->initialised)) {
    del_sprites(gui);
    del_gui(gui);
    unit_db = del_db(unit_db);
    unit_db = enter_database(gui, settings->screen_dim);
    settings->initialised = true;
  }
  return (unit_db);
}

void enter_menu(std::multimap<gui_type, gui_base *> *gui) {
  mINI::INIFile file("data/menu_gui.ini");
  mINI::INIFile file2("data/settings_gui.ini");

  initialise_menu(gui);
  set_boundaries(gui, 0, 0, file, 1);
  change_button_destination(1, 0, file2);
}

void enter_settings(std::multimap<gui_type, gui_base *> *gui,
                    game_settings settings) {
  mINI::INIFile file("data/settings_gui.ini");

  initialise_settings(gui);
  set_boundaries(gui, (settings.screen_dim.x - settings.settings_dim.x) / 2,
                 (settings.screen_dim.y - settings.settings_dim.y) / 2, file,
                 1);
}

char **enter_database(std::multimap<gui_type, gui_base *> *gui,
                      Vector2 screen_dim) {
  mINI::INIFile file("data/database_gui.ini");

  initialise_database(gui);
  set_database_boundaries(gui, screen_dim);
  return (initialise_unit_db());
}

void enter_new_game(std::multimap<gui_type, gui_base *> *gui,
                    default_run **user, float scale) {
  mINI::INIFile file("data/draft_gui.ini");
  mINI::INIFile file2("data/settings_gui.ini");

  delete (*user);
  *user = new default_run();
  write_changes(*user);
  initialise_draft(gui, *user);
  reroll_shop(gui, *user);
  set_boundaries(gui, 0, 0, file, scale);
  change_button_destination(7, 0, file2);
}

void enter_load(std::multimap<gui_type, gui_base *> *gui, default_run **user,
                float scale) {
  mINI::INIFile file("data/draft_gui.ini");
  mINI::INIFile file2("data/settings_gui.ini");

  load_user(*user);
  initialise_draft(gui, *user);
  set_boundaries(gui, 0, 0, file, scale);
  change_button_destination(7, 0, file2);
}

void enter_simulation(std::multimap<gui_type, gui_base *> *gui,
                      std::map<int, sprite_multi *> *sprites,
                      game_settings *settings) {
  char **unit_db;
  mINI::INIFile file("data/simulation_gui.ini");
  mINI::INIFile file2("data/settings_gui.ini");

  unit_db = initialise_unit_db();
  if (!(settings->user->get_ongoing_game())) {
    initialise_simulation(sprites, settings->user, settings->sprite_size,
                          unit_db);
    settings->user->toggle_ongoing_game();
  }
  initialise_sim_gui(gui);
  set_boundaries(gui, 0, 0, file, settings->scale);
  for (int i = 0; i < 128; i++)
    free(unit_db[i]);
  free(unit_db);
  change_button_destination(4, 0, file2);
}

void initialise_game(game_settings *settings) {
  InitWindow(0, 0, "Auto Chess");
  settings->max_dim = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  settings->screen_dim = get_screen_dim();
  settings->scale = settings->screen_dim.x / settings->max_dim.x;
  SetWindowSize(1920, 1080);
  SetTargetFPS(60);

  settings->mouse_point = {0.0f, 0.0f};
  settings->settings_dim = {800, 450};
  settings->exit_window = false;
  settings->frame_count = 0;
  settings->sprite_size = get_sprite_size();
  settings->x_offset =
      -(56 * (256 * settings->sprite_size) - settings->screen_dim.x) / 2;
  settings->state = LOADING;
  settings->user = new default_run();
}
