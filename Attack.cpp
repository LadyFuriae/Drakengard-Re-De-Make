#include "Attack.hpp"
#include <format>
void Attack::print_att() const {

	std::string message = std::format("\n{}:\n Tipo de daño: {}\n Daño: {}\n HP: {}\n SP: {}\n", attack_att.name, 
																								 attack_att.type, 
																								 attack_att.damage, 
																								 attack_att.hp_cost, 
																								 attack_att.sp_cost);
	std::cout << message;
	
}
 
const attack_attributes& Attack:: get_attack_att() const {
	return attack_att;
}