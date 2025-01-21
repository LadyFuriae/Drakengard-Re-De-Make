#pragma once
#include "Caim.hpp"
#include "generic_tools.hpp"
#include <format>
Caim::Caim(std::string name_of, unsigned int hp_of, unsigned int sp_of, int reduct)
	: Character(name_of, hp_of, sp_of, reduct) {

	physical_attack* Espadazo = new physical_attack("Espadazo", 5, 0, 0);
	physical_attack* Punch = new physical_attack("Puñetazo", 3, 1, 0);
	holy_attack* angelus = new holy_attack("Fauces de Angelus", 10, 0, 10);
	holy_attack* raphael = new holy_attack("Ira de Raphael", 15, 5, 15);

	this->phys_attack_list.push_back(Espadazo);
	this->phys_attack_list.push_back(Punch);
	this->holy_attack_list.push_back(angelus);
	this->holy_attack_list.push_back(raphael);

}
void Caim::Offensive(Enemy& Objective, const attack_attributes& attack) {

	if (!Objective.get_COVERING_STATUS()) {

		Objective.get_enemy_att()->hp -= attack.damage;
		get_char_att()->sp -= attack.sp_cost;
		get_char_att()->hp -= attack.hp_cost;
		std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
			char_attribs.name,
			Objective.get_enemy_att()->name,
			attack.name,
			attack.damage);
		std::cout << message;
	}
	else
	{

		int reducted_attack = (attack.damage * (100 - Objective.get_enemy_att()->COVERING_REDUCTION) / 100);
		Objective.get_enemy_att()->hp -= reducted_attack;
		get_char_att()->sp -= attack.sp_cost;
		get_char_att()->hp -= attack.hp_cost;
		std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
			char_attribs.name,
			Objective.get_enemy_att()->name,
			attack.name,
			reducted_attack);
		std::cout << message;
		generic_tools::sleep(2);
		Objective.set_covering_and_message(false);
	}

	if (Objective.get_enemy_att()->hp < 0) {
		Objective.get_enemy_att()->hp = 0;
	}

}

