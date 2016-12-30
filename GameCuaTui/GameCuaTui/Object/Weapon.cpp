#include "Weapon.h"

Weapon::Weapon(eID id) : BaseObject(id)
{
	
}

CollisionBody* Weapon::getCollisionBody()
{
	return nullptr;
}
