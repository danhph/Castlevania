#ifndef __MAP_H__
#define __MAP_H__
#include "TileSet.h"

#include "..\FrameWork\define.h"
#include "..\FrameWork\Sprite.h"
#include "..\FrameWork\SpriteManager.h"
#include "..\pugixml\pugixml.hpp"

using namespace std;
using namespace pugi;
USE_GAMEUIT_FRAMEWORK

class Map
{
public:

	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	static Map* LoadFromFile(const string path, eID spriteId);

	GVector2 getWorldSize();
	
	Map();
	~Map();

private:

	int _frameWidth;
	int _frameHeight;

	// Kích thước map tính theo số ô Tile.
	GVector2 _mapSize;

	int** _mapIndex;

	TileSet* _tileSet;

	static xml_attribute getAttributeValue(const xml_node& node, string attributeName);

	static void getElementMatrixIndex(xml_node& node, int** matrix);
};

#endif // !__MAP_H__
