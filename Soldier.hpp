#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#pragma once
#include "Enemy.hpp"
#include "Attack.hpp"
#include "vector"
class Soldier : public Enemy {
public:
	Soldier(std::string name_of, unsigned int hp_of, unsigned int sp_of, std::string type = "Soldado", int reduct = 22);

	void Offensive(Character& Objective, const attack_attributes& attack);

	void song();

};
#endif // !SOLDIER_HPP