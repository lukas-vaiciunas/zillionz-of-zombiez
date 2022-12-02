#include "WeaponData.h"
#include <fstream>

WeaponData::WeaponData() :
	weapons_()
{
	this->load_("data/weapons.txt");
}

WeaponData &WeaponData::getInstance()
{
	static WeaponData instance;
	return instance;
}

std::vector<Weapon::WeaponId> WeaponData::getWeaponIds() const
{
	std::vector<Weapon::WeaponId> weaponIds;

	for (auto it = weapons_.begin(); it != weapons_.end(); ++it)
	{
		weaponIds.push_back(it->first);
	}

	return weaponIds;
}

const Weapon &WeaponData::getWeapon(Weapon::WeaponId weaponId) const
{
	return weapons_.find(weaponId)->second;
}

void WeaponData::load_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in WeaponData!\n", filePath.c_str());
		return;
	}

	int numWeapons;
	in >> numWeapons;

	while (numWeapons--)
	{
		int weaponId;
		float barrelOffset;
		int numBullets;
		float bulletSpeed;
		float bulletDamage;
		float bulletDurationSecs;
		float bulletSpreadRad;
		float cooldownSecs;
		int bulletTextureId;
		int ejectTextureId;
		int weaponTextureId;
		std::string weaponName;

		in >> weaponId
			>> barrelOffset
			>> numBullets
			>> bulletSpeed
			>> bulletDamage
			>> bulletDurationSecs
			>> bulletSpreadRad
			>> cooldownSecs
			>> bulletTextureId
			>> ejectTextureId
			>> weaponTextureId
			>> weaponName;

		weapons_.emplace(
			weaponId,
			Weapon(
				weaponId,
				0.0f, 0.0f, 0.0f,
				barrelOffset,
				numBullets,
				bulletSpeed,
				bulletDamage,
				bulletDurationSecs,
				bulletSpreadRad,
				cooldownSecs,
				bulletTextureId,
				ejectTextureId,
				TextureData::getInstance().getTexture(weaponTextureId),
				weaponName));
	}

	in.close();
}