#include "BirdRange.h"

BirdRange::BirdRange(int x, int y, int width, int height) : BaseObject(eID::BIRD_RANGE)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	BaseObject::setPhysicsBodySide(eDirection::ALL);
	_active = false;
	_direct = false;
	_initY = 0;
}

RECT BirdRange::getBounding()
{
	return _bound;
}

void BirdRange::SetDirect(bool direct)
{
	if (_direct != direct)
		_direct = direct;
}


void BirdRange::release()
{

}

void BirdRange::draw(LPD3DXSPRITE, Viewport*)
{

}

void BirdRange::init()
{
	_initBirdStopWatch = new StopWatch();
}

void BirdRange::update(float deltatime)
{
	if (_active)
	if (_initBirdStopWatch->isTimeLoop(2000))
	{
		auto viewportPos = SceneManager::getInstance()->getCurrentScene()->getViewport()->getPositionWorld();
		viewportPos.y = _initY;
		BaseObject* bird;
		if (_direct)
			bird = new Bird(viewportPos.x, viewportPos.y, _direct);
		else
			bird = new Bird(viewportPos.x + 512, viewportPos.y, _direct);
		bird->init();
		QuadTreeNode::getInstance()->Insert(bird);
		bird = nullptr;
	}
}

bool BirdRange::GetDirect()
{
	return _direct;
}


void BirdRange::Active()
{
	_active = true;
}

void BirdRange::Deactive()
{
	_active = false;
}


BirdRange::~BirdRange()
{

}


void BirdRange::SetInitY(float y)
{
	_initY = y;
}
