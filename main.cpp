#include <locale>
#include <cstdlib>
#include "CombatManager.hpp"

int main() {
	setlocale(LC_CTYPE, "Spanish");
	CombatManager combat;
	combat.command_manager();
}
 