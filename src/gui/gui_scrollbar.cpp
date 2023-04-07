#include "gui_scrollbar.hpp"

gui_scrollbar::gui_scrollbar() {
  scroll.x = 99;
  scroll.y = -20;
}
void set_scrollbar_content(gui_base *gui, float x_off, float y_off, float width,
                           float height) {
  gui_scrollbar *scrollbar = dynamic_cast<gui_scrollbar *>(gui);

  if (scrollbar)
    scrollbar->content = Rectangle{x_off, y_off, width, height};
}
void set_scrollbar_bounds(gui_base *gui, float off_x, float off_y, float width,
                          float height) {
  gui_scrollbar *scrollbar = dynamic_cast<gui_scrollbar *>(gui);

  if (scrollbar)
    scrollbar->bounds = Rectangle{off_x, off_y, width, height};
}
Rectangle check_scrollbar_content(gui_base *gui) {
  gui_scrollbar *scrollbar = dynamic_cast<gui_scrollbar *>(gui);

  if (scrollbar)
    return (scrollbar->content);
  return ((Rectangle){0, 0, 0, 0});
}
float check_scrollbar_x(gui_base *gui) {
  gui_scrollbar *scrollbar = dynamic_cast<gui_scrollbar *>(gui);

  if (scrollbar)
    return (scrollbar->scroll.x);
  return (-1);
}
float check_scrollbar_y(gui_base *gui) {
  gui_scrollbar *scrollbar = dynamic_cast<gui_scrollbar *>(gui);

  if (scrollbar)
    return (scrollbar->scroll.y);
  return (-1);
}
Vector2 *get_scrollbar_scroll(gui_base *gui) {
  gui_scrollbar *scrollbar = dynamic_cast<gui_scrollbar *>(gui);

  if (scrollbar)
    return (&(scrollbar->scroll));
  return (NULL);
}