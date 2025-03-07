#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include<iostream>
#include "BaseSkill.hpp"
#include <vector>
#include "Weakneses.hpp"
#include "entity_status.hpp" 
#include "GenericSpell.hpp"
#include "Effect.hpp"
#include "SpecialAction.hpp"

struct entity_att {
	std::string name;
	int HP;
	int SP;
	int MAX_HP;
	int MAX_SP;
	int DEFENSE;
	int COVERING_REDUCTION;
};

class Generic_Spell;
class SpecialAction;
class Effects;

class Entity
{
protected:

	entity_att entity_attribs;
	bool COVERING_STATUS = false;
	entity_status EFFECT_STATUS = IS_NOT_AFFECTED;
	std::vector<Weakness> weakneses_list;
	std::vector<Generic_Spell*> generic_spells_list;
	std::vector<Effects*> effects_buffer;
	std::vector<SpecialAction*> special_act_buffer;

public:
	BaseSkill* Basic_Attack;

public:
	Entity(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction);
	void  print_stats() const;
	entity_att* get_entity_att();
	
	void take_turn();
	void pass_turn();
	bool is_alive() const;
	void check_hp();
	void check_sp();
	void check_effect();
	void add_effect(BaseSkill& new_effect);
	void add_special_action(BaseSkill& new_esp_action);
	void check_special_action();

private:
	bool can_apply_special_action(BaseSkill& skill);
	bool can_apply_effect(BaseSkill& skill);
public:
	bool enough_hp(const BaseSkillAttributes& attack) const;
	bool enough_sp(const BaseSkillAttributes& attack) const;
	
	void set_weakness(Weakness weakness);
	bool is_weak(const SkillType& type_of_attack);

	void set_covering_status(bool cover);

	void set_covering_and_message(bool cover);
	void set_effect_status(entity_status status);
	bool get_covering_status() const;
	bool get_effect_status() const;
	~Entity();

};



#endif //ENTITY_HPP