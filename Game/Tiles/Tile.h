﻿#ifndef __TILE__
#define __TILE__

#include <string>
#include "../Framework/Sprite.h"

USE_GAMEUIT_FRAMEWORK

// Class helper for class Map.
class Tile 
{
private:
	int _id;
	RECT _srcRect;

	Sprite* _refSprite; // ảnh gồm nhiều tile. khi vẽ cắt bằng srcRect như Sprite

public:

	const int &getId() const;

	Tile(Sprite *refSprite, RECT srcRect, int id);
	void draw(LPD3DXSPRITE spriteHandle, GVector2 position,  Viewport *viewport = NULL);

};




#endif	//#ifndef __TILE__
