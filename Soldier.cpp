#include "Soldier.hpp"
#include "generic_tools.hpp"
#include <format>
#include "SkillType.hpp"
BaseSkillAttributes basic_attack
{
	Objective_Type::ENEMIES,
	"su mondá",             
	50,                     
	0,                      
	0,                      
	SkillType::PHYSICAL,    
	"NONE",                 
	false,                  
};

BaseSkillAttributes soldier_generic_spell1
{
	Objective_Type::ENEMIES,
	"Bola de fuego",
	15,
	10,
	15,
	SkillType::FIRE,
	"Inflije daño de fuego quemando a sus enemigos",
	true,
	0.12,
	3,
};

BaseSkillAttributes soldier_generic_spell2
{
	Objective_Type::ALLYES,
	"Rezo a Manah",
	30,
	0,
	30,
	SkillType::DARK,
	"Dígale a esa mamu que le chupe la mondá",
	false,
	0.0,
	3,
	special_action::BUFFER,
	modified_stat::DEFENSE
};

BaseSkillAttributes soldier_generic_spell3
{
	Objective_Type::ENEMIES,
	"Rezo a mi concha",
	30,
	0,
	30,
	SkillType::DARK,
	"Dígale a esa mamu que le chupe la mondá",
	false,
	0.0,
	3,
	special_action::DEBUFFER,
	modified_stat::DEFENSE
};

Soldier::Soldier(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction)
	: Enemy(name_of, MAXHP, MAXSP, DEFENSE, reduction)
{
	set_weakness(Weakness::DARK);
	Basic_Attack = new BaseSkill(basic_attack);

	Generic_Spell* fuego = new Generic_Spell(soldier_generic_spell1);
	Generic_Spell* manah = new Generic_Spell(soldier_generic_spell2);
	Generic_Spell* concha = new Generic_Spell(soldier_generic_spell3);
	generic_spells_list.push_back(fuego);
	generic_spells_list.push_back(manah);
	generic_spells_list.push_back(concha);
}

void Soldier::basic_offensive(Character& Objective, const BaseSkillAttributes& attack)
{
	if (!Objective.get_covering_status()) {
		if (!Objective.is_weak(attack.skill_type)) {
			int calculated_damage = (attack.base_power + (Objective.get_entity_att()->HP * 0.13));
			Objective.get_entity_att()->HP -= calculated_damage;
			get_entity_att()->SP -= attack.sp_cost;
			get_entity_att()->HP -= attack.hp_cost;
			std::string message = std::format("\n{} ataca a {} con {} e inflije {} daño!\n",
				entity_attribs.name,
				Objective.get_entity_att()->name,
				attack.name,
				calculated_damage);
			std::cout << message;
		}
		else
		{
			int calculated_damage = ((attack.base_power + (Objective.get_entity_att()->HP * 0.13)) + (Objective.get_entity_att()->HP * 0.13));
			Objective.get_entity_att()->HP -= calculated_damage;
			get_entity_att()->SP -= attack.sp_cost;
			get_entity_att()->HP -= attack.hp_cost;
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
		int reducted_attack = (attack.base_power * (100 - Objective.get_entity_att()->COVERING_REDUCTION) / 100) + (Objective.get_entity_att()->HP * 0.13);
		Objective.get_entity_att()->HP -= reducted_attack;
		get_entity_att()->SP -= attack.sp_cost;
		get_entity_att()->HP -= attack.hp_cost;
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

void Soldier::song() {
	std::cout << "owo";
}