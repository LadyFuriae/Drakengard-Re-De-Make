#ifndef CAIM_HPP
#define CAIM_HPP
#pragma once

#include "character.hpp"
#include <format>


class Caim : public Character {

public:
	Caim(std::string name_of = "Caim", unsigned int hp_of = 150, unsigned int sp_of = 80, int reduct = 30);
	
	void Offensive(Enemy& Objective, const attack_attributes& attack);
};

#endif // CAIM_HPP