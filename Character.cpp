#pragma once
#include "Character.hpp"
#include <format>
Character::Character(std::string name_of, int hp_of, int sp_of, int reduction)
	: char_attribs{ name_of, hp_of, sp_of, reduction} {
}

void Character::print_stats() const {

	std::string message = std::format("\nNombre: {}\nHP: {}\nSP: {}\n", char_attribs.name,
																		char_attribs.hp,
																		char_attribs.sp);
	std::cout << message;
}

Character::~Character() {
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

char_att* Character::get_char_att() {
	return &char_attribs;
}

void Character::take_turn() {
	std::string message = std::format("\n¡Turno de {}!\n", char_attribs.name);
	std::cout << message;
}

void Character::pass_turn() {
	std::string message = std::format("\n¡{} pasa turno!\n", char_attribs.name);
	std::cout << message;
}

bool Character::is_alive() const {
	return char_attribs.hp > 0;
}

physical_attack& Character::get_phys_atk() {
	int index = 1;
	for (physical_attack* phys_attack : phys_attack_list) {
		std::cout << "\nÍndice de Ataque: " << index << "\n";
		phys_attack->print_att();
		index++;
	}

	int elect;
	std::cout << "\nSelecciona el ataque:";
	std::cin >> elect;
	elect -= 1;
	return *phys_attack_list[elect];
}

holy_attack& Character::get_holy_atk() {

	int index = 1;
	for (holy_attack* holy_attack : holy_attack_list) {
		std::cout << "\nÍndice de Ataque: " << index << "\n";
		holy_attack->print_att();
		index++;
	}

	int elect;
	std::cout << "\nSelecciona el ataque:";
	std::cin >> elect;
	elect -= 1;
	return *holy_attack_list[elect];
}

void Character::check_hp() {
	if (char_attribs.hp < 0) {
		char_attribs.hp = 0;
	}
}

void Character::check_sp() {
	if (char_attribs.sp < 0) {
		char_attribs.sp = 0;
	}
}

bool Character::enough_hp(physical_attack* attack) const {
	return (char_attribs.hp >= attack->get_attack_att().hp_cost);
}

bool Character::enough_sp(holy_attack* attack) const {
	return (char_attribs.sp >= attack->get_attack_att().sp_cost);
}

inline void Character::set_COVERING_STATUS(bool cover) {
	COVERING_STATUS = cover;
}

void Character::set_covering_and_message(bool cover) {
	COVERING_STATUS = cover;
	if (COVERING_STATUS) {
		std::string message = std::format("\n¡{} está en defensa!\n", char_attribs.name);
		std::cout << message;
	}
	else {
		std::string message = std::format("\n¡{} ya no está en defensa!\n", char_attribs.name);
		std::cout << message;
	}
}

bool Character::get_COVERING_STATUS() const {
	return COVERING_STATUS;
}

template <>

physical_attack& Character::get_attack<physical_attack>() {
	return this->get_phys_atk();
}

template <>

holy_attack& Character::get_attack<holy_attack>() {
	return this->get_holy_atk();
}
