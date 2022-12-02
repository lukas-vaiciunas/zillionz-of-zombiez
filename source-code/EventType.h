#pragma once

#include <cinttypes>

enum class EventType : uint8_t
{
	ChangeDriverState,
	Quit,
	UpdateHealthBar,
	PlayerWasKilled,
	EnemyWasKilled,
	PickupWeapon,
	DropWeapon,
	DropFood,
	HealPlayer
};