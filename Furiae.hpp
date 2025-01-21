#ifndef FURIAE_HPP
#define FURIAE_HPP

#pragma once
#include "Character.hpp"
#include <format>


class Furiae : public Character {


public:
	Furiae(std::string name_of = "Furiae", unsigned int hp_of = 80, unsigned int sp_of = 120, int reduct = 15);

	void Offensive(Enemy& Objective, const attack_attributes& attack);
};
#endif //FURIAE_HPP