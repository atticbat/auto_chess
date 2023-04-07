#include "game_progression.hpp"

game_state parse_destination(int id, mINI::INIFile file) {
  mINI::INIStructure ini;
  char c[4];

  ft_itoa(id, c);
  file.read(ini);
  return (static_cast<game_state>(stoi(ini.get("ButtonDestination").get(c))));
}