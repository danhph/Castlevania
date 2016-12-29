#include "Revive.h"

Revive::Revive(int x, int y, int width, int height) : BaseObject(eID::REVIVE)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	BaseObject::setPhysicsBodySide(eDirection::ALL);
}

RECT Revive::getBounding()
{
	return _bound;
}

void Revive::release()
{

}

void Revive::draw(LPD3DXSPRITE, Viewport*)
{

}

GVector2 Revive::getPosition()
{
	return GVector2(_bound.left, _bound.bottom);
}

void Revive::init()
{

}

void Revive::update(float deltatime)
{

}

Revive::~Revive()
{

}


