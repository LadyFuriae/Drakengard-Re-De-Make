#ifndef BASESKILL_HPP
#define BASESKILL_HPP

#pragma once
#include <iostream>
#include <string>
#include "SkillType.hpp"

struct BaseSkillAttributes 
{
	Objective_Type objective;
	std::string name;
	int base_power;
	int hp_cost;
	int sp_cost;
	float bonifier;
	SkillType skill_type;
	Element element;
	std::string element_string;
	std::string description;
	const bool has_effect;
	special_action special_act;
	is_stats_based is_based;
	short int turns_of_effect;
	modified_stat mod_stat;

	BaseSkillAttributes(
		Objective_Type objtv, // objective
		std::string name,
		int power,
		int hp,
		int sp,
		SkillType type,
		std::string desc,
		bool effect,
		float bonus = 0.0f,
		short turns = 0,
		special_action sp_act = special_action::NONE,
		modified_stat mod = modified_stat::NONE)
		:
		objective(objtv),
		name(name),
		base_power(power),
		hp_cost(hp),
		sp_cost(sp),
		skill_type(type),
		description(desc),
		has_effect(effect),
		special_act(sp_act),
		bonifier(bonus),
		turns_of_effect(turns),
		mod_stat(mod)
	{
		switch (skill_type)
		{
		case SkillType::PHYSICAL:
		{
			element_string = "Físico"; 
			element = Element::PHYSICAL;
			break;
		}
		case SkillType::FIRE:
		{
			element_string = "Fuego"; 
			element = Element::FIRE;
			break;
		}
		case SkillType::WATER:
		{
			element_string = "Agua"; 
			element = Element::WATER;
			break;

		}
		case SkillType::HOLY:
		{
			element_string = "Divino";
			element = Element::HOLY;
			break;
		}
		case SkillType::DARK:
		{
			element_string = "Oscuro";
			element = Element::DARK;
			break;
		}
		default:
		{
			element_string = "NONE";
			element = Element::NONE;
			break;
		}
		}
		if (bonifier > 0.0f)
		{
			is_based = is_stats_based::STATS_BASED;
		}
		else
		{
			is_based = is_stats_based::NON_STATS_BASED;
		}

	};
};

class BaseSkill {
private:
	BaseSkillAttributes base_skill_att;
public:
	BaseSkill(BaseSkillAttributes& att);
		
const BaseSkillAttributes& get_base_skill_att() const;
	void print_all_att() const;
};

#endif //BASESKILL_HPP