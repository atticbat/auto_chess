#include "gui_dynamic_label.hpp"

void    gui_dynamic_label::set_text(int id, int mode, int size, mINI::INIFile file)
{
    mINI::INIStructure  ini;
    char                *ptr;
    size_t              len;
    char    c[5];

    gui_id = id;
    text_size = size;
    ft_itoa(id, c);
    file.read(ini);
    len = ini.get(text_modes[mode]).get(c).size();
    ptr = (char *) malloc (sizeof(char) * len);
    ft_strlcpy(ptr, ini.get(text_modes[mode]).get(c).c_str(), len + 1);
    text = ptr;
    original_length = strlen(text);
}

void    gui_dynamic_label::update_text(int _value, bool _percentage)
{
    char    value_string[6];
    char    text_buffer[12];

    value = _value;
    percentage = _percentage;
    ft_itoa(value, value_string);
    if (percentage)
        ft_strlcat(value_string, "%", 5);
    ft_strlcpy(text_buffer, text, 10);
    if (text)
        free (text);
    text = (char *) malloc (sizeof(char) * (original_length + strlen(value_string) + 2));
    ft_strlcpy(text, text_buffer, original_length + 1);
    ft_strlcat(text, value_string, original_length + strlen(value_string) + 2);
}

void    update_label(gui_base *gui, default_run *user)
{
    gui_dynamic_label   *label = dynamic_cast <gui_dynamic_label *> (gui);

    if (label)
        label->update_text(user->get_gold(), false);
}