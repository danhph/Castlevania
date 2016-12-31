#ifndef _BIRD_RANGE_H_
#define _BIRD_RANGE_H_

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"
#include "../Framework/StopWatch.h"
#include "Bird.h"
#include "../Framework/SceneManager.h"

class BirdRange : public BaseObject
{
public:
	BirdRange(int x, int y, int width, int height);
	~BirdRange();

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

	StopWatch* _initBirdStopWatch;

	float _initY;
};


#endif // !_BIRD_RANGE_H_
