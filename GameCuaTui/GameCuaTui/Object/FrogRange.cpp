#include "FrogRange.h"

FrogRange::FrogRange(int x, int y, int width, int height) : BaseObject(eID::FROG_RANGE)
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

RECT FrogRange::getBounding()
{
	return _bound;
}

void FrogRange::SetDirect(bool direct)
{
	if (_direct != direct)
		_direct = direct;
}


void FrogRange::release()
{
}

void FrogRange::draw(LPD3DXSPRITE, Viewport*)
{
}

void FrogRange::init()
{
	_initFrogStopWatch = new StopWatch();
}

void FrogRange::update(float deltatime)
{
	if (_active)
		if (_initFrog && _initFrogStopWatch->isTimeLoop(0))
		{
			auto viewportPos = SceneManager::getInstance()->getCurrentScene()->getViewport()->getPositionWorld();
			viewportPos.y = _initY;
			auto frog = new Frog(this->_bound.left, this->_bound.top);
			frog->init();
			QuadTreeNode::getInstance()->Insert(frog);
			frog->setPosition(viewportPos.x + 512 - 64, viewportPos.y);
			frog = nullptr;
			_initFrogStopWatch->isTimeLoop(10000);
			_initFrog = false;
		}
}

bool FrogRange::GetDirect()
{
	return _direct;
}


void FrogRange::Active()
{
	_active = true;
	_initFrog = true;
}

void FrogRange::Deactive()
{
	_active = false;
}


FrogRange::~FrogRange()
{
}


void FrogRange::SetInitY(float y)
{
	_initY = y;
}
