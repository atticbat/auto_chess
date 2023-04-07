#ifndef BATTLE_SIM_HPP
#define BATTLE_SIM_HPP

class battle_sim {
private:
  int total_allies = 0;
  int total_enemies = 0;
  int attacker_id = 0;
  int target_id = 0;
  int attacker_pos = 0;
  int target_pos = 0;
  int max_range = 1;
  int dead_zone = -1;
  const int total_slots = 56;
  int move_from = 0;
  int move_to = 0;
  int current_unit = 0;
  int unit_direction = 1;
  int unit_width = 256;
  int scroll_speed = 32;

public:
  int get_total_allies(void) { return (total_allies); }
  int get_total_enemies(void) { return (total_enemies); }
  int get_attacker_id(void) { return (attacker_id); }
  int get_target_id(void) { return (target_id); }
  int get_attacker_pos(void) { return (attacker_pos); }
  int get_target_pos(void) { return (target_pos); }
  int get_max_range(void) { return (max_range); }
  int get_dead_zone(void) { return (dead_zone); }
  int get_total_slots(void) { return (total_slots); }
  int get_move_from(void) { return (move_from); }
  int get_move_to(void) { return (move_to); }
  int get_current_unit(void) { return (current_unit); }
  int get_unit_direction(void) { return (unit_direction); }
  int get_unit_width(void) { return (unit_width); }
  int get_scroll_speed(void) { return (scroll_speed); }

  void set_total_allies(int amount) { total_allies = amount; }
  void set_total_enemies(int amount) { total_enemies = amount; }
  void set_attacker(int atk_id, int atk_pos) {
    attacker_id = atk_id;
    attacker_pos = atk_pos;
  }
  void set_target(int tgt_id, int tgt_pos) {
    target_id = tgt_id;
    target_pos = tgt_pos;
  }
  void set_ranged(int max, int dead) {
    max_range = max;
    dead_zone = dead;
  }
  void set_movement(int unit, int from, int to, int direction) {
    current_unit = unit;
    move_from = from;
    move_to = to;
    unit_direction = direction;
  }
};

#endif