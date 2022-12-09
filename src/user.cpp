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
	std::string temp;
    char    it[4];

    file.read(ini);
    // user->set_name(ini.get("UserSettings").get("name").c_str());

	temp = ini.get("UserSettings").get("gold");
    user->set_gold(ft_atoi(temp.c_str()));
	temp = ini.get("UserSettings").get("level");
    user->set_level(ft_atoi(temp.c_str()));
	temp = ini.get("UserSettings").get("exp");
    user->set_exp(ft_atoi(temp.c_str()));
	temp = ini.get("UserSettings").get("max_exp");
    user->set_exp_cap(ft_atoi(temp.c_str()));
	temp = ini.get("UserSettings").get("wins");
    user->set_wins(ft_atoi(temp.c_str()));
	temp = ini.get("UserSettings").get("losses");
    user->set_losses(ft_atoi(temp.c_str()));
	temp = ini.get("UserSettings").get("ssize");
    user->set_sprite_size(ft_atoi(temp.c_str()));
    for (int i = 0; i < 8; i++)
    {
        ft_itoa(i, it);
		temp = ini.get("Roster").get("it");
    	user->set_unit(i, ft_atoi(temp.c_str()));
		temp = ini.get("UnitXP").get("it");
    	user->set_unit_exp(i, ft_atoi(temp.c_str()));
		temp = ini.get("MaxXP").get("it");
    	user->set_unit_max_exp(i, ft_atoi(temp.c_str()));
    }
    for (int i = 0; i < 5; i++)
    {
        ft_itoa(i, it);
		temp = ini.get("Store").get("it");
        user->set_store(i, ft_atoi(temp.c_str()));
    }
}