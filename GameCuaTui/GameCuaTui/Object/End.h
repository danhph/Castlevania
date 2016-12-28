#ifndef __END_H__
#define __END_H__

#include "..\FrameWork\define.h"
#include "BaseObject.h"
#include "..\Framework\IComponent.h"
#include "CollisionBody.h"

class End : public BaseObject
{
public:
	End(int x, int y, int width, int height);
	~End();

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	RECT getBounding() override;

	eID getNextStage();
	void setNextStage(eID id);
private:
	map<string, IComponent*> _listComponent;

	RECT _bound;

	eID _nextStage;
};


#endif // !__END_H__
