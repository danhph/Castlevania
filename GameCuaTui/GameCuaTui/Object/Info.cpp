#include "Info.h"
#include "TextSprite.h"
#include <string>
#include <sstream>
#include <iomanip>

Info::Info() : BaseObject(eID::INFO)
{
	_iconHeart = SpriteManager::getInstance()->getSprite(eID::HEART_ICON);
	_iconHeart->setScale(SCALE_FACTOR);
	_iconHeart->setPosition(350, 35);

	_textPlayer = new TextSprite(eID::FONTFULL, "PLAYER", GVector2(10, 45));
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
}

void Info::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	stringstream ssHeart;
	_iconHeart->render(spriteHandle);
	_textHeart->setPosition(GVector2(_iconHeart->getPosition().x + GAP / 1.4, _iconHeart->getPosition().y + GAP / 1.4));
	ssHeart << setw(2) << setfill('0') << _heartNumber;
	_textHeart->setString("-" + ssHeart.str());
	_textHeart->draw(spriteHandle);

	stringstream ssStage;
	ssStage << setw(2) << setfill('0') << _stageNumber;
	_textStage->setString("STAGE-" + ssStage.str());
	_textStage->draw(spriteHandle);

	stringstream ssTime;
	ssTime << setw(4) << setfill('0') << _timeNumber;
	_textTime->setString("TIME " + ssTime.str());
	_textTime->draw(spriteHandle);

	stringstream ssScore;
	ssScore << setw(6) << setfill('0') << _scoreNumber;
	_textScore->setString("SCORE-" + ssScore.str());
	_textScore->draw(spriteHandle);

	stringstream ssLife;
	ssLife << setw(2) << setfill('0') << _lifeNumber;
	_textLife->setString("P-" + ssLife.str());
	_textLife->draw(spriteHandle);

	_textPlayer->draw(spriteHandle);
	_textEnemy->draw(spriteHandle);
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
	return _timeNumber;
}


void Info::SetEnemyHitPoint(int number)
{
	_enemyHitPointNumber = number;
}

void Info::SetHeart(int number)
{
	_heartNumber = number;
}

void Info::SetLife(int number)
{
	_lifeNumber = number;
}

void Info::SetPlayerHitPoint(int number)
{
	_playerHitPointNumber = number;
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
	_timeNumber = number;
}
