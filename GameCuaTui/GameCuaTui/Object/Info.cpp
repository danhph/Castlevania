#include "Info.h"
#include "TextSprite.h"
#include <string>
#include <sstream>
#include <iomanip>

eID Info::GetCurrentWeapon()
{
	return _weaponID;
}

void Info::SetWeapon(eID id)
{
	_weaponID = id;

	switch (id)
	{
		case DAGGER:
			{
				_weaponSprite = SpriteManager::getInstance()->getSprite(ITEM);
				_weaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "dagger"));
				_weaponSprite->setPosition(300, 42);
				break;
			}
		case AXE:
			{
				_weaponSprite = SpriteManager::getInstance()->getSprite(ITEM);
				_weaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "axe"));
				_weaponSprite->setPosition(300, 42);
				break;
			}
		case BOOMERANG:
			{
				_weaponSprite = SpriteManager::getInstance()->getSprite(ITEM);
				_weaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "boomerang"));
				_weaponSprite->setPosition(300, 42);
				break;
			}
		default:
			_weaponSprite = nullptr;
			break;
	}
}


Info::Info() : BaseObject(eID::INFO)
{
	_weaponID = WEAPON;
	_weaponSprite = nullptr;
	_maxWeaponSprite = nullptr;
	_maxWeapon = 1;

	_border = SpriteManager::getInstance()->getSprite(BORDER);
	_border->setScale(0.8f);
	_border->setPosition(300, 42);

	_iconEmptyHitPoint = SpriteManager::getInstance()->getSprite(HEAL);
	_iconEmptyHitPoint->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::HEAL, "empty"));
	_iconEmptyHitPoint->setScale(0.85f);

	_iconPlayerHitPoint = SpriteManager::getInstance()->getSprite(HEAL);
	_iconPlayerHitPoint->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::HEAL, "red_blood"));
	_iconPlayerHitPoint->setScale(0.9f);

	_iconEnemyHitPoint = SpriteManager::getInstance()->getSprite(HEAL);
	_iconEnemyHitPoint->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::HEAL, "pink_blood"));
	_iconEnemyHitPoint->setScale(0.9f);

	_iconHeart = SpriteManager::getInstance()->getSprite(eID::HEART_ICON);
	_iconHeart->setScale(SCALE_FACTOR);
	_iconHeart->setPosition(350, 35);

	_textPlayer = new TextSprite(eID::FONTFULL, "PLAYER", GVector2(10, 42));
	_textPlayer->init();
	_textPlayer->setScale(1.6);
	_textPlayer->setOrigin(VECTOR2ZERO);

	_textHeart = new TextSprite(eID::FONTFULL, "- ", GVector2(0, 0));
	_textHeart->init();
	_textHeart->setScale(1.6);
	_textHeart->setOrigin(VECTOR2ZERO);

	_textLife = new TextSprite(eID::FONTFULL, "P- ", GVector2(345, 60));
	_textLife->init();
	_textLife->setScale(1.6);
	_textLife->setOrigin(VECTOR2ZERO);

	_textEnemy = new TextSprite(eID::FONTFULL, "ENEMY", GVector2(10, 60));
	_textEnemy->init();
	_textEnemy->setScale(1.6);
	_textEnemy->setOrigin(VECTOR2ZERO);


	_textScore = new TextSprite(eID::FONTFULL, "SCORE- ", GVector2(10, 20));
	_textScore->init();
	_textScore->setScale(1.6);
	_textScore->setOrigin(VECTOR2ZERO);

	_textTime = new TextSprite(eID::FONTFULL, "STAGE- ", GVector2(200, 20));
	_textTime->init();
	_textTime->setScale(1.6);
	_textTime->setOrigin(VECTOR2ZERO);

	_textStage = new TextSprite(eID::FONTFULL, "STAGE- ", GVector2(380, 20));
	_textStage->init();
	_textStage->setScale(1.6);
	_textStage->setOrigin(VECTOR2ZERO);
}

Info::~Info()
{
}

void Info::init()
{
}

void Info::update(float deltatime)
{
	stringstream ssHeart;
	_textHeart->setPosition(GVector2(_iconHeart->getPosition().x + GAP / 1.4, _iconHeart->getPosition().y + GAP / 1.4));
	ssHeart << setw(2) << setfill('0') << _heartNumber;
	_textHeart->setString("-" + ssHeart.str());

	stringstream ssStage;
	ssStage << setw(2) << setfill('0') << _stageNumber;
	_textStage->setString("STAGE-" + ssStage.str());


	stringstream ssScore;
	ssScore << setw(6) << setfill('0') << _scoreNumber;
	_textScore->setString("SCORE-" + ssScore.str());

	stringstream ssLife;
	ssLife << setw(2) << setfill('0') << _lifeNumber;
	_textLife->setString("P-" + ssLife.str());


	int time = _timeNumber - ((int)GameTime::getInstance()->getTotalGameTime() - _beginTime) / 1000;

	stringstream ssTime;
	ssTime << setw(4) << setfill('0') << time;
	_textTime->setString("TIME " + ssTime.str());
}

