#include "StairEnd.h"


StairEnd::StairEnd(int x, int y, int width, int height, bool direct) : BaseObject(eID::STAIR_END)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;

	this->_direct = direct;

	BaseObject::setPhysicsBodySide(eDirection::TOP);
}

bool StairEnd::GetDirection()
{
	return _direct;
}

void StairEnd::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;
}

void StairEnd::update(float deltatime)
{
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}
}

void StairEnd::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	return;
}

void StairEnd::release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

GVector2 StairEnd::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

float StairEnd::getPositionX()
{
	return _bound.left;
}

float StairEnd::getPositionY()
{
	return _bound.top;
}

void StairEnd::setPosition(GVector3 vector)
{
	_bound.left = vector.x;
	_bound.top = vector.y;
}

void StairEnd::setPosition(float x, float y, float z)
{
	_bound.left = x;
	_bound.top = y;
}

void StairEnd::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

void StairEnd::setPosition(float x, float y)
{
	_bound.left = x;
	_bound.top = y;
}

void StairEnd::setPositionX(float x)
{
	_bound.left = x;
}

void StairEnd::setPositionY(float y)
{
	_bound.right = y;
}

GVector2 StairEnd::getScale()
{
	return VECTOR2ONE;
}

void StairEnd::setScale(GVector2 scale)
{
	// do nothing.
}

void StairEnd::setScale(float scale)
{
	// do nothing.
}

void StairEnd::setScaleX(float sx)
{
	// do nothing.
}

void StairEnd::setScaleY(float sy)
{
	// do nothing.
}

GVector2 StairEnd::getOrigin()
{
	return VECTOR2ZERO;
}

void StairEnd::setOrigin(GVector2 origin)
{
	// do nothing.
}

float StairEnd::getRotate()
{
	return 0.0f;
}

void StairEnd::setRotate(float degree)
{
	// do nothing.
}

void StairEnd::setZIndex(float z)
{
	// do nothing.
}

float StairEnd::getZIndex()
{
	return 1; // hard code
}

GVector2 StairEnd::getAnchorPoint()
{
	return GVector2(_bound.left, _bound.right);
}

RECT StairEnd::getBounding()
{
	return _bound;
}

StairEnd::~StairEnd()
{
}
