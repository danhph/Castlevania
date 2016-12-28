#include "Start.h"


Start::Start(int x, int y, int width, int height) : BaseObject(eID::START)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	BaseObject::setPhysicsBodySide(eDirection::NONE);
}

void Start::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;
}

void Start::update(float deltatime)
{
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}
}

void Start::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	return;
}

void Start::release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

GVector2 Start::getPosition()
{
	return GVector2(_bound.left, _bound.bottom);
}

float Start::getPositionX()
{
	return _bound.left;
}

float Start::getPositionY()
{
	return _bound.top;
}

void Start::setPosition(GVector3 vector)
{
	_bound.left = vector.x;
	_bound.top = vector.y;
}

void Start::setPosition(float x, float y, float z)
{
	_bound.left = x;
	_bound.top = y;
}

void Start::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

void Start::setPosition(float x, float y)
{
	_bound.left = x;
	_bound.top = y;
}

void Start::setPositionX(float x)
{
	_bound.left = x;
}

void Start::setPositionY(float y)
{
	_bound.right = y;
}

GVector2 Start::getScale()
{
	return VECTOR2ONE;
}

void Start::setScale(GVector2 scale)
{
	// do nothing.
}

void Start::setScale(float scale)
{
	// do nothing.
}

void Start::setScaleX(float sx)
{
	// do nothing.
}

void Start::setScaleY(float sy)
{
	// do nothing.
}

GVector2 Start::getOrigin()
{
	return VECTOR2ZERO;
}

void Start::setOrigin(GVector2 origin)
{
	// do nothing.
}

float Start::getRotate()
{
	return 0.0f;
}

void Start::setRotate(float degree)
{
	// do nothing.
}

void Start::setZIndex(float z)
{
	// do nothing.
}

float Start::getZIndex()
{
	return 1; // hard code
}

GVector2 Start::getAnchorPoint()
{
	return GVector2(_bound.left, _bound.right);
}

RECT Start::getBounding()
{
	return _bound;
}

Start::~Start()
{
}
