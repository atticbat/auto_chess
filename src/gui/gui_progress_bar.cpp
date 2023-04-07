#include "gui_progress_bar.hpp"

gui_progress_bar::gui_progress_bar(int _value, int _min, int _max)
    : gui_slider(_value, _min, _max) {}
gui_progress_bar::~gui_progress_bar() {}
void gui_progress_bar::set_text_right(int id, int mode, int size,
                                      mINI::INIFile file) {
  mINI::INIStructure ini;
  size_t len;
  char c[5];

  gui_id = id;
  text_size = size;
  ft_itoa(id, c);
  file.read(ini);
  text_right = ini.get(text_modes[mode]).get(c);
}
void gui_progress_bar::increment_value(void) {
  value++;
  if (value >= max) {
    value = 0;
    max = 4;
  }
}
