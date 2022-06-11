#include "user.hpp"

void    write_changes(default_run *user)
{
    mINI::INIFile   file ("data/user_settings.ini");
    mINI::INIStructure ini;
    char    it[3];
    char    holder[5];
    file.read(ini);
    for (int i = 0; i < 8; i++)
    {
        ft_itoa(i, it);
        ft_itoa(user->get_roster_slot(i), holder);
        ini["Roster"][it] = holder;
        ft_itoa(user->get_unit_xp(i), holder);
        ini["UnitXP"][it] = holder;
        ft_itoa(user->get_unit_max_xp(i), holder);
        ini["MaxXP"][it] = holder;
    }
    for (int i = 0; i < 5; i++)
    {
        ft_itoa(i, it);
        ft_itoa(user->get_store_slot(i), holder);
        ini["Store"][it] = holder;
        // user->set_store(i, stoi(ini.get("Store").get(it)));
    }
    // ini["UserSettings"]["name"] = user->get_name();
    ft_itoa(user->get_gold(), holder);
    ini["UserSettings"]["gold"] = holder;
    ft_itoa(user->get_level(), holder);
    ini["UserSettings"]["level"] = holder;
    ft_itoa(user->get_exp(), holder);
    ini["UserSettings"]["exp"] = holder;
    ft_itoa(user->get_exp_cap(), holder);
    ini["UserSettings"]["max_exp"] = holder;
    ft_itoa(user->get_wins(), holder);
    ini["UserSettings"]["wins"] = holder;
    ft_itoa(user->get_losses(), holder);
    ini["UserSettings"]["losses"] = holder;
    file.write(ini);
}

void    load_user(default_run *user)
{
    mINI::INIFile   file ("data/user_settings.ini");
    mINI::INIStructure ini;
    char    it[4];

    file.read(ini);
    // user->set_name(ini.get("UserSettings").get("name").c_str());
    user->set_gold(stoi(ini.get("UserSettings").get("gold")));
    user->set_level(stoi(ini.get("UserSettings").get("level")));
    user->set_exp(stoi(ini.get("UserSettings").get("exp")));
    user->set_exp_cap(stoi(ini.get("UserSettings").get("max_exp")));
    user->set_wins(stoi(ini.get("UserSettings").get("wins")));
    user->set_losses(stoi(ini.get("UserSettings").get("losses")));
    user->set_sprite_size(stoi(ini.get("UserSettings").get("ssize")));
    printf("sprite size is %d.\n", user->get_sprite_size());
    for (int i = 0; i < 8; i++)
    {
        ft_itoa(i, it);
        user->set_unit(i, stoi(ini.get("Roster").get(it)));
        user->set_unit_exp(i, stoi(ini.get("UnitXP").get(it)));
        user->set_unit_max_exp(i, stoi(ini.get("MaxXP").get(it)));
    }
    for (int i = 0; i < 5; i++)
    {
        ft_itoa(i, it);
        user->set_store(i, stoi(ini.get("Store").get(it)));
    }
}