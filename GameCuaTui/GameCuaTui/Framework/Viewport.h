#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "define.h"


//	Viewport là class dùng để chuyển hệ toạ độ top-left về hệ toạ độ đê-cac

class Viewport
{
public:
	Viewport();
	Viewport(float x, float y);
	Viewport(float x, float y, float width, float height);
	~Viewport();

	void setPositionWorld(GVector2 position);
	GVector2 getPositionWorld();

	float getWidth();
	float getHeight();

	GVector3 getPositionInViewport(GVector3* position);

	bool isContains(const RECT& rect);

	// Lấy kích thước của viewport bằng HCN, tinhs trong world lớn

	RECT getBounding();

private:
	GVector2 _positionWorld;
	float _width;
	float _height;
};

#endif // !__VIEWPORT_H__
