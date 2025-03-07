#ifndef SPECIALACTION_HPP
#define SPECIALACTION_HPP
#pragma once

#include"BaseSkill.hpp"
#include "Entity.hpp"

class Entity;

class SpecialAction
{
private:
	short turns_remaining = 3;
	int original_stat;
	bool is_active = false;
	//SPECIAL_ACTIONS
private:
	void fixed_buff();

public:
	Entity* Objective;
	BaseSkill* SkillInstance;
	SpecialAction(Entity* Objective_of, BaseSkill* skill);
	void SpecialActionManager();
	void fixed_debuff();
	void restore_stat();
	bool Is_Active();
	special_action get_special_action();
};


#endif //!SPECIALACTIONMANAGER_HPP