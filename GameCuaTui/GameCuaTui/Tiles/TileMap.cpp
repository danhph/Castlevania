#include "TileMap.h"

TileMap::TileMap()
{
	_mapIndex = NULL;
	_checkPoint = -1;
}

TileMap::~TileMap()
{
}

void TileMap::release()
{
}


void TileMap::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	RECT screenRectEx =
	{
		viewport->getPositionWorld().x,
		viewport->getPositionWorld().y,
		viewport->getPositionWorld().x + viewport->getWidth(),
		viewport->getPositionWorld().y - viewport->getHeight()
	};

	int colBegin = max(screenRectEx.left / _frameWidth, 0);
	int colEnd = min(screenRectEx.right / _frameWidth + 1, _mapSize.x);
	int rowBegin = _mapSize.y - min(screenRectEx.top / _frameHeight + 1, _mapSize.y);
	int rowEnd = _mapSize.y - max(screenRectEx.bottom / _frameHeight , 0);

	GVector2 pos;

	for (int col = colBegin; col < colEnd; col++)
	{
		for (int row = rowBegin; row < rowEnd; row++)
		{
			pos.x = col * _frameWidth;
			pos.y = (_mapSize.y - row - 1) * _frameHeight;
			this->_tileSet->draw(spriteHandle, this->_mapIndex[row][col], pos, viewport);
		}
	}
}

GVector2 TileMap::getWorldSize()
{
	GVector2 result;
	result.x = this->_mapSize.x * this->_frameWidth;
	result.y = this->_mapSize.y * this->_frameHeight;
	return result;
}

void TileMap::setCheckpoint(int checkPoint)
{
	_checkPoint = checkPoint;
}

void TileMap::setColor(D3DXCOLOR color)
{
	_tileSet->setColor(color);
}


TileMap* TileMap::LoadFromFile(const string path, eID spriteId)
{
	xml_document doc;

	xml_parse_result result = doc.load_file(path.data(), parse_default | parse_pi);
	if (result == false)
	{
		return nullptr;
	}
	TileMap* tileMap = new TileMap();

	xml_node map = doc.child("map");
	if (map == NULL)
		return nullptr;

	xml_node properties = map.child("properties");
	if (properties != NULL)
	{
		tileMap->setCheckpoint(properties.child("property").attribute("value").as_int()*2);
	}
	

	xml_node tileset = map.child("tileset");
	tileMap->_tileSet = new TileSet(spriteId);
	tileMap->_tileSet->loadListTiles(tileset);


	xml_node layer = map.child("layer");
	tileMap->_mapSize.x = layer.attribute("width").as_int();
	tileMap->_mapSize.y = layer.attribute("height").as_int();

	tileMap->_mapIndex = new int*[int(tileMap->_mapSize.y)];
	for (int i = 0; i < tileMap->_mapSize.y; i++)
	{
		tileMap->_mapIndex[i] = new int[(int)tileMap->_mapSize.x];
	}

	tileMap->getElementMatrixIndex(layer);

	tileMap->_frameWidth = tileMap->_tileSet->getSprite()->getFrameWidth();
	tileMap->_frameHeight = tileMap->_tileSet->getSprite()->getFrameHeight();

	return tileMap;
}

void TileMap::getElementMatrixIndex(xml_node& node)
{
	auto elements = node.child("data").children();
	auto row = 0, col = 0;

	for (auto element : elements)
	{
		this->_mapIndex[row][col] = element.attribute("gid").as_int();
		col++;
		if (col >= this->_mapSize.x)
		{
			col = 0;
			row++;
		}
	}
}

int TileMap::worldHeight()
{
	return _frameWidth * _mapSize.x;
}

int TileMap::worldWidth()
{
	return _frameHeight * _mapSize.y;
}

int TileMap::getCheckpoint()
{
	return _checkPoint;
}
