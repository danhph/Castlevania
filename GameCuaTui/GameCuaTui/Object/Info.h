#ifndef __LIFEUI_H__
#define __LIFEUI_H__

#include "EmptyObject.h"
#include "../FrameWork/define.h"
#include "TextSprite.h"
#include "../Framework/StopWatch.h"

#define GAP 10

class Info : public BaseObject
{
public:
	Info();
	~Info();

	virtual void init();
	virtual void update(float deltatime);
	virtual void draw(LPD3DXSPRITE, Viewport*);
	virtual void release();

	void SetPlayerHitPoint(int number);
	int GetPlayerHitPoint();
	
	void SetEnemyHitPoint(int number);
	int GetEnemyHitPoint();

	void SetHeart(int number);
	int GetHeart();

	void SetLife(int number);
	int GetLife();

	void SetStage(int number);
	int GetStage();

	void AddScore(int number);
	void SetScore(int number);
	int GetScore();

	void SetTime(int number);
	void PauseTime();
	void ActiveTime();
	int GetTime();

	void SetWeapon(eID id);
	eID GetCurrentWeapon();

	void SetMaxWeapon(int num);
	int GetMaxWeapon();
private:
	eID _weaponID;
	Sprite* _weaponSprite;
	Sprite* _iconEmptyHitPoint;
	Sprite* _border;

	Sprite* _iconPlayerHitPoint;
	TextSprite* _textPlayer;
	int _playerHitPointNumber;
	
	Sprite* _iconEnemyHitPoint;
	TextSprite* _textEnemy;
	int _enemyHitPointNumber;

	Sprite* _iconHeart;
	TextSprite* _textHeart;
	int _heartNumber;
	
	TextSprite* _textLife;
	int _lifeNumber;

	TextSprite* _textScore;
	int _scoreNumber;

	TextSprite* _textStage;
	int _stageNumber;

	TextSprite* _textTime;
	int _timeNumber;
	
	float _beginTime;
	bool _pauseTime;
	int time;
	int _maxWeapon;
	Sprite* _maxWeaponSprite;
};

#endif // !__LIFEUI_H__
