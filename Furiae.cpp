#include "Furiae.hpp"
#include <format>
#include "generic_tools.hpp"

BaseSkillAttributes furiae_basic_attack

{
	Objective_Type::ENEMIES,
	"Rezo al sello",
	15,
	0,
	0,
	SkillType::HOLY,
	"NONE",
	false,
};

BaseSkillAttributes furiae_generic_spell_1
{
	Objective_Type::ALLYES,
	"Rezo al sello",
	50,
	0,
	20,
	SkillType::HOLY,
	"Furiae reza al sello y reestablece una cantidad pequeña de HP a un aliado",
	false,
	0,
	0,
	special_action::HEAL,
};

BaseSkillAttributes furiae_generic_spell_2
{
	Objective_Type::ENEMIES,
	"Rezo a los custodios", 
	30, 
	10, 
	15, 
	SkillType::FIRE,
	"Furiae reza a los custios y estos golpean quemando a un enemigo.",
	true,
	0.10,
	3
};

BaseSkillAttributes furiae_generic_spell_3
{
	Objective_Type::ALLYES,
	"Plegaria",
	30,
	0,
	15,
	SkillType::HOLY,
	"Furiae realiza una plegaria y potencia a los aliados",
	false,
	0,
	0,
	special_action::BUFFER,
	modified_stat::DEFENSE
};


Furiae::Furiae(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction)
	: Character(name_of, MAXHP, MAXSP, DEFENSE, reduction)
{
	set_weakness(Weakness::DARK);

	Basic_Attack = new BaseSkill(furiae_basic_attack);

	Generic_Spell* pray = new Generic_Spell(furiae_generic_spell_1);
	Generic_Spell* mother = new Generic_Spell(furiae_generic_spell_2);
	Generic_Spell* PRAYPRAY = new Generic_Spell(furiae_generic_spell_3);

	generic_spells_list.push_back(pray);
	generic_spells_list.push_back(mother);
	generic_spells_list.push_back(PRAYPRAY);
};

void Furiae::basic_offensive(Enemy& Objective, const BaseSkillAttributes& attack) {

	if (!Objective.get_covering_status())
	{

		if (!Objective.is_weak(attack.skill_type)) 
		{
			int calculated_damage = (attack.base_power + (Objective.get_entity_att()->HP * 0.10));
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
			int calculated_damage = ((attack.base_power + (Objective.get_entity_att()->HP * 0.12)) + (Objective.get_entity_att()->HP * 0.10));
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
		int reducted_attack = (attack.base_power * (100 - Objective.get_entity_att()->COVERING_REDUCTION) / 100) + (Objective.get_entity_att()->HP * 0.10);
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

	Objective.check_hp();

}