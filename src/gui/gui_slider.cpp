#include "gui_slider.hpp"

gui_slider::gui_slider(float _value, float _min, float _max) {
  value = _value;
  min = _min;
  max = _max;
}
void set_slider(gui_base *gui, float value) {
  gui_slider *slider = dynamic_cast<gui_slider *>(gui);

  if (slider)
    slider->value = value;
}
float check_slider_value(gui_base *gui) {
  gui_slider *slider = dynamic_cast<gui_slider *>(gui);

  if (slider)
    return (slider->value);
  return (0);
}
float check_slider_min(gui_base *gui) {
  gui_slider *slider = dynamic_cast<gui_slider *>(gui);

  if (slider)
    return (slider->min);
  return (0);
}
float check_slider_max(gui_base *gui) {
  gui_slider *slider = dynamic_cast<gui_slider *>(gui);

  if (slider)
    return (slider->max);
  return (0);
}