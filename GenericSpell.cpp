#pragma once 
#include "GenericSpell.hpp"
#include <format>
#include "generic_tools.hpp"

Generic_Spell::Generic_Spell(BaseSkillAttributes& att)
	: BaseSkill{ att } {};


void Generic_Spell::offensive_cast(Entity& Objective, Entity& Caster)
{
	Caster.get_entity_att()->HP -= get_base_skill_att().hp_cost;
	Caster.get_entity_att()->SP -= get_base_skill_att().sp_cost;
	if (!Objective.get_covering_status() && get_base_skill_att().has_effect)
	{
		Objective.add_effect(*this);
	}
	else if (get_base_skill_att().special_act != special_action::NONE)
	{
		Objective.add_special_action(*this);
	}
	else
	{
		if (!Objective.get_covering_status()) {

			if (!Objective.is_weak(get_base_skill_att().skill_type)) {


				int calculated_damage = get_base_skill_att().base_power;
				Objective.get_entity_att()->HP -= calculated_damage;
				std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
					Caster.get_entity_att()->name,
					Objective.get_entity_att()->name,
					get_base_skill_att().name,
					calculated_damage);
				std::cout << message;
			}
			else
			{
				int calculated_damage = get_base_skill_att().base_power * get_base_skill_att().bonifier;
				Objective.get_entity_att()->HP -= calculated_damage;
				std::cout << "\n¡Débil!\n";
				generic_tools::sleep(2);
				std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
					Caster.get_entity_att()->name,
					Objective.get_entity_att()->name,
					get_base_skill_att().name,
					calculated_damage);
				std::cout << message;

			}

		}
		else
		{
			int reducted_attack = (get_base_skill_att().base_power * (100 - Objective.get_entity_att()->COVERING_REDUCTION) / 100);
			Objective.get_entity_att()->HP -= reducted_attack;
			std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
				Caster.get_entity_att()->name,
				Objective.get_entity_att()->name,
				get_base_skill_att().name,
				reducted_attack);
			std::cout << message;
			generic_tools::sleep(2);
			Objective.set_covering_and_message(false);
		}
	}
}

void Generic_Spell::deffensive_cast(Entity& Objective, Entity& Caster)
{
	if (get_base_skill_att().objective == Objective_Type::ALLYES && get_base_skill_att().special_act != special_action::NONE)
	{
	Caster.get_entity_att()->HP -= get_base_skill_att().hp_cost;
	Caster.get_entity_att()->SP -= get_base_skill_att().sp_cost;
	Caster.check_hp();
	Caster.check_sp();
	std::string message;
	int spell_numbers;
	
	
		switch (get_base_skill_att().special_act)
		{
		case special_action::HEAL:
		{
			if (get_base_skill_att().is_based == is_stats_based::NON_STATS_BASED)
			{
				spell_numbers = get_base_skill_att().base_power;
			}
			else
			{
				spell_numbers = (get_base_skill_att().base_power + (Objective.get_entity_att()->HP * get_base_skill_att().bonifier));
			}
			Objective.get_entity_att()->HP += spell_numbers;
			message = std::format("¡{} ha curado a {} {} de HP!", Caster.get_entity_att()->name, Objective.get_entity_att()->name, spell_numbers);
			break;
		}
		case special_action::BUFFER:
		{
			Objective.add_special_action(*this);
			break;
		}
		default:
			std::cout << "No deberías ver esto xd.";
			generic_tools::sleep(5);
			break;
		}
		std::cout << message;
	}
}

void Generic_Spell::generic_spell_manager(Entity& Objective, Entity& Caster)
{
	if (get_base_skill_att().objective == Objective_Type::ALLYES)
	{
		deffensive_cast(Objective, Caster);
	}
	else
	{
		offensive_cast(Objective, Caster);
	}
}