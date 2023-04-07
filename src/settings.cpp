#include "settings.hpp"

int parse_resolution(int id) {
  mINI::INIFile file("data/settings_gui.ini");
  mINI::INIStructure ini;
  char c[5];

  ft_itoa(id, c);
  file.read(ini);
  return (stoi(ini.get("ResolutionX").get(c)));
}

static int parse_choice(int id) {
  mINI::INIFile file("data/settings_gui.ini");
  mINI::INIStructure ini;
  char c[5];

  ft_itoa(id, c);
  file.read(ini);
  return (stoi(ini.get("DropdownDefaultChoice").get(c)));
}

Vector2 get_screen_dim(void) {
  return ((Vector2){(float)parse_resolution(parse_choice(0)),
                    (float)(parse_resolution(parse_choice(0)) / 16) * 9});
}

float get_sprite_size(void) {
  int choice = parse_choice(1);
  switch (choice) {
  case 0:
    return (1);
  case 1:
    return (0.75);
  case 2:
    return (0.5);
  case 3:
    return (0.25);
  }
  return (0.5);
}

void initialise_settings(std::multimap<gui_type, gui_base *> *gui) {
  mINI::INIFile file("data/settings_gui.ini");

  for (int i = 0; i < 5; i++) {
    gui_base *label = new gui_base;

    label->set_text(i, 0, 32, file);
    label->unique_id = i;
    gui->insert(std::pair<gui_type, gui_base *>(G_LABEL, label));
  }
  for (int i = 5; i < 7; i++) {
    gui_checkbox *checkbox = new gui_checkbox;

    if (IsWindowFullscreen() && i - 5 == 0)
      checkbox->checked = true;
    checkbox->unique_id = i;
    gui->insert(std::pair<gui_type, gui_base *>(G_CHECKBOX, checkbox));
  }
  for (int i = 7; i < 9; i++)
    gui->insert(std::pair<gui_type, gui_base *>(G_BUTTON,
                                                generate_button(i - 7, file)));
  {
    gui_slider *slider = new gui_slider(50, 0, 100);

    slider->unique_id = 9;
    gui->insert(std::pair<gui_type, gui_base *>(G_SLIDER, slider));
  }
  for (int i = 10; i < 12; i++) {
    gui_dropdown *dropdown = new gui_dropdown;

    dropdown->set_text(i - 10, 6, 24, file);
    dropdown->choice = parse_choice(i - 10);
    if (i == 10) {
      dropdown->set_default(parse_resolution(dropdown->choice),
                            (parse_resolution(dropdown->choice) / 16) * 9);
      dropdown->is_resolution = true;
    }
    dropdown->unique_id = i;
    gui->insert(std::pair<gui_type, gui_base *>(G_DROPDOWN, dropdown));
  }
}

void apply_settings(std::multimap<gui_type, gui_base *> *gui,
                    game_settings *settings) {
  mINI::INIFile file("data/settings_gui.ini");

  if (check_checkbox(find_gui_by_id(gui, 5, G_CHECKBOX)) &&
      !IsWindowFullscreen()) {
    settings->screen_dim.x = settings->max_dim.x;
    settings->screen_dim.y = settings->max_dim.y;
    SetWindowSize(settings->screen_dim.x, settings->screen_dim.y);
    ToggleFullscreen();
    set_boundaries(gui, (settings->screen_dim.x - settings->settings_dim.x) / 2,
                   (settings->screen_dim.y - settings->settings_dim.y) / 2,
                   file, 1);
  } else if (!check_checkbox(find_gui_by_id(gui, 5, G_CHECKBOX)) &&
             IsWindowFullscreen()) {
    ToggleFullscreen();
    settings->screen_dim.x =
        check_default_x(find_gui_by_id(gui, 10, G_DROPDOWN));
    settings->screen_dim.y =
        check_default_y(find_gui_by_id(gui, 10, G_DROPDOWN));
    SetWindowSize(settings->screen_dim.x, settings->screen_dim.y);
    set_boundaries(gui, (settings->screen_dim.x - settings->settings_dim.x) / 2,
                   (settings->screen_dim.y - settings->settings_dim.y) / 2,
                   file, 1);
  } else if (!IsWindowFullscreen()) {
    settings->screen_dim.x =
        check_default_x(find_gui_by_id(gui, 10, G_DROPDOWN));
    settings->screen_dim.y =
        check_default_y(find_gui_by_id(gui, 10, G_DROPDOWN));
    SetWindowSize(settings->screen_dim.x, settings->screen_dim.y);
    set_boundaries(gui, (settings->screen_dim.x - settings->settings_dim.x) / 2,
                   (settings->screen_dim.y - settings->settings_dim.y) / 2,
                   file, 1);
  }
  mINI::INIStructure ini;
  char holder[5];
  file.read(ini);
  ft_itoa(check_dropdown_choice(find_gui_by_id(gui, 10, G_DROPDOWN)), holder);
  ini["DropdownDefaultChoice"]["0"] = holder;
  ft_itoa(check_dropdown_choice(find_gui_by_id(gui, 11, G_DROPDOWN)), holder);
  ini["DropdownDefaultChoice"]["1"] = holder;
  file.write(ini);
  file.reset("data/user_settings.ini");
  file.read(ini);
  ini["UserSettings"]["ssize"] = holder;
  file.write(ini);
  settings->user->set_sprite_size(
      check_dropdown_choice(find_gui_by_id(gui, 11, G_DROPDOWN)));
}

void update_sprite_size(game_settings *settings, int index) {
  switch (index) {
  case 0: {
    settings->sprite_size = 1;
  } break;
  case 1: {
    settings->sprite_size = 0.75;
  } break;
  case 2: {
    settings->sprite_size = 0.5;
  } break;
  case 3: {
    settings->sprite_size = 0.25;
  } break;
  default:
    break;
  }
}