#include "Enemy.hpp"
#include <format>
#include <random>
#include <ctime>
#include "generic_tools.hpp"

Enemy::Enemy(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction)
	: Entity
	{
	name_of,
	MAXHP,
	MAXSP,
	DEFENSE,
	reduction
	} {};

Generic_Spell* Enemy::get_spell()
{
	int elect = generic_tools::random_number(generic_spells_list.size());
	return generic_spells_list[elect];
}