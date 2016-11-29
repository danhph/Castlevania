#include "TileMap.h"

TileMap::TileMap()
{
	_mapIndex = NULL;
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

	int iBegin = max(screenRectEx.left / _frameWidth, 0);
	int iEnd = min(screenRectEx.right / _frameWidth + 1, _mapSize.x);
	int jBegin = _mapSize.y - min(screenRectEx.top / _frameHeight + 1, _mapSize.y);
	int jEnd = _mapSize.y - max(screenRectEx.bottom / _frameHeight , 0);

	GVector2 pos;

	for (int i = iBegin; i < iEnd; i++)
	{
		for (int j = jBegin; j < jEnd; j++)
		{
			pos.x = i * _frameWidth;
			pos.y = (_mapSize.y - j - 1) * _frameHeight;
			this->_tileSet->draw(spriteHandle, this->_mapIndex[j][i], pos, viewport);
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

TileMap* TileMap::LoadFromFile(const string path, eID spriteId)
{
	xml_document doc;

	xml_parse_result result = doc.load_file(path.data(), parse_default | parse_pi);
	if (result == false)
	{
		return nullptr;
	}
	TileMap* map = new TileMap();


	xml_node tilemap = doc.child("Tilesmap");
	if (tilemap == NULL)
		return nullptr;
	map->_mapSize.x = getAttributeValue(tilemap, "columns").as_int();
	map->_mapSize.y = getAttributeValue(tilemap, "rows").as_int();

	map->_mapIndex = new int*[int(map->_mapSize.y)];
	for (int i = 0; i < map->_mapSize.y; i++)
	{
		map->_mapIndex[i] = new int[(int)map->_mapSize.x];
	}

	xml_node matrixindex = tilemap.child("MatrixIndex");
	if (matrixindex == NULL)
		return nullptr;
	getElementMatrixIndex(matrixindex, map->_mapIndex);

	xml_node tileset = tilemap.child("TileSet");
	map->_tileSet = new TileSet(spriteId);
	map->_tileSet->loadListTiles(tileset);

	map->_frameWidth = map->_tileSet->getSprite()->getFrameWidth();
	map->_frameHeight = map->_tileSet->getSprite()->getFrameHeight();

	return map;
}

void TileMap::getElementMatrixIndex(xml_node& node, int** matrix)
{
	xml_node child = node.first_child();

	string indexStr;

	int i = 0, j = 0;

	while (child != nullptr)
	{
		char* temp = NULL;
		char* pch = NULL;

		indexStr = child.text().as_string();

		i = child.attribute("id").as_int();

		auto str = splitString(indexStr, '\t');
		int j = 0;

		for (string tmp : str)
		{
			matrix[i][j] = atoi(tmp.c_str());
			j++;
		}

		child = child.next_sibling();
		str.clear();
	}
}

xml_attribute TileMap::getAttributeValue(const xml_node& node, string attributename)
{
	return node.find_attribute(
		[&](xml_attribute att) -> bool
		{
			if (string(att.name()).compare(attributename) == 0)
				return true;
			return false;
		});
}
