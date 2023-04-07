#ifndef GUI_DRAG_DROP_HPP
#define GUI_DRAG_DROP_HPP

#include "gui_base.hpp"

class gui_drag_drop : public gui_base {
public:
  bool is_picked;
  bool display;
  int unit_id;
  sprite_base *sprite;
  gui_drag_drop();
  void generate_picked_up_sprite(int id, int frames, mINI::INIFile file);
  void generate_static_sprite(int id, int frames, mINI::INIFile file);
  void remove_sprite(void);
  void draw_sprite(Vector2 point, float scale, bool drag);
  int get_sprite_id(void);
  void increment_state(void);
};
void check_drag_drops(std::multimap<gui_type, gui_base *> *gui,
                      Vector2 mouse_point, default_run *user);
void del_sprites(std::multimap<gui_type, gui_base *> *gui);
void draw_drag_drops(gui_base *gui, game_settings settings);

#endif