#pragma once
#include <format>
#include "Effect.hpp"
#include "SkillType.hpp"
#include "generic_tools.hpp"
#include "entity_status.hpp"
Effects::Effects(Entity* Objective_of, BaseSkill* attack_of) : Objective(Objective_of), AttackInstance(attack_of)
{
	Objective->set_effect_status(IS_AFFECTED);
	turns_remaining = AttackInstance->get_base_skill_att().turns_of_effect;

}

Effects::~Effects()
{
	Objective = nullptr;
	AttackInstance = nullptr;
}

//EFFECTS

void Effects::burn() 
{
	int burn_damage = Objective->get_entity_att()->HP * 0.10;
	Objective->get_entity_att()->HP -= burn_damage;
	std::string message = std::format("¡{} se ha quemado y ha sufrido {} de daño!", Objective->get_entity_att()->name, burn_damage);
	std::cout << message;
}

//******************************************************************************************************

void Effects::Effects_Manager()
{
	if (turns_remaining > 0)
	{
		switch (AttackInstance->get_base_skill_att().skill_type)
		{
		case SkillType::FIRE:
			{
				burn();
				break;
			}
			default: 
			{
				std::cout << "\nEFFECT NOT IMPLEMENTED YET.\n";
				generic_tools::sleep(1);
				break;
			}
		}
	turns_remaining -= 1;

	}
}

std::string Effects::get_objective_name()
{
	return Objective->get_entity_att()->name;
}

int Effects::get_turns_remaining()
{
	return turns_remaining;
}

bool Effects::effect_finished()
{
	return turns_remaining <= 0;
}

SkillType Effects::get_effect_type()
{
	return AttackInstance->get_base_skill_att().skill_type;
}