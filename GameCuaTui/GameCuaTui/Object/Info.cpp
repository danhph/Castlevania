#include "Info.h"
#include "TextSprite.h"
#include <string>
Info::Info(GVector2 position, int number) : EmptyObject(eID::LIFE_ICON, position, 0, 0)
{
	_lifeNumber = number;
	_iconLife = SpriteManager::getInstance()->getSprite(eID::LIFE_ICON);
	_iconLife->setScale(SCALE_FACTOR);
	_iconLife->setPosition(position.x, position.y);

	_textLife = new TextSprite(eID::FONTFULL, "- ", GVector2(0, 280));
	_textLife->init();
	_textLife->setScale(1.6);
	_textLife->setOrigin(VECTOR2ZERO);
}

Info::~Info()
{
}

void Info::init()
{
	this->setScale(SCALE_FACTOR);
}

void Info::update(float deltatime)
{
}

void Info::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_iconLife->render(spriteHandle);
	_textLife->setPosition(GVector2(_iconLife->getPosition().x + GAP, _iconLife->getPosition().y + GAP/1.4));
	_textLife->setString("-0" + to_string(_lifeNumber));
	_textLife->draw(spriteHandle);

}

void Info::release()
{
	SAFE_DELETE(_iconLife);
	SAFE_DELETE(_textLife);
}

void Info::setLifeNumber(int number)
{
	_lifeNumber = number;
}

int Info::getLifeNumber()
{
	return _lifeNumber;
}