void Info::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_border->render(spriteHandle);
	_iconHeart->render(spriteHandle);
	_textHeart->draw(spriteHandle);

	_textStage->draw(spriteHandle);

	_textTime->draw(spriteHandle);

	_textScore->draw(spriteHandle);

	_textLife->draw(spriteHandle);

	_textPlayer->draw(spriteHandle);

	if (_weaponSprite != nullptr)
		_weaponSprite->render(spriteHandle);

	if (_maxWeaponSprite != nullptr)
		_maxWeaponSprite->render(spriteHandle);

	auto posPlayer = GVector2(100, 34);
	for (int i = 0; i < 16; i++)
	{
		if (i < _playerHitPointNumber)
		{
			_iconPlayerHitPoint->setPosition(posPlayer);
			_iconPlayerHitPoint->render(spriteHandle);
		}
		else
		{
			_iconEmptyHitPoint->setPosition(posPlayer);
			_iconEmptyHitPoint->render(spriteHandle);
		}

		posPlayer = posPlayer + GVector2(10, 0);
	}

	_textEnemy->draw(spriteHandle);
	auto posEnemy = GVector2(100, 53);
	for (int i = 0; i < 16; i++)
	{
		if (i < _enemyHitPointNumber)
		{
			_iconEnemyHitPoint->setPosition(posEnemy);
			_iconEnemyHitPoint->render(spriteHandle);
		}
		else
		{
			_iconEmptyHitPoint->setPosition(posEnemy);
			_iconEmptyHitPoint->render(spriteHandle);
		}

		posEnemy = posEnemy + GVector2(10, 0);
	}
}

void Info::release()
{
	SAFE_DELETE(_iconPlayerHitPoint);
	SAFE_DELETE(_textPlayer);
	SAFE_DELETE(_iconEnemyHitPoint);
	SAFE_DELETE(_textEnemy);
	SAFE_DELETE(_iconHeart);
	SAFE_DELETE(_textHeart);
	SAFE_DELETE(_textLife);
	SAFE_DELETE(_textScore);
	SAFE_DELETE(_textStage);
}

int Info::GetEnemyHitPoint()
{
	return _enemyHitPointNumber;
}

int Info::GetHeart()
{
	return _heartNumber;
}

int Info::GetLife()
{
	return _lifeNumber;
}

int Info::GetPlayerHitPoint()
{
	return _playerHitPointNumber;
}

int Info::GetScore()
{
	return _scoreNumber;
}

int Info::GetStage()
{
	return _stageNumber;
}

int Info::GetTime()
{
	return _timeNumber - ((int)GameTime::getInstance()->getTotalGameTime() - _beginTime) / 1000;
}


void Info::SetEnemyHitPoint(int number)
{
	_enemyHitPointNumber = number;
}

void Info::SetHeart(int number)
{
	_heartNumber = number;
	if (_heartNumber >= 100)
		_heartNumber = 99;
}

void Info::SetLife(int number)
{
	_lifeNumber = number;
}

void Info::SetPlayerHitPoint(int number)
{
	_playerHitPointNumber = number;
	if (_playerHitPointNumber > 16)
		_playerHitPointNumber = 16;
}

void Info::SetScore(int number)
{
	_scoreNumber = number;
}

void Info::SetStage(int number)
{
	_stageNumber = number;
}

void Info::SetTime(int number)
{
	_timeNumber = number + 1;
	_beginTime = GameTime::getInstance()->getTotalGameTime();
}

void Info::SetMaxWeapon(int num)
{
	switch(num)
	{
	case 2:
		_maxWeaponSprite = SpriteManager::getInstance()->getSprite(ITEM);
		_maxWeaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "small2"));
		_maxWeaponSprite->setPosition(420, 45);
		break;
	case 3:
		_maxWeaponSprite = SpriteManager::getInstance()->getSprite(ITEM);
		_maxWeaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "small3"));
		_maxWeaponSprite->setPosition(420, 45);
		break;
	default:
		num = 1;
		_maxWeaponSprite = nullptr;
		break;
	}
	_maxWeapon = num;
}

int Info::GetMaxWeapon()
{
	return _maxWeapon;
}
