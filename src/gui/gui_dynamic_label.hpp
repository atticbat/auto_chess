#ifndef GUI_DYNAMIC_LABEL_HPP
#define GUI_DYNAMIC_LABEL_HPP
#include "gui_base.hpp"
class gui_dynamic_label : public gui_base {
private:
  int value;
  int original_length;
  bool percentage;

public:
  gui_dynamic_label();
  void set_text(int id, int mode, int size, mINI::INIFile file);
  void update_text(int _value, bool _percentage);
};

void update_label(gui_base *gui, default_run *user);

#endif