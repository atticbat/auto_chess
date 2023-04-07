#include "gui_textbox.hpp"

gui_textbox::gui_textbox() {
  max_input = 5;
  edit_mode = false;
  input_count = 0;
}
void gui_textbox::set_text(int id, int size) {
  gui_id = id;
  text_size = size;
  max_input = db_max_input[id];
}
bool gui_textbox::check_if_max(void) {
  if (input_count == max_input)
    return (true);
  return (false);
}
void gui_textbox::add_letter(char letter) {
  if (!check_if_max()) {
    text[input_count] = letter;
    input_count++;
    text[input_count] = '\0';
  }
}
void gui_textbox::delete_letter(void) {
  if (input_count > 0) {
    input_count--;
    text[input_count] = '\0';
  }
}
static void input_status_visual(gui_textbox *textbox) {
  Rectangle bounds = textbox->bounds;

  DrawRectangleRec(bounds, LIGHTGRAY);
  if (textbox->edit_mode)
    DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, BLACK);
  else
    DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height,
                       DARKGRAY);
  DrawText(textbox->text.c_str(), bounds.x + 4, bounds.y + 8, 24, BLACK);
  if (textbox->edit_mode) {
    DrawText("_", (int)bounds.x + 8 + MeasureText(textbox->text.c_str(), 24),
             (int)bounds.y + 8, 24, BLACK);
  }
}
void input_status_check(gui_textbox *textbox, Vector2 mousePoint) {
  if (CheckCollisionPointRec(mousePoint, textbox->bounds))
    textbox->edit_mode = true;
  else
    textbox->edit_mode = false;
  if (textbox->edit_mode) {
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    int key = GetCharPressed();
    while (key > 0) {
      if ((key >= 48) && (key <= 57))
        textbox->add_letter(key);
      key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE))
      textbox->delete_letter();
  }
}
void check_textboxes(std::multimap<gui_type, gui_base *> *gui,
                     Vector2 mouse_point) {
  bool no_hover = true;
  auto range = gui->equal_range(G_TEXTBOX);

  for (auto i = range.first; i != range.second; ++i) {
    gui_textbox *textbox = dynamic_cast<gui_textbox *>(i->second);

    input_status_check(textbox, mouse_point);
    if (textbox->edit_mode)
      no_hover = false;
  }
  if (no_hover)
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}
void draw_textbox(gui_base *gui) {
  gui_textbox *textbox = dynamic_cast<gui_textbox *>(gui);

  input_status_visual(textbox);
}