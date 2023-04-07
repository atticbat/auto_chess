#include "gui_dropdown.hpp"

int parse_resolution(int id);

gui_dropdown::gui_dropdown() {
  edit_mode = false;
  is_resolution = false;
  default_x = 0;
  default_y = 0;
  choice = 3;
}
void gui_dropdown::set_default(int width, int height) {
  default_x = width;
  default_y = height;
}
void gui_dropdown::toggle_edit_mode(void) { edit_mode = !edit_mode; }
int *get_dropdown_choice_ptr(gui_base *gui) {
  gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(gui);

  if (dropdown)
    return (&(dropdown->choice));
  return (NULL);
}
int check_default_x(gui_base *gui) {
  gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(gui);

  if (dropdown)
    return (dropdown->default_x);
  return (1920);
}
int check_default_y(gui_base *gui) {
  gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(gui);

  if (dropdown)
    return (dropdown->default_y);
  return (1080);
}
int check_dropdown_choice(gui_base *gui) {
  gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(gui);

  if (dropdown)
    return (dropdown->choice);
  return (3);
}
bool check_dropdown_edit_mode(gui_base *gui) {
  gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(gui);

  if (dropdown)
    return (dropdown->edit_mode);
  return (false);
}
void set_dropdown_default(gui_base *gui, int x, int y) {
  gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(gui);

  if (dropdown)
    dropdown->set_default(x, y);
}
void check_dropdowns(std::multimap<gui_type, gui_base *> *gui,
                     Vector2 mouse_point) {
  auto range = gui->equal_range(G_DROPDOWN);
  for (auto i = range.first; i != range.second; ++i) {
    gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(i->second);

    if (dropdown) {
      if (CheckCollisionPointRec(mouse_point, dropdown->bounds) &&
          IsGestureDetected(GESTURE_TAP))
        dropdown->toggle_edit_mode();
    }
  }
}
void draw_dropdowns(gui_base *gui) {
  gui_dropdown *dropdown = dynamic_cast<gui_dropdown *>(gui);
  int resolution_x = parse_resolution(dropdown->choice);

  GuiDropdownBox(dropdown->bounds, dropdown->text.c_str(), &(dropdown->choice),
                 dropdown->edit_mode);
  if (dropdown->is_resolution)
    dropdown->set_default(resolution_x, (resolution_x / 16) * 9);
}