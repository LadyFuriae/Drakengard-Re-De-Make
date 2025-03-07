#ifndef CHARACTER_HPP 
#define CHARACTER_HPP
#pragma once
#include "Entity.hpp"
#include "Enemy.hpp"

class Enemy;

class Character : public Entity {

public:
	Character(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction);
	Generic_Spell* get_spell();
	virtual void basic_offensive(Enemy& Objective, const BaseSkillAttributes& attack) = 0;

};

#endif // CHARACTER_HPP