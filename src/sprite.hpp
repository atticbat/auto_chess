#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "../raylib-cpp/include/raylib-cpp.hpp"
#include "conversion_functions.hpp"
#include "user.hpp"

class sprite_base {
protected:
  const char *modes[3] = {"RightSpriteAddresses3x", "RightSpriteAddresses4x",
                          "LeftSpriteAddresses4x"};
  float width;
  int unit_id;
  Texture2D image;
  Rectangle source;
  int frames;
  int state = 0;

public:
  sprite_base(int id, int _frames, int mode, mINI::INIFile file) {
    mINI::INIStructure ini;
    char c[5];
    file.read(ini);
    ft_itoa(id, c);
    unit_id = id;
    frames = _frames;
    image = LoadTexture(ini.get(modes[mode]).get(c).c_str());
    if (frames <= 0)
      frames = 1;
    width = (float)image.width / frames;
    source = {0, 0, width, (float)image.height};
  }
  ~sprite_base() { UnloadTexture(image); }
  virtual void increment_state(void) {
    state++;
    state = state % frames;
    source = {width * state, 0, width, (float)image.height};
  }
  void set_unit_id(int id) { unit_id = id; }
  virtual Rectangle get_boundaries(Rectangle offset, float scale) {
    return (Rectangle{offset.x, offset.y, width * scale, image.height * scale});
  }
  virtual Vector2 get_offset_location(Rectangle offset, float scale) {
    return ((Vector2){-(offset.width - width * scale) / 2,
                      image.height * scale - (offset.height / 2)});
  }
  int get_unit_id(void) { return (unit_id); }
  Rectangle get_source(void) { return (source); }
  Texture2D get_image(void) { return (image); }
  float get_width(void) { return (width); }
};

class sprite_picked_up : public sprite_base {
public:
  sprite_picked_up(int id, int frames, int mode, mINI::INIFile file)
      : sprite_base(id, frames, mode, file) {
    ;
  }
  ~sprite_picked_up() { UnloadTexture(image); }
  Vector2 get_offset_location(float scale) {
    return ((Vector2){(width / 2) * scale, (source.height * 9 / 10) * scale});
  }
  Rectangle get_boundaries(Vector2 offset, float scale) {
    return (Rectangle{offset.x, offset.y, width * scale, image.height * scale});
  }
};

class sprite_multi : public sprite_base {
private:
  bool facing_right = true;
  int starts[3] = {0, 2, 4};
  int lengths[3] = {2, 2, 5};
  int current_ani = 0;
  bool despawn = false;
  int state_delay = 0;

public:
  sprite_multi(int id, int frames, int mode, mINI::INIFile file)
      : sprite_base(id, frames, mode, file) {
    ;
  }
  ~sprite_multi() { UnloadTexture(image); }
  void increment_state(void) {
    if (current_ani == 0) {
      state_delay++;
      if (state_delay % 2 == 0) {
        state_delay = 0;
        state++;
      }
    } else if (current_ani == 2)
      state++;
    else if (current_ani == 1) {
      if (state == 3)
        current_ani = 0;
      else
        state++;
    }
    state = (state - starts[current_ani]) % lengths[current_ani] +
            starts[current_ani];
    source = {width * state, 0, width, (float)image.height};
  }
  void change_animation(int index) {
    current_ani = index % 3;
    if (current_ani == 0 || current_ani == 2)
      state = starts[current_ani];
    else
      state = 1;
  }
  virtual Rectangle get_boundaries(Rectangle offset, float scale,
                                   int scroll_x) {
    return (Rectangle{offset.x + scroll_x, offset.y, width * scale,
                      image.height * scale});
  }
  virtual Vector2 get_offset_location(Rectangle offset, float scale) {
    return ((Vector2){-(offset.width - width * scale) / 2,
                      image.height * scale - offset.height});
  }
  void set_despawn(void) { despawn = true; }
  bool get_despawn(void) { return (despawn); }
  int get_animation(void) { return (current_ani); }
};

#endif