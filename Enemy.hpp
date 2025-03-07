#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <string>
#include "Character.hpp"
#include "Entity.hpp"
#include "Weakneses.hpp"


class Character;

class Enemy : public Entity {
public:
	Enemy(std::string name_of, int MAXHP, int MAXSP, int DEFENSE, int reduction);
	Generic_Spell* get_spell();
	virtual void basic_offensive(Character& Objective, const BaseSkillAttributes& attack) = 0;
	
};

#endif // ENEMY_HPP