#include "StageManager.h"

StageManager* StageManager::_instance = nullptr;
TileMap* StageManager::_tileMap = nullptr;

StageManager::StageManager(void)
{
}

StageManager::~StageManager(void)
{
}

StageManager* StageManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new StageManager();
	return _instance;
}

list<BaseObject*>* StageManager::getListObject(eID id)
{
	return GetListObjectFromFile(_resourcePath[id]);
}

TileMap* StageManager::getTileMap(eID id)
{
	_tileMap = TileMap::LoadFromFile(_resourcePath[id], id);
	return _tileMap;
}

void StageManager::loadResource()
{
	_resourcePath[eID::MAP_STAGE_21] = "Resources//Map//stage21.tmx";
	_resourcePath[eID::MAP_STAGE_22] = "Resources//Map//stage22.tmx";
	_resourcePath[eID::MAP_STAGE_23] = "Resources//Map//stage23.tmx";
	_resourcePath[eID::MAP_STAGE_24] = "Resources//Map//stage24.tmx";
	_resourcePath[eID::MAP_STAGE_31] = "Resources//Map//stage31.tmx";
	_resourcePath[eID::MAP_STAGE_32] = "Resources//Map//stage32.tmx";
	_resourcePath[eID::MAP_STAGE_33] = "Resources//Map//stage33.tmx";
}

void StageManager::release()
{
	
}

TileMap* StageManager::getCurrentTileMap()
{
	return  _tileMap;
}
