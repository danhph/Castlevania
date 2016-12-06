#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include <map> // map contain a pair data with key and value
// http://www.cplusplus.com/reference/map/map
#include <fstream>

#include "define.h"
#include "Sprite.h"

class SpriteManager
{
public:
	static SpriteManager* getInstance();
	static void release();

	void loadResource(LPD3DXSPRITE spritehandle);
	Sprite* getSprite(eID id);

	RECT getSourceRect(eID id, string name);
	void loadSpriteInfo(eID id, const char* fileInfoPath);

	void releaseSprite(eID id);

	void releaseTexture(eID id);

	~SpriteManager(void);
private:
	SpriteManager(void);
	static SpriteManager* _instance;
	map<eID, Sprite*> _listSprite;
	map<eID, map<string, RECT>> _sourceRectList;

	Sprite* loadXMLDoc(LPD3DXSPRITE spritehandle, LPWSTR path);
};


#endif // !__SPRITEMANAGER_H__
