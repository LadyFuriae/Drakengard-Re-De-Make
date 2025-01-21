#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <string>
#include "Character.hpp"
struct enemy_att {

	std::string name;
	int hp;
	int sp;
	std::string type;
	int COVERING_REDUCTION;
};

class Character;

class Enemy {
protected:
	
	enemy_att enemy_attribs;
	bool COVERING_STATUS = false;
	std::vector<physical_attack*> phys_attack_list;
	std::vector<holy_attack*> holy_attack_list;
	physical_attack& get_phys_atk();
	holy_attack& get_holy_atk();
public:
	Enemy(std::string name_of, int hp_of, int sp_of, std::string type, int reduct);
	void  print_stats() const;
	virtual void Offensive(Character& Objective, const attack_attributes& attack) = 0;
	enemy_att* get_enemy_att();
	template <typename AttackType>
	AttackType& get_attack();
	void take_turn();
	virtual void song() = 0;
	bool is_alive() const ;
	void check_hp();
	void check_sp();
	inline void set_COVERING_STATUS(bool cover);
	void set_covering_and_message(bool cover);
	bool get_COVERING_STATUS() const;
	
	~Enemy();
	
};

#endif // ENEMY_HPP