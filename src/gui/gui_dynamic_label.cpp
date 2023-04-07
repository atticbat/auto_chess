#include "gui_dynamic_label.hpp"

gui_dynamic_label::gui_dynamic_label() {
  value = 0;
  original_length = 0;
  percentage = false;
}
void gui_dynamic_label::set_text(int id, int mode, int size,
                                 mINI::INIFile file) {
  mINI::INIStructure ini;
  char c[5];

  gui_id = id;
  text_size = size;
  ft_itoa(id, c);
  file.read(ini);
  text = ini.get(text_modes[mode]).get(c);
  original_length = text.length();
}
void gui_dynamic_label::update_text(int _value, bool _percentage) {
  static std::string holder = text;
  std::string value_string;

  value = _value;
  percentage = _percentage;
  value_string = std::to_string(value);
  if (percentage)
    value_string = value_string + "%";
  text = holder + value_string;
}
void update_label(gui_base *gui, default_run *user) {
  gui_dynamic_label *label = dynamic_cast<gui_dynamic_label *>(gui);

  if (label)
    label->update_text(user->get_gold(), false);
}