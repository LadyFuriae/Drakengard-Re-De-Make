﻿#include <locale>
#include <cstdlib>
#include "CombatManager.hpp"

//TODO: FIX MEMORY LEAK IN SPECIAL ACTION


int main() {
	setlocale(LC_CTYPE, "Spanish");
	CombatManager combat;
	combat.command_manager();
}
 