#ifndef __MAP_H__
#define __MAP_H__
#include "TileSet.h"

#include "..\FrameWork\define.h"
#include "..\FrameWork\Sprite.h"
#include "..\FrameWork\SpriteManager.h"
#include "..\pugixml\pugixml.hpp"

using namespace std;
using namespace pugi;

class TileMap
{
public:

	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	static TileMap* LoadFromFile(const string path, eID spriteId);

	GVector2 getWorldSize();
	
	TileMap();
	~TileMap();
	int worldWidth();
	int worldHeight();
	int getCheckpoint();

	void setCheckpoint(int checkPoint);

	void setColor(D3DXCOLOR color);

private:

	int _frameWidth;
	int _frameHeight;

	int _checkPoint;

	// Kích thước map tính theo số ô Tile.
	GVector2 _mapSize;

	int** _mapIndex;

	TileSet* _tileSet;

	void getElementMatrixIndex(xml_node& node);
};

#endif // !__MAP_H__
