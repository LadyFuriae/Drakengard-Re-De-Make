#ifndef GENERICSPELL_HPP
#define GENERICSPELL_HPP
#pragma once
#include "Entity.hpp"
#include "BaseSkill.hpp"

class Entity;

class Generic_Spell : public BaseSkill
{

private:
	void offensive_cast(Entity& Objective, Entity& Caster);

	void deffensive_cast(Entity& Objective, Entity& Caster);
public:
	Generic_Spell(BaseSkillAttributes& att);
	void generic_spell_manager(Entity& Objective, Entity& Caster);
	
};



#endif //GENERICSPELL_HPP
