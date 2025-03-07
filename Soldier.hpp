#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#pragma once
#include "Enemy.hpp"
#include "BaseSkill.hpp"
#include "vector"
class Soldier : public Enemy {
public:
	Soldier(std::string name_of, int MAXHP = 200, int MAXSP = 150, int DEFENSE = 30, int reduction = 13);

	void basic_offensive(Character& Objective, const BaseSkillAttributes& attack);

	void song();

};
#endif // !SOLDIER_HPP
