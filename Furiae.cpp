#include "Furiae.hpp"
#include <format>
#include "generic_tools.hpp"
Furiae::Furiae(std::string name_of, unsigned int hp_of, unsigned int sp_of, int reduct)
: Character(name_of, hp_of, sp_of, reduct){

	physical_attack* dagger = new physical_attack("Daga", 5, 0, 0);
	physical_attack* slap = new physical_attack("Bofetada", 1, 2, 0);
	holy_attack* watchers = new holy_attack("Llamada a los custodios", 15, 0, 10);
	holy_attack* pray = new holy_attack("Rezo al sello", 0 , 0, 15);

	this->phys_attack_list.push_back(dagger);
	this->phys_attack_list.push_back(slap);
	this->holy_attack_list.push_back(watchers);
	this->holy_attack_list.push_back(pray);

}

void Furiae::Offensive(Enemy& Objective, const attack_attributes& attack) {

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
