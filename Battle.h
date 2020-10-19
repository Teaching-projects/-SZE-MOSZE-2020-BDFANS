/**
 * @file Battle.h
 * @class Battle
 * 
 * @author BDFANS
 * 
 * @brief header for Battle class
 * @version 0.3.0
 * 
 * 
 * @date 2020-10-15
 * 
 */

#pragma once
#include "Unit.h"

/**
 * @brief this function simulates the combat until one of the participant is slain
 * 
 * @param attacker the initiator of the battle
 * @param defender the defender of the battle
 */
void Battle(Unit& attacker, Unit& defender);