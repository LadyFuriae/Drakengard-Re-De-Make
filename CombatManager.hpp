#ifndef COMBATMANAGER_HPP
#define COMBATMANAGER_HPP
#pragma once
#include <vector>
#include "Character.hpp"
#include "Enemy.hpp"
#include "BaseSkill.hpp"
#include "Effect.hpp"
class CombatManager
{
protected:

	std::vector<Character*> character_list;
	std::vector<Enemy*> enemy_list;
	
public:
	CombatManager();

	void set_character_list(Character& character);
	void set_enemy_list(Enemy& enemy);

	bool is_character_team_alive(const std::vector<Character*>& team);
	bool is_enemy_team_alive(const std::vector<Enemy*>& enemy_team);

	void print_all_stats();

	const std::vector<Character*>& get_character_list() const;
	const std::vector<Enemy*>& get_enemy_list() const;
	Character& get_character_for_enemy();
	Enemy& get_ally_for_enemy();
	Character& get_character();
	Enemy& get_enemy() const;
	
	void check_everyone_stats();
	
	inline void character_basic_offensive_flow(Character* Attacker);
	inline void enemy_basic_offensive_flow(Enemy* Attacker);
		void command_manager();

	void set_all_character_covering_false();/* they all sets COVERING_STATUS as false  THEY ARE NOT THE SAME AS THE OTHERS*/
	void set_all_enemy_covering_false(); /* they all sets COVERING_STATUS as false THEY ARE NOT THE SAME AS THE OTHERS*/
	void set_everyone_covering_false(); /* they all sets COVERING_STATUS as false THEY ARE NOT THE SAME AS THE OTHERS*/

	inline void set_all_character_covering(bool cover);
	inline void set_all_enemy_covering(bool cover);
	inline void set_everyone_covering(bool cover);
	void success_battle();
	void game_over();

	~CombatManager();
};


#endif //COMBAT_HPP