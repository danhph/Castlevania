#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include <stdarg.h>
#include "define.h"
#include "Sprite.h"
#include "IComponent.h"
#include "SpriteManager.h"

class Animation : public IComponent
{
public:
	~Animation();
	Animation(Sprite* spriteSheet, float timeAnimate = 0.0f, bool loop = true);

	Animation(Sprite* spriteSheet, int totalFrames, int cols, float timeAnimate = 0.0f);

	void nextFrame();

	void setIndex(int index);

	int getIndex();

	void update(float dt);

	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);

	void setTimeAnimate(float time);

	float getTimeAnimate();

	void start();

	void stop();

	void canAnimate(bool can);
	bool isAnimate();
	void addFrameRect(RECT rect);
	void addFrameRect(float left, float top, int width, int height);
	void addFrameRect(float left, float top, float right, float bottom);

	void addFrameRect(eID id, char* firstRectName, ...);

	void setPosition(GVector2 p)
	{
	}

	void setLoop(bool isLoop);
	bool isLoop();

	void restart(int from = 0);

	void enableFlashes(bool enable);

	void setValueFlashes(float value);

	void animateFromTo(int from, int to, bool loop = true);

	void setColorFlash(D3DXCOLOR color);
	D3DXCOLOR getColorFlash();
	bool isLastAnimation();
private:
	bool _isAll;
	int _startFrame;
	int _endFrame;
	int _index;
	int _totalFrames;

	float _timeAnimate;
	float _timer;

	bool _canAnimate;
	bool _isLoop;

	Sprite* _spriteSheet;
	vector<RECT> _frameRectList;
	string _nameAnimation;
	RECT _currentRect;

	bool _canFlashes;
	float _valueFlashes;
	D3DXCOLOR _flashColor;
};

#endif // !__ANIMATION_H__
