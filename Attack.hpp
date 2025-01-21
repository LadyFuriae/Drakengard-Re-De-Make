#ifndef ATTACK_HPP
#define ATTACK_HPP
#pragma once
#include <iostream>
#include <string>

struct attack_attributes {
	std::string name;
	int damage;
	int hp_cost;
	int sp_cost;
	std::string type;
};

class Attack {
protected:
	attack_attributes attack_att;
public:
	Attack(std::string name_of, int hp_damage, int required_hp, int required_sp, std::string type)
		: attack_att{ name_of, hp_damage, required_hp, required_sp, type }{}

	const attack_attributes& get_attack_att() const;

	void print_att() const;
};
	
class physical_attack : public Attack{

public:
	physical_attack(std::string name_of, int hp_damage, int required_hp, int required_sp, std::string type = "Físico")
		: Attack{ name_of, hp_damage, required_hp, required_sp, type} {}
	
};

class holy_attack : public Attack {

public:
	holy_attack(std::string name_of, int hp_damage, int required_hp, int required_sp, std::string type = "Divino")
		: Attack{ name_of, hp_damage, required_hp, required_sp, type } { }

};
#endif //ATTACK_HPP