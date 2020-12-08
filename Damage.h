/**
 * @file Damage.h
 *
 * @author BDFANS
 *
 * @brief header for Damage struct
 * @version 0.5.0
 *
 *
 * @date 2020-11-27
 *
 */
#pragma once

#include <iostream>

/// Damage is a struct which contains int physical and int magical dmg.
struct Damage {
	int physical = 0; ///< Physical damage can be reduced by defense.
	int magical = 0; ///< Magical damage can't be reduced by defense.

	/**
	 * @brief Construct a new Damage object
	 * 
	 * @param pdmg the input physical damage
	 * @param mdmg the input magicad damage
	 */
	Damage(int pdmg, int mdmg) :physical(pdmg), magical(mdmg) {}

	///adds dmg to both physical and magical damage and return a new damage object
	Damage operator+(const Damage& dmg) {
		Damage Returndmg(physical + dmg.physical, magical + dmg.magical);

		return Returndmg;
	}

	///Adds dmg to both physical and magical damage
	Damage& operator+=(const Damage& dmg) {
		physical += dmg.physical;
		magical += dmg.magical;

		return *this;
	}

	///Multiplies both physical and magical damage by multi
	Damage& operator*=(const int& multi) {
		physical = physical * multi;
		magical = magical * multi;

		return *this;
	}

	///Checks if the two objects physical and magical damage is equal
	bool operator==(const Damage& dmg) const
	{
		return (physical == dmg.physical && magical == dmg.magical);
	}

	/**
	 * @brief Outputs the damage values in the following format
	 * 
	 * "Physical: " << dmg.physical << ", Magical: " << dmg.magical
	 */
	friend std::ostream& operator<<(std::ostream& out, const Damage& dmg) {
		out << "Physical: " << dmg.physical << ", Magical: " << dmg.magical;
		return out;
	}

};