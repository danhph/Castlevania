#pragma once
#ifndef _FROG_RANGE_H_
#define _FROG_RANGE_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../Framework/StopWatch.h"
#include "Frog.h"
#include "../Framework/SceneManager.h"

class FrogRange : public BaseObject
{
public:
	FrogRange(int x, int y, int width, int height);
	~FrogRange();

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	RECT getBounding() override;

	void SetDirect(bool direct);

	bool GetDirect();
	void Active();
	void Deactive();

	void SetInitY(float y);
private:
	map<string, IComponent*> _listComponent;

	bool _active;
	RECT _bound;
	bool _direct;

	bool _initFrog;
	StopWatch* _initFrogStopWatch;

	float _initY;
};


#endif // !_FROG_RANGE_H_
