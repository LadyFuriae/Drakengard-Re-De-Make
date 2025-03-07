#pragma once
#include "Caim.hpp"
#include "generic_tools.hpp"
#include <format>

BaseSkillAttributes basic_attack_caim_att
{ 
	Objective_Type::ENEMIES,
	"su espada", 
	10, 
	0, 
	0, 
	SkillType::PHYSICAL,  
	"Inflije daño mínimo a un enemigo de tipo físico", 
	false 
};

BaseSkillAttributes caim_generic_spell_1
{
	Objective_Type::ENEMIES,
	"Ira de Angelus", 
	30, 
	10, 
	15, 
	SkillType::FIRE, 
	"Caim invoca Angelus y quema a un enemigo", 
	true,
	0.15,
	3
};

BaseSkillAttributes caim_generic_spell_2
{
	Objective_Type::ENEMIES,
	"Grito de Raphael",
	30,
	0,
	15,
	SkillType::DARK,
	"Caim invoca Raphael desde otra dimensión y maldice a un enemigo",
	false,
	0,
	0,
	special_action::DEBUFFER,
	modified_stat::DEFENSE
};

Caim::Caim(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction)
	: Character(name_of, MAXHP, MAXSP, DEFENSE, reduction) 
{
	set_weakness(Weakness::DARK);
	Basic_Attack = new BaseSkill(basic_attack_caim_att);

	Generic_Spell* angelus = new Generic_Spell(caim_generic_spell_1);
	Generic_Spell* raphael = new Generic_Spell(caim_generic_spell_2);
	generic_spells_list.push_back(angelus);
	generic_spells_list.push_back(raphael);
}

void Caim::basic_offensive(Enemy& Objective, const BaseSkillAttributes& attack) 
{
	if (!Objective.get_covering_status()) {
		if (!Objective.is_weak(attack.skill_type)) {
			int calculated_damage = (attack.base_power + (Objective.get_entity_att()->HP * 0.15));
			Objective.get_entity_att()->HP -= calculated_damage;
			std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
																							entity_attribs.name,
																							Objective.get_entity_att()->name,
																							attack.name,
																							calculated_damage);
			std::cout << message;
		}
		else
		{
			int calculated_damage = ((attack.base_power + (Objective.get_entity_att()->HP * 0.15)) + (Objective.get_entity_att()->HP * 0.15));
			Objective.get_entity_att()->HP -= calculated_damage;
			std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
																							entity_attribs.name,
																							Objective.get_entity_att()->name,
																							attack.name,
																							calculated_damage);
			std::cout << "\n!Es débil!\n";
			generic_tools::sleep(2);
			std::cout << message;
		}
	}
	else
	{
		int reducted_attack = (attack.base_power * (100 - Objective.get_entity_att()->COVERING_REDUCTION) / 100) + (Objective.get_entity_att()->HP * 0.15);
		Objective.get_entity_att()->HP -= reducted_attack;
		std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
																						entity_attribs.name,
																						Objective.get_entity_att()->name,
																						attack.name,
																						reducted_attack);
		std::cout << message;
		generic_tools::sleep(2);
		Objective.set_covering_and_message(false);
	}
}