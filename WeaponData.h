#pragma once

#include "Weapon.h"
#include <unordered_map>

class WeaponData
{
public:
	WeaponData(const WeaponData &) = delete;
	WeaponData &operator=(const WeaponData &) = delete;

	static WeaponData &getInstance();

	std::vector<Weapon::WeaponId> getWeaponIds() const;
	const Weapon &getWeapon(Weapon::WeaponId weaponId) const;
private:
	std::unordered_map<Weapon::WeaponId, Weapon> weapons_;

	WeaponData();
	~WeaponData() {}

	void load_(const std::string &filePath);
};