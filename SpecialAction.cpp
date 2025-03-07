#pragma once
#include "SpecialAction.hpp"
#include "BaseSkill.hpp"
#include <format>
#include "generic_tools.hpp"
#include <string>

SpecialAction::SpecialAction(Entity* Objective_of, BaseSkill* spell)
{
	Objective = Objective_of;
	SkillInstance = spell;
	is_active = true;

	switch (SkillInstance->get_base_skill_att().mod_stat) 
	{
	case modified_stat::DEFENSE:
		original_stat = Objective->get_entity_att()->DEFENSE;
	}

}

//SPECIAL_ACTIONS
void SpecialAction::fixed_buff()
{
	Objective->get_entity_att()->DEFENSE += SkillInstance->get_base_skill_att().base_power;
}
void SpecialAction::fixed_debuff() 
{
	Objective->get_entity_att()->DEFENSE -= SkillInstance->get_base_skill_att().base_power;
	
}

//*********************************************************************************************************************
void SpecialAction::restore_stat()
{
	std::string message;
	switch (SkillInstance->get_base_skill_att().mod_stat)
	{
	case modified_stat::DEFENSE:
		Objective->get_entity_att()->DEFENSE = original_stat;
		message = std::format("¡La defensa de {} ha sido restaurada!", Objective->get_entity_att()->name);
	}

	std::cout << message;
}

bool SpecialAction::Is_Active()
{
	return is_active;
}

special_action SpecialAction::get_special_action() 
{
	return SkillInstance->get_base_skill_att().special_act;
}

void SpecialAction::SpecialActionManager()
{

	if(is_active)
	{
		switch (SkillInstance->get_base_skill_att().special_act) 
		{
		case special_action::BUFFER: 
		{
			fixed_buff();
		}
		case special_action::DEBUFFER:
		{
			fixed_debuff();
		}
		default:
			break;
		}
	}
	if (--turns_remaining <= 0)
	{
		restore_stat();
		is_active = false;
	}
}