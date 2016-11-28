#ifndef __COLLISION_BODY__
#define __COLLISION_BODY__

#include "BaseObject.h"
#include "../Framework/IComponent.h"

class CollisionEventArg : public EventArg
{
public:
	CollisionEventArg(BaseObject* object)
	{
		_otherObject = object;
		_sideCollision = eDirection::NONE;
	}

	BaseObject* _otherObject;
	eDirection _sideCollision;
private:

};

[event_source(native)]
class CollisionBody : public IComponent
{
public:
	CollisionBody(BaseObject* target);
	CollisionBody(BaseObject* target, RECT bodyRect);

	~CollisionBody();

	void checkCollision(BaseObject* otherObject, float dt, bool updatePosition = true);

	bool checkCollision(BaseObject* otherObject, eDirection& direction, float dt, bool updatePosition = true);

	bool isColliding(BaseObject* otherObject);

	void update(float dt);

	__event void onCollisionBegin(CollisionEventArg* e);
	__event void onCollisionEnd(CollisionEventArg* e);

	RECT getCollisionRect();

	void updateTargetPosition(BaseObject* otherObject, eDirection direction, bool withVelocity, GVector2 move = GVector2(0, 0));

	float isCollide(BaseObject* otherObject, eDirection& direction, float dt);
	bool isColliding(RECT myRect, RECT otherRect);
	bool isColliding(BaseObject* otherObject, float& moveX, float& moveY, float dt);

	RECT getSweptBroadphaseRect(BaseObject* object, float dt);
	eDirection getSide(BaseObject* otherObject);

private:
	BaseObject* _target;
	RECT _collisionBodyRect;

	float _dxEntry, _dyEntry, _dxExit, _dyExit;
	float _txEntry, _tyEntry, _txExit, _tyExit;

	map<BaseObject*, bool> _listColliding;

};

#endif // !__COLLISION_BODY__
