#include "Stair.h"


Stair::Stair(int x, int y, int width, int height, int step, bool direct) : BaseObject(eID::STAIR)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;

	this->_step = step;
	this->_direct = direct;

	BaseObject::setPhysicsBodySide(eDirection::TOP_BOTTOM);
}

int Stair::GetStep()
{
	return _step;
}

bool Stair::GetDirection()
{
	return _direct;
}

void Stair::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;
}

void Stair::update(float deltatime)
{
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}
}

void Stair::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	return;
}

void Stair::release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

GVector2 Stair::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

float Stair::getPositionX()
{
	return _bound.left;
}

float Stair::getPositionY()
{
	return _bound.top;
}

void Stair::setPosition(GVector3 vector)
{
	_bound.left = vector.x;
	_bound.top = vector.y;
}

void Stair::setPosition(float x, float y, float z)
{
	_bound.left = x;
	_bound.top = y;
}

void Stair::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

void Stair::setPosition(float x, float y)
{
	_bound.left = x;
	_bound.top = y;
}

void Stair::setPositionX(float x)
{
	_bound.left = x;
}

void Stair::setPositionY(float y)
{
	_bound.right = y;
}

GVector2 Stair::getScale()
{
	return VECTOR2ONE;
}

void Stair::setScale(GVector2 scale)
{
	// do nothing.
}

void Stair::setScale(float scale)
{
	// do nothing.
}

void Stair::setScaleX(float sx)
{
	// do nothing.
}

void Stair::setScaleY(float sy)
{
	// do nothing.
}

GVector2 Stair::getOrigin()
{
	return VECTOR2ZERO;
}

void Stair::setOrigin(GVector2 origin)
{
	// do nothing.
}

float Stair::getRotate()
{
	return 0.0f;
}

void Stair::setRotate(float degree)
{
	// do nothing.
}

void Stair::setZIndex(float z)
{
	// do nothing.
}

float Stair::getZIndex()
{
	return 1; // hard code
}

GVector2 Stair::getAnchorPoint()
{
	return GVector2(_bound.left, _bound.right);
}

RECT Stair::getBounding()
{
	return _bound;
}

Stair::~Stair()
{
}
