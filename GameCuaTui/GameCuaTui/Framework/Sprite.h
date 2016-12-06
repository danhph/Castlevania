#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <list>
#include "define.h"
#include "DeviceManager.h"
#include "Texture.h"
#include "Viewport.h"
#include "Transformable.h"

using namespace std;

class Sprite : public Transformable
{
public:
	Sprite(LPD3DXSPRITE spriteHandle, LPWSTR filePath, int totalFrames = 1, int cols = 1);

	~Sprite();

	void release();


	void render(LPD3DXSPRITE spriteHandle);

	void render(LPD3DXSPRITE spriteHandle, Viewport* viewport);

	void setPosition(float x, float y, float z = 1);
	void setPosition(GVector3 vector);
	void setPosition(GVector2 position);
	void setPositionX(float x);
	void setPositionY(float y);

	void setScale(GVector2 scale);
	void setScale(float scale);
	void setScaleX(float sx);
	void setScaleY(float sy);

	void setRotate(float degree);

	void setOrigin(GVector2 origin);

	void setZIndex(float z);

	RECT getBounding();

	void setFrameRect(RECT rect);
	void setFrameRect(float top, float right, float bottom, float left);
	void setFrameRect(float x, float y, int width, int height);
	RECT getFrameRect();
	RECT getFrameRectByIndex(int index);

	void nextFrame();

	void setIndex(int index);

	int getFrameWidth();

	int getFrameHeight();

	int getTextureWidth();

	int getTextureHeight();

	void drawBounding(bool draw);

	void setOpacity(float opacity);
	float getOpacity();

	void setColor(D3DXCOLOR color);
	D3DXCOLOR getColor();

private:
	Texture _texture;
	float _opacity;
	D3DXCOLOR _color;

	RECT _bound;

	int _totalFrames;
	int _columns;
	int _index;
	GVector2 _currentFrame;

	RECT _frameRect;
	int _frameWidth;
	int _frameHeight;
	int _textureWidth;
	int _textureHeight;

	void setFrameRect();
	void setCurrentFrame();
	void updateBounding();

	GVector2 rotatePointAroundOrigin(GVector2 point, float angle, GVector2 origin);

	LPDIRECT3DSURFACE9 _surface;
	bool _isDrawBounding;
};


#endif // !__SPRITE_H__
