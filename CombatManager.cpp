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
	Enemy* soldier1 = new Soldier("Rickert", 100, 200);
	Enemy* soldier2 = new Soldier("Oscar", 100, 200);

	character_list.push_back(caim);
	character_list.push_back(furiae);

	enemy_list.push_back(soldier1);
	enemy_list.push_back(soldier2);
	
}
CombatManager::~CombatManager(){
	for (Character* character : character_list) {
		delete character;
	}
	character_list.clear();

	for (Enemy* enemy : enemy_list) {
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

const std::vector<Character*>& CombatManager::get_character_list() const {
	return character_list;
}
const std::vector<Enemy*>& CombatManager::get_enemy_list() const {
	return enemy_list;
}

Character& CombatManager::get_character_for_enemy(){
	
	int elect = generic_tools::random_number(character_list.size());
	return *character_list[elect];
}

Character& CombatManager::get_character() {
	unsigned int elect;
	std::cout << "\nPersonaje: ";
	std::cin >> elect;

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
		if (!character->get_COVERING_STATUS()) {
			continue;
		}
		else {
			character->set_covering_and_message(false);
		}
	}
}

void CombatManager::set_all_enemy_covering_false() {
	for (Enemy* enemy : enemy_list) {
		if (!enemy->get_COVERING_STATUS()) {
			continue;
		}
		else {
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
		character->set_COVERING_STATUS(cover);
	}
}

inline void CombatManager::set_all_enemy_covering(bool cover) {
	for (Enemy* enemy : enemy_list) {
		enemy->set_COVERING_STATUS(cover);
	}
}

inline void CombatManager::set_everyone_covering(bool cover) {
	set_all_character_covering(cover);
	set_all_enemy_covering(cover);
}



void CombatManager::character_offensive_flow(Character* character) 
{
	bool action = false;
	while (!action)
	{
		int elect;
		std::cout << "\nSelecciona el tipo de ataque.\n1: Físico\n2:Sagrado: ";
		std::cin >> elect;

		switch (elect)
		{
		case 1://Physical
		{
			physical_attack& attack = character->get_attack<physical_attack>();
			if (character->enough_hp(&attack)) {
				character->Offensive(get_enemy(), attack.get_attack_att());
				action = true;
			}
			else 
			{
				std::cout << "No tienes suficiente HP para realizar este ataque";
				generic_tools::sleep(3);
			}
			break;
		}
		case 2://Holy
		{
			holy_attack& attack = character->get_attack<holy_attack>();
			if (character->enough_sp(&attack))
			{
				character->Offensive(get_enemy(), attack.get_attack_att());
				action = true;
			}
			else 
			{
				std::cout << "\nNo tienes suficiente SP para realizar este ataque.\n";
				generic_tools::sleep(3);
			}
			break;
		}
		default:
		{
			std::cout << "\nSelecciona algún ataque\n";
			this->character_offensive_flow(character);
			break;
		}
		}
	}
}

void CombatManager::enemy_offensive_flow(Enemy* enemy) 
{
	int elect = generic_tools::random_number(2);
	switch (elect)
	{
		case 0:
		{
			enemy->Offensive(get_character_for_enemy(), enemy->get_attack<physical_attack>().get_attack_att());
			break;
		}
		case 1:
		{
			enemy->Offensive(get_character_for_enemy(), enemy->get_attack<holy_attack>().get_attack_att());
			break;
		}
		default:
			{
				std::cout << "\nERROR. NO DEBERÍAS VER ESTE MENSAJE. SI ES ASÍ, REPÓRTALO.\n";
				generic_tools::sleep(10);
				break;
			}
	}
}

void CombatManager::command_manager()
{
	generic_tools::start_song(C_V_G_P1);

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
				std::cout << "\n1. Atacar. \n2. Defensa\n3. Pasar: ";
				std::cin >> elect;
				
				if (elect < 1 || elect > 3) {
					std::cout << "\nIngresa una opción válida\n";
				}
			} while (elect < 1 || elect > 3);

			switch (elect)
			{
				case 1: // attack
				{	if (character->get_COVERING_STATUS()) character->set_covering_and_message(false), generic_tools::sleep(3);
					
					this->character_offensive_flow(character);
					check_everyone_stats();
					generic_tools::sleep(5);
					break;
				}
				case 2: //defend
				{
					character->set_covering_and_message(true);
					generic_tools::sleep(2);
					break;
				}
				case 3://Pass turn
				{
					character->pass_turn();
					generic_tools::sleep(2);
					break;
				}
				default:
				{
					std::cout << "\nERROR: NO DEBERÍAS VER ESTO. SI VES ESTE ERROR, REPÓRTALO..\n";
					generic_tools::sleep(10);
					break;
				}
			}
		}

		for (Enemy* enemy : enemy_list)
		{	
			if (!enemy->is_alive()) continue;
			generic_tools::clear_console();
			print_all_stats();
			enemy->take_turn();
			generic_tools::sleep(1);
			int elect = 0;

			do {
				elect = generic_tools::random_number(1, 2);
			} while (elect <= 0);

			switch (elect)
			{
				case 1:
				{
					
					if (enemy->get_COVERING_STATUS()) enemy->set_covering_and_message(false);
					this->enemy_offensive_flow(enemy);
					void check_everyone_stats();
					generic_tools::sleep(5);

					break;
				}
				case 2:
				{
					enemy->set_covering_and_message(true);
					generic_tools::sleep(2);
					break;
				}
				default:
				{
					std::cout << "ERROR: NO DEBERÍAS VER ESTO. SI VES ESTE ERROR, REPÓRTALO.";
					generic_tools::sleep(10);
				}
			}
			
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
	std::cout << "\n¡Has ganado!";
	generic_tools::start_song(FANFARRIA);
	generic_tools::wait_for_enter();
	generic_tools::stop_song();
}

void CombatManager::game_over() {
	std::cout << "\nHas perdido...";
	generic_tools::start_song(GAME_OVER);
	generic_tools::wait_for_enter();
	generic_tools::stop_song();
}