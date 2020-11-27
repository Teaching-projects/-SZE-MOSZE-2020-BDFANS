#pragma once

#include <iostream>

/// Damage is a struct which contains int physical and int magical dmg.
struct Damage {
	int physical = 0; ///< Physical damage can be reduced by defense.
	int magical = 0; ///< Magical damage can't be reduced by defense.

	Damage operator+(const Damage& dmg) {
		Damage Returndmg;
		Returndmg.physical = physical + dmg.physical;
		Returndmg.magical = magical + dmg.magical;

		return Returndmg;
	}

	Damage& operator+=(const Damage& dmg) {
		physical += dmg.physical;
		magical += dmg.magical;

		return *this;
	}

	Damage& operator*=(const Damage& dmg) {
		physical += dmg.physical;
		magical += dmg.magical;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Damage& dmg) {
		out << "Physical: " << dmg.physical << ", Magical: " << dmg.magical;
		return out;
	}

};