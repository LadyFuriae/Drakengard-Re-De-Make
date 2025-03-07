#ifndef FURIAE_HPP
#define FURIAE_HPP

#pragma once
#include "Character.hpp"
#include <format>


class Furiae : public Character {


public:
	Furiae(std::string name_of = "Furiae", int MAXHP = 100, int MAXSP = 150, int DEFENSE = 0, int reduction = 12);

	void basic_offensive(Enemy& Objective, const BaseSkillAttributes& attack);
};
#endif //FURIAE_HPP
