#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "SkillType.hpp"
#include "Entity.hpp"
#include "GenericSpell.hpp"

class Entity;

class Effects 
{
protected:
	Entity* Objective;
	BaseSkill* AttackInstance;
	short turns_remaining; 
public:
	Effects(Entity* Objective_of, BaseSkill* attack_of);
	~Effects();
//EFFECTS 
private:
	void burn();
public:
	void Effects_Manager();
	std::string get_objective_name();
	int get_turns_remaining();
	bool effect_finished();
	SkillType get_effect_type();
};

#pragma once
#endif// EFFECT_HPP