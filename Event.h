#pragma once

#include "EventType.h"
#include "DriverStateType.h"
#include "Weapon.h"

class Event
{
public:
	Event(EventType type) :
		type_(type)
	{}

	virtual ~Event() {}

	EventType getType() const
	{
		return type_;
	}
private:
	EventType type_;
};

class EventChangeDriverState : public Event
{
public:
	EventChangeDriverState(DriverStateType driverStateType) :
		Event(EventType::ChangeDriverState),
		driverStateType_(driverStateType)
	{}

	DriverStateType getDriverStateType() const
	{
		return driverStateType_;
	}
private:
	DriverStateType driverStateType_;
};

class EventQuit : public Event
{
public:
	EventQuit() :
		Event(EventType::Quit)
	{}
};

class EventUpdateHealthBar : public Event
{
public:
	EventUpdateHealthBar() :
		Event(EventType::UpdateHealthBar)
	{}
};

class EventPlayerWasKilled : public Event
{
public:
	EventPlayerWasKilled() :
		Event(EventType::PlayerWasKilled)
	{}
};

class EventEnemyWasKilled : public Event
{
public:
	EventEnemyWasKilled() :
		Event(EventType::EnemyWasKilled)
	{}
};

class EventPickupWeapon : public Event
{
public:
	EventPickupWeapon(Weapon::WeaponId weaponId) :
		Event(EventType::PickupWeapon),
		weaponId_(weaponId)
	{}

	Weapon::WeaponId getWeaponId() const
	{
		return weaponId_;
	}
private:
	Weapon::WeaponId weaponId_;
};

class EventDropWeapon : public Event
{
public:
	EventDropWeapon(float x, float y, float maxY, Weapon::WeaponId weaponId) :
		Event(EventType::DropWeapon),
		x_(x),
		y_(y),
		maxY_(maxY),
		weaponId_(weaponId)
	{}

	float getX() const
	{
		return x_;
	}

	float getY() const
	{
		return y_;
	}

	float getMaxY() const
	{
		return maxY_;
	}

	Weapon::WeaponId getWeaponId() const
	{
		return weaponId_;
	}
private:
	float x_;
	float y_;
	float maxY_;
	Weapon::WeaponId weaponId_;
};

class EventDropFood : public Event
{
public:
	EventDropFood(float x, float y, float maxY) :
		Event(EventType::DropFood),
		x_(x),
		y_(y),
		maxY_(maxY)
	{}

	float getX() const
	{
		return x_;
	}

	float getY() const
	{
		return y_;
	}

	float getMaxY() const
	{
		return maxY_;
	}
private:
	float x_;
	float y_;
	float maxY_;
};

class EventHealPlayer : public Event
{
public:
	EventHealPlayer(float health) :
		Event(EventType::HealPlayer),
		health_(health)
	{}

	float getHealth() const
	{
		return health_;
	}
private:
	float health_;
};