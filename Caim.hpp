#ifndef CAIM_HPP
#define CAIM_HPP
#pragma once

#include "character.hpp"
#include <format>


class Caim : public Character {

public:
	Caim(std::string name_of = "Caim", int MAXHP = 150, int MAXSP = 80, int DEFENSE = 0, int reduction = 15);

	void basic_offensive(Enemy& Objective, const BaseSkillAttributes& attack);
};

#endif // CAIM_HPP