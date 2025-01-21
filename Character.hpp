#ifndef CHARACTER_HPP 
#define CHARACTER_HPP
#pragma once
#include<sstream>
#include<iostream>
#include "Attack.hpp"
#include <vector>
#include "Enemy.hpp"

struct char_att {
	std::string name;
	int hp;
	int sp;
	int COVERING_REDUCTION;
};

class Enemy;

class Character {
protected:
	char_att char_attribs;
	bool COVERING_STATUS = false;

	std::vector<physical_attack*> phys_attack_list;
	std::vector<holy_attack*> holy_attack_list;

	physical_attack& get_phys_atk();
	holy_attack& get_holy_atk();
public:
	Character(std::string name_of,  int hp_of, int sp_of, int reduction);
	void  print_stats() const; 
	virtual void Offensive(Enemy& Objective, const attack_attributes& attack) = 0;
	char_att* get_char_att();
	template <typename AttackType> 
	AttackType& get_attack();
	void take_turn();
	void pass_turn();
	bool is_alive() const;
	void check_hp();
	void check_sp();
	bool enough_hp(physical_attack* attack) const;
	bool enough_sp(holy_attack* attack) const;
	inline void set_COVERING_STATUS(bool cover);
	void set_covering_and_message(bool cover);
	bool get_COVERING_STATUS() const ;
	
	~Character();
	
};

template <>
physical_attack& Character::get_attack<physical_attack>();
template <>
holy_attack& Character::get_attack<holy_attack>();

#endif // CHARACTER_HPP