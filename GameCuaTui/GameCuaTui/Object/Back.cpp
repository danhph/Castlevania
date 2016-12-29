#include "Back.h"

Back::Back(int x, int y, int width, int height) : BaseObject(eID::BACK)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	BaseObject::setPhysicsBodySide(eDirection::ALL);
}

RECT Back::getBounding()
{
	return _bound;
}

eID Back::getNextStage()
{
	return _nextStage;
}

void Back::setNextStage(eID id)
{
	_nextStage = id;
}



void Back::release()
{

}

void Back::draw(LPD3DXSPRITE, Viewport*)
{

}

void Back::init()
{

}

void Back::update(float deltatime)
{

}

Back::~Back()
{

}


