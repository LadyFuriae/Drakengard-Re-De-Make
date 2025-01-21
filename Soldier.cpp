#include "Soldier.hpp"
#include "generic_tools.hpp"
#include <format>
Soldier::Soldier(std::string name_of, unsigned int hp_of, unsigned int sp_of, std::string type, int reduct)
	: Enemy(name_of, hp_of, sp_of, type, reduct) {

	physical_attack* thrust = new physical_attack("Estocada", 15, 2, 0);
	physical_attack* esp_attack = new physical_attack("Espadazo del caballero", 10, 0, 0);

	holy_attack* fire_ball = new holy_attack("Bola de fuego", 10, 0, 10);
	holy_attack* iceball = new holy_attack("Hielo", 8, 0, 6);

	this->phys_attack_list.push_back(thrust);
	this->phys_attack_list.push_back(esp_attack);
	this->holy_attack_list.push_back(fire_ball);
	this->holy_attack_list.push_back(iceball);
}

void Soldier::Offensive(Character& Objective, const attack_attributes& attack) {
	if (!Objective.get_COVERING_STATUS()) {

		Objective.get_char_att()->hp -= attack.damage;
		get_enemy_att()->sp -= attack.sp_cost;
		get_enemy_att()->hp -= attack.hp_cost;
		std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
																						enemy_attribs.name,
																						Objective.get_char_att()->name,
																						attack.name,
																						attack.damage);
		std::cout << message;
	}
	else
	{
		int reducted_attack = (attack.damage * (100 - Objective.get_char_att()->COVERING_REDUCTION) / 100);
		Objective.get_char_att()->hp -= reducted_attack;
		get_enemy_att()->sp -= attack.sp_cost;
		get_enemy_att()->hp -= attack.hp_cost;
		std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
																						enemy_attribs.name,
																						Objective.get_char_att()->name,
																						attack.name,
																						reducted_attack);
		std::cout << message;
		generic_tools::sleep(2);
		Objective.set_covering_and_message(false);
	}

	if (Objective.get_char_att()->hp < 0) {
		Objective.get_char_att()->hp = 0;
	}
}

void Soldier::song() {
	std::cout << "owo";
}

