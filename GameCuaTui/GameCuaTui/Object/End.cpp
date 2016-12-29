#include "End.h"

End::End(int x, int y, int width, int height) : BaseObject(eID::END)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	BaseObject::setPhysicsBodySide(eDirection::ALL);
}

RECT End::getBounding()
{
	return _bound;
}

eID End::getNextStage()
{
	return _nextStage;
}

void End::setNextStage(eID id)
{
	_nextStage = id;
}



void End::release()
{

}

void End::draw(LPD3DXSPRITE, Viewport*)
{
	
}

void End::init()
{
	
}

void End::update(float deltatime)
{
	
}

End::~End()
{
	
}


GVector2 End::getPosition()
{
	return GVector2(_bound.left, _bound.bottom);
}