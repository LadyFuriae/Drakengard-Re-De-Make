#include <format>
#include <string>
#include "CombatManager.hpp"
#include "generic_tools.hpp"
#include "Caim.hpp"
#include "Furiae.hpp"
#include "Soldier.hpp"
#include "songs.hpp"

CombatManager::CombatManager()
{
	Character* caim = new Caim;
	Character* furiae = new Furiae;
	Enemy* soldier1 = new Soldier("Rickert");
	Enemy* soldier2 = new Soldier("Oscar");

	character_list.push_back(caim);
	character_list.push_back(furiae);

	enemy_list.push_back(soldier1);
	enemy_list.push_back(soldier2);

}
CombatManager::~CombatManager() 
{
	for (Character* character : character_list) 
	{
		delete character;
	}

	character_list.clear();

	for (Enemy* enemy : enemy_list) 
	{
		delete enemy;
	}

	enemy_list.clear();
}

void CombatManager::set_character_list(Character& character) {
	character_list.push_back(&character);

}void CombatManager::set_enemy_list(Enemy& enemy) {
	enemy_list.push_back(&enemy);
}

bool CombatManager::is_character_team_alive(const std::vector<Character*>& team) {
	for (Character* character : team)
	{
		if (character->is_alive())
		{
			return true;
		}
	}
	return false;
}

bool CombatManager::is_enemy_team_alive(const std::vector<Enemy*>& enemy_team) {
	for (Enemy* enemy : enemy_team)
	{
		if (enemy->is_alive())
		{
			return true;
		}
	}
	return false;
}

void CombatManager::print_all_stats() {
	for (Character* character : character_list)
	{
		character->print_stats();
	}
	int index = 1;
	for (Enemy* enemy : enemy_list)
	{
		std::cout << "\nÍndice de enemigo: " << index;
		enemy->print_stats();
		index++;
	}
}

Enemy& CombatManager::get_ally_for_enemy()
{
	int elect = generic_tools::random_number(enemy_list.size());
	return *enemy_list[elect];
}

const std::vector<Character*>& CombatManager::get_character_list() const {
	return character_list;
}
const std::vector<Enemy*>& CombatManager::get_enemy_list() const {
	return enemy_list;
}

Character& CombatManager::get_character_for_enemy() {

	int elect = generic_tools::random_number(character_list.size());
	return *character_list[elect];
}

Character& CombatManager::get_character() 
{
	int elect;
	do {
		std::cout << "\nObjetivo: ";
		std::cin >> elect;
		elect -= 1;
		if (elect >= character_list.size() || elect < 0) {
			std::cout << "\nDebes ingresar un índice válido para el aliado.";
		}
	} while (elect >= enemy_list.size() || elect < 0);
	return *character_list[elect];
}

Enemy& CombatManager::get_enemy() const {

	int elect = -1;
	while (elect >= enemy_list.size() || elect < 0) {
		std::cout << "\nObjetivo: ";
		std::cin >> elect;
		elect -= 1;
		if (elect >= enemy_list.size() || elect < 0) {
			std::cout << "\nDebes ingresar un índice válido para el enemigo.";
		}
	}

	return *enemy_list[elect];
}

void CombatManager::check_everyone_stats() {
	for (Character* character : character_list)
	{
		character->check_hp();
		character->check_sp();
	}

	for (Enemy* enemy : enemy_list)
	{
		enemy->check_hp();
		enemy->check_sp();
	}
}

void CombatManager::set_all_character_covering_false() {
	for (Character* character : character_list) {
		if (!character->get_covering_status()) {
			continue;
		}
		else {
			character->set_covering_and_message(false);
		}
	}
}

void CombatManager::set_all_enemy_covering_false() {
	for (Enemy* enemy : enemy_list) {
		if (!enemy->get_covering_status()) 
		{
			continue;
		}
		else
		{
			enemy->set_covering_and_message(false);
		}
	}
}

void CombatManager::set_everyone_covering_false() {
	set_all_character_covering_false();
	set_all_enemy_covering_false();
}


inline void CombatManager::set_all_character_covering(bool cover) {
	for (Character* character : character_list) {
		character->set_covering_status(cover);
	}
}

inline void CombatManager::set_all_enemy_covering(bool cover) {
	for (Enemy* enemy : enemy_list) {
		enemy->set_covering_status(cover);
	}
}

inline void CombatManager::set_everyone_covering(bool cover) {
	set_all_character_covering(cover);
	set_all_enemy_covering(cover);
}

void CombatManager::character_basic_offensive_flow(Character* Attacker)
{
	Attacker->basic_offensive(get_enemy(), Attacker->Basic_Attack->get_base_skill_att());
}

