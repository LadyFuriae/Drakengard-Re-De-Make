#pragma once
#include "Entity.hpp"
#include <format>
#include "generic_tools.hpp"

Entity::Entity(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction)
	: entity_attribs
	{ 
		name_of,
		0, 
		0,
		MAXHP,
		MAXSP,
		DEFENSE, 
		reduction 
	} 
{
	entity_attribs.HP = MAXHP;
	entity_attribs.SP = MAXSP;
};

Entity::~Entity() 
{
	weakneses_list.clear();
	generic_spells_list.clear();
}

void Entity::print_stats() const {

	std::string message = std::format("\nNombre: {}\nHP: {}/{}\nSP: {}/{}\n", entity_attribs.name,
																		entity_attribs.HP,
																		entity_attribs.MAX_HP,
																		entity_attribs.SP,
																		entity_attribs.MAX_SP);
	std::cout << message;
}

entity_att* Entity::get_entity_att() {
	return &entity_attribs;
}

void Entity::take_turn() {
	std::string message = std::format("\n¡Turno de {}!\n", entity_attribs.name);
	std::cout << message;
}

void Entity::pass_turn() {
	std::string message = std::format("\n¡{} pasa turno!\n", entity_attribs.name);
	std::cout << message;
}

bool Entity::is_alive() const {
	return entity_attribs.HP > 0;
}

void Entity::check_hp() {
	if (entity_attribs.HP < 0) entity_attribs.HP = 0;
	if (entity_attribs.HP > entity_attribs.MAX_HP) entity_attribs.HP = entity_attribs.MAX_HP;
}
void Entity::check_sp() {
	if (entity_attribs.SP < 0) entity_attribs.SP = 0;
	if (entity_attribs.SP > entity_attribs.MAX_SP) entity_attribs.SP = entity_attribs.MAX_SP;
}

void Entity::check_effect()
{
	for (auto iterator = effects_buffer.begin(); iterator != effects_buffer.end();)
	{
		Effects* effect = *iterator;

		if (effect->effect_finished())
		{
			delete effect;
			iterator = effects_buffer.erase(iterator);
		}
		else
		{
			effect->Effects_Manager();
		}
		if (!(iterator == effects_buffer.end())) ++iterator; //Fixes vector subscript out of range
	}
}

bool Entity::can_apply_effect(BaseSkill& skill)
{
	for (Effects* effect : effects_buffer)
	{
		if (effect->get_effect_type() == skill.get_base_skill_att().skill_type)
		{
			return false;
		}
	}
	return true;
}

void Entity::add_effect(BaseSkill& new_effect)
{
	if (can_apply_effect(new_effect))
	{
		Effects* effect = new Effects(this, &new_effect);
		effects_buffer.push_back(effect);
		set_effect_status(IS_AFFECTED);
		std::string message = std::format("\n¡{} ha sufrido un efecto de estado!", get_entity_att()->name);
		std::cout << message;
		generic_tools::sleep(5);
	}
	else { return; }

}

void Entity::add_special_action(BaseSkill& new_esp_action)
{
	std::string message;
	if (can_apply_special_action(new_esp_action)) 
	{
		SpecialAction* new_action = new SpecialAction(this, &new_esp_action);
		special_act_buffer.push_back(new_action);
		message = format("\n{} has been affected!", get_entity_att()->name);
	}
	else
	{
		message = format("\n{} is already affected!", get_entity_att()->name);
		std::cout << message;
		generic_tools::sleep(2);
	}
	std::cout << message;
}

void Entity::check_special_action()
{
	for (auto iterator = special_act_buffer.begin(); iterator != special_act_buffer.end();)
	{
		SpecialAction* special_action = *iterator;

		if (!special_action->Is_Active())
		{
			delete special_action;
			iterator = special_act_buffer.erase(iterator);
		}
		else
		{
			special_action->SpecialActionManager();
		}
		if (!(iterator == special_act_buffer.end())) ++iterator; //Fixes vector subscript out of range
	}
}

bool Entity::can_apply_special_action(BaseSkill& skill)
{
	for (SpecialAction* special_action : special_act_buffer)
	{
		if (special_action->get_special_action() == skill.get_base_skill_att().special_act)
		{
			return false;
		}
	}
	return true;
}


bool Entity::enough_hp(const BaseSkillAttributes& attack) const 
{
	return (entity_attribs.HP > attack.hp_cost);
}

bool Entity::enough_sp(const BaseSkillAttributes& attack) const 
{
	return (entity_attribs.SP > attack.sp_cost);
}

void Entity::set_weakness(Weakness weakness) 
{
	weakneses_list.push_back(weakness);
}

bool Entity::is_weak(const SkillType&type_of_attack)
{
	for (Weakness weakness : weakneses_list)
	{
		if (static_cast<unsigned char>(weakness) == static_cast<unsigned char>(type_of_attack))
		{
			return true;
		}
	}
	return false;
}

void Entity::set_covering_status(bool cover) {
	COVERING_STATUS = cover;
}

void Entity::set_covering_and_message(bool cover) {
	COVERING_STATUS = cover;
	if (COVERING_STATUS) 
	{
		std::string message = std::format("\n¡{} está en defensa!\n", entity_attribs.name);
		std::cout << message;
	}
	else 
	{
		std::string message = std::format("\n¡{} ya no está en defensa!\n", entity_attribs.name);
		std::cout << message;
	}
}

void Entity::set_effect_status(entity_status status)
{
	EFFECT_STATUS = status;
}

bool Entity::get_covering_status() const {
	return COVERING_STATUS;
}

bool Entity::get_effect_status() const 
{
	return EFFECT_STATUS;
}
