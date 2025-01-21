#include "Enemy.hpp"
#include <format>
#include <random>
#include <ctime>
#include "generic_tools.hpp"

Enemy::Enemy(std::string name_of, int hp_of, int sp_of, std::string type, int reduct)
	: enemy_attribs{ name_of, hp_of, sp_of, type, reduct } {};

Enemy::~Enemy() {
	for (physical_attack* attack : phys_attack_list)
	{
		delete attack;
	}
	phys_attack_list.clear();

	for (holy_attack* attack : holy_attack_list)
	{
		delete attack;
	}

	holy_attack_list.clear();
}


void Enemy::print_stats() const{

	std::string message = std::format("\nNombre: {}\nTipo: {}\nHP: {}\nSP: {}\n", enemy_attribs.name, 
																				enemy_attribs.type, 
																				enemy_attribs.hp, 
																				enemy_attribs.sp);
	std::cout << message;
	
}




physical_attack& Enemy::get_phys_atk() {

	int elect = generic_tools::random_number(phys_attack_list.size());

	return *phys_attack_list[elect];
}

holy_attack& Enemy::get_holy_atk() {
	int elect = generic_tools::random_number(holy_attack_list.size());
	return *holy_attack_list[elect];
}


template <>

physical_attack& Enemy::get_attack<physical_attack>() {
	return this->get_phys_atk();
}

template <>

holy_attack& Enemy::get_attack<holy_attack>() {
	return this->get_holy_atk();
}

enemy_att* Enemy::get_enemy_att() {
	return &enemy_attribs;
}

void Enemy::take_turn() {
	std::string message = std::format("\n¡Turno de {}!\n", enemy_attribs.name);
	std::cout << message;
}

bool Enemy::is_alive() const {

	return enemy_attribs.hp > 0;
}

void Enemy::check_hp(){
	if (enemy_attribs.hp < 0) {
		enemy_attribs.hp = 0;
	}
}

void Enemy::check_sp() {
	if (enemy_attribs.sp < 0) {
		enemy_attribs.sp = 0;
	}
}

inline void Enemy::set_COVERING_STATUS(bool cover) {
	COVERING_STATUS = cover;
}


void Enemy::set_covering_and_message(bool cover) {
	COVERING_STATUS = cover;
	if (COVERING_STATUS) {
		std::string message = std::format("\n¡{} está en defensa!\n", enemy_attribs.name);
		std::cout << message;
	}
	else {
		std::string message = std::format("\n¡{} ya no está en defensa!\n", enemy_attribs.name);
		std::cout << message;
	}
}



bool Enemy::get_COVERING_STATUS() const {
	return COVERING_STATUS;
}


