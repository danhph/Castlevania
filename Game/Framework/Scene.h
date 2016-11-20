#ifndef __SCENE_H__
#define __SCENE_H__

#include "define.h"
#include "Viewport.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	bool virtual init() = 0;
	void virtual updateInput(float dt) = 0;
	void virtual update(float dt) = 0;
	void virtual draw(LPD3DXSPRITE spriteHandle) = 0;
	void virtual release() = 0;

	Viewport*  getViewport();
protected:
	Viewport* _viewport;
private:

};

#endif // !__SCENE_H__

