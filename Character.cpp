#pragma once
#include "Character.hpp"
#include <format>
Character::Character(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction)
	: Entity
	{
	name_of,
	MAXHP,
	MAXSP,
	DEFENSE,
	reduction
	} {};


Generic_Spell* Character::get_spell()
{
	unsigned int index = 1;
	unsigned int elect = 0;

	for (Generic_Spell* spell : generic_spells_list)
	{
		std::cout << "\nÍndice hechizo: " << index << "\n";
		spell->print_all_att();
		index += 1;
	}

	do 
	{
		std::cout << "Hechizo: ";
		std::cin >> elect;
		if (elect > generic_spells_list.size()) std::cout << "\nIngresa un índice correcto.\n";
	} while (elect > generic_spells_list.size());
	return generic_spells_list[(elect - 1)];
}
