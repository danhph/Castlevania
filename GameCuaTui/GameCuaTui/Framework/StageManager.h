#ifndef __STAGEMANAGER_H__
#define __STAGEMANAGER_H__

#include <map>

#include <fstream>

#include "define.h"
#include "Sprite.h"
#include "../Tiles/TileMap.h"
#include "../Object/BaseObject.h"
#include "../Tiles/myutils.h"

class StageManager
{
public:
	static StageManager* getInstance();

	static void release();

	void loadResource();
	
	TileMap* getTileMap(eID id);

	list<BaseObject*>* getListObject(eID id);

	~StageManager(void);

private:
	StageManager(void);
	
	static StageManager* _instance;

	map<eID, string> _resourcePath;
};


#endif // !__SPRITEMANAGER_H__
