#ifndef SKILLTYPE_HPP
#define SKILLTYPE_HPP

enum class SkillType : unsigned char
{
	NONE,
	PHYSICAL,
	FIRE,
	WATER,
	HOLY,
	DARK,
};

enum class Element : unsigned char
{
	NONE,
	PHYSICAL,
	FIRE,
	WATER,
	HOLY,
	DARK,
};

enum class Objective_Type : bool
{
	ALLYES,
	ENEMIES,
};

enum class is_stats_based : bool
{
	NON_STATS_BASED,
	STATS_BASED
};

enum class special_action : unsigned char 
{	
	NONE,
	HEAL,
	BUFFER,
	DEBUFFER
};

enum class modified_stat : unsigned char
{
	NONE,
	DEFENSE,
};
#pragma once
#endif //SKILLTYPE_HPP