#include "BaseSkill.hpp"
#include <format>

BaseSkill::BaseSkill(BaseSkillAttributes& att) : base_skill_att{ att } {};
	

void BaseSkill::print_all_att() const {

	std::string message = std::format("\nNombre{}:\n Tipo: {}\nPoder: {}\n HP: {}\n SP: {}\nDescripción: {}\n", base_skill_att.name,
		base_skill_att.element_string,
		base_skill_att.base_power,
		base_skill_att.hp_cost,
		base_skill_att.sp_cost,
		base_skill_att.description);
	std::cout << message;

}

const BaseSkillAttributes& BaseSkill::get_base_skill_att() const
{
	return base_skill_att;
}