void CombatManager::enemy_basic_offensive_flow(Enemy* Attacker)
{
	Attacker->basic_offensive(get_character_for_enemy(), Attacker->Basic_Attack->get_base_skill_att());
}


void CombatManager::command_manager()
{
	generic_tools::start_song(SHOSTAKOVICH);

	while (is_character_team_alive(character_list) && is_enemy_team_alive(enemy_list))
	{
		for (Character* character : character_list)
		{
			if (!character->is_alive()) continue;
			generic_tools::clear_console();
			print_all_stats();
			character->take_turn();
			int elect;
			do {
				std::cout << "\n1. Atacar. \n2. Hechizo\n3. Cubrirse: ";
				std::cin >> elect;

				if (elect < 1 || elect > 3) {
					std::cout << "\nIngresa una opción válida\n";
				}
			} while (elect < 1 || elect > 3);

			switch (elect)
			{
			case 1: // Basic attack
			{
				if (character->get_covering_status()) character->set_covering_and_message(false), generic_tools::sleep(2);

				this->character_basic_offensive_flow(character);
				check_everyone_stats();
				generic_tools::sleep(5);
				break;
			}
			case 2: //generic_spell
			{
				if (character->get_covering_status()) character->set_covering_and_message(false), generic_tools::sleep(2);

				Generic_Spell& spell = *character->get_spell();
				if (character->enough_hp(spell.get_base_skill_att()) && character->enough_sp(spell.get_base_skill_att()))
				{
					if (spell.get_base_skill_att().objective == Objective_Type::ENEMIES)
					{
						Enemy& enemy_reference = get_enemy();
						spell.generic_spell_manager(enemy_reference, *character);
					}
					else
					{
						Character& ally_reference = get_character();
						spell.generic_spell_manager(ally_reference, *character);
					}
				}
				else
				{
					std::cout << "No tienes suficiente HP/SP para castear este hechizo.";
					generic_tools::sleep(2);
				}
				break;
			}
			case 3://Cover
			{
				character->set_covering_and_message(true);
				generic_tools::sleep(2);
				break;
			}
			default:
			{
				std::cout << "\nERROR: NO DEBERÍAS VER ESTO. SI VES ESTE ERROR, REPÓRTALO.\n";
				generic_tools::sleep(10);
				break;
			}
			}
			character->check_effect();
			character->check_special_action();
			generic_tools::sleep(3);
			check_everyone_stats();
		}

		for (Enemy* enemy : enemy_list)
		{
			if (!enemy->is_alive()) continue;
			generic_tools::clear_console();
			print_all_stats();
			enemy->take_turn();
			generic_tools::sleep(1);
			int elect = 0;

			elect = generic_tools::random_number(1, 3);
			
			switch (elect)
			{
			case 1://Basic BaseSkill
			{
				if (enemy->get_covering_status()) enemy->set_covering_and_message(false), generic_tools::sleep(2);
				this->enemy_basic_offensive_flow(enemy);
				void check_everyone_stats();
				generic_tools::sleep(5);

				break;
			}
			case 2:// generic_spell
			{
				Generic_Spell& spell = *enemy->get_spell();
				if (enemy->enough_hp(spell.get_base_skill_att()) && enemy->enough_sp(spell.get_base_skill_att()))
				{

					if (spell.get_base_skill_att().objective == Objective_Type::ENEMIES)
					{
						Character& character_reference = get_character_for_enemy();
						spell.generic_spell_manager(character_reference, *enemy);
					}
					else
					{
						Enemy& ally_reference = get_ally_for_enemy();
						spell.generic_spell_manager(ally_reference, *enemy);
					}
				}
				else
				{
					this->enemy_basic_offensive_flow(enemy);
				}
				break;
			}
			case 3://Cover
			{
				enemy->set_covering_and_message(true);
				generic_tools::sleep(2);
				break;
			}
			default: 
			{
				std::cout << "ERROR: NO DEBERÍAS VER ESTO. SI VES ESTE ERROR, REPÓRTALO.";
				generic_tools::sleep(10);
				break;
			}
			}
			enemy->check_effect();
			enemy->check_special_action();
			check_everyone_stats();
			generic_tools::sleep(3);
		}

	}
	

	generic_tools::stop_song();

	if (!is_enemy_team_alive(enemy_list))
	{
		success_battle();
	}
	else
	{
		game_over();
	}
}

void CombatManager::success_battle() {
	print_all_stats();
	std::cout << "\n¡Has ganado!";
	generic_tools::start_song(FANFARRIA);
	generic_tools::wait_for_enter();
	generic_tools::stop_song();
}

void CombatManager::game_over() 
{
	print_all_stats();
	std::cout << "\nHas perdido...";
	generic_tools::start_song(GAME_OVER);
	generic_tools::wait_for_enter();
	generic_tools::stop_song();
}