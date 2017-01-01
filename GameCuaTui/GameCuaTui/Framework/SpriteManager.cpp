#include "SpriteManager.h"
#include "../pugixml/pugixml.hpp"
SpriteManager* SpriteManager::_instance = nullptr;

SpriteManager::SpriteManager(void)
{
	// do nothing.
}

SpriteManager::~SpriteManager(void)
{
	for (auto spr = _listSprite.begin(); spr != _listSprite.end(); ++spr)
	{
		spr->second->release(); // release image
		delete spr->second; // delete sprite
	}
	if (_listSprite.empty() == false)
		_listSprite.clear(); // remove all from MAP
}

void SpriteManager::loadResource(LPD3DXSPRITE spriteHandle)
{
	Sprite* pSprite = NULL;

	pSprite = new Sprite(spriteHandle, L"Resources//Images//mainmenu.png");
	this->_listSprite[eID::MAIN_MENU] = pSprite;

	pSprite = new Sprite(spriteHandle, L"Resources//Images//life.png");
	this->_listSprite[eID::HEART_ICON] = pSprite;

	pSprite = new Sprite(spriteHandle, L"Resources//Images//border.png");
	this->_listSprite[eID::BORDER] = pSprite;

	pSprite = new Sprite(spriteHandle, L"Resources//Images//wall_cube.png");
	this->_listSprite[eID::WALL] = pSprite;

	pSprite = new Sprite(spriteHandle, L"Resources//Fonts//fontFull.png", 54, 6);
	this->_listSprite[eID::FONTFULL] = pSprite;

	pSprite = new Sprite(spriteHandle, L"Resources//Images//simon.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::PLAYER, pSprite));
	this->loadSpriteInfo(eID::PLAYER, "Resources//Images//simon.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//candle.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::CANDLE, pSprite));
	this->loadSpriteInfo(eID::CANDLE, "Resources//Images//candle.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//enemy.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ENEMY, pSprite));
	this->loadSpriteInfo(eID::ENEMY, "Resources//Images//enemy.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//rope_new.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ROPE, pSprite));
	this->loadSpriteInfo(eID::ROPE, "Resources//Images//rope_new.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//items.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ITEM, pSprite));
	this->loadSpriteInfo(eID::ITEM, "Resources//Images//items.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//effects.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::EFFECT, pSprite));
	this->loadSpriteInfo(eID::EFFECT, "Resources//Images//effects.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//objects.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::OBJECTS, pSprite));
	this->loadSpriteInfo(eID::OBJECTS, "Resources//Images//objects.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//weapon.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::WEAPON, pSprite));
	this->loadSpriteInfo(eID::WEAPON, "Resources//Images//weapon.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//boss.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BOSS, pSprite));
	this->loadSpriteInfo(eID::BOSS, "Resources//Images//boss.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//breakwall.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BREAKWALL, pSprite));
	this->loadSpriteInfo(eID::BREAKWALL, "Resources//Images//breakwall.txt");

	pSprite = new Sprite(spriteHandle, L"Resources//Images//heal.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::HEAL, pSprite));
	this->loadSpriteInfo(eID::HEAL, "Resources//Images//heal.txt");

	pSprite = loadXMLDoc(spriteHandle, L"Resources//Map//stage21.tmx");
	pSprite->setOrigin(VECTOR2ZERO);
	pSprite->setScale(2.0f);
	this->_listSprite[eID::MAP_STAGE_21] = pSprite;

	pSprite = loadXMLDoc(spriteHandle, L"Resources//Map//stage22.tmx");
	pSprite->setOrigin(VECTOR2ZERO);
	pSprite->setScale(2.0f);
	this->_listSprite[eID::MAP_STAGE_22] = pSprite;

	pSprite = loadXMLDoc(spriteHandle, L"Resources//Map//stage23.tmx");
	pSprite->setOrigin(VECTOR2ZERO);
	pSprite->setScale(2.0f);
	this->_listSprite[eID::MAP_STAGE_23] = pSprite;

	pSprite = loadXMLDoc(spriteHandle, L"Resources//Map//stage24.tmx");
	pSprite->setOrigin(VECTOR2ZERO);
	pSprite->setScale(2.0f);
	this->_listSprite[eID::MAP_STAGE_24] = pSprite;

	pSprite = loadXMLDoc(spriteHandle, L"Resources//Map//stage31.tmx");
	pSprite->setOrigin(VECTOR2ZERO);
	pSprite->setScale(2.0f);
	this->_listSprite[eID::MAP_STAGE_31] = pSprite;

	pSprite = loadXMLDoc(spriteHandle, L"Resources//Map//stage32.tmx");
	pSprite->setOrigin(VECTOR2ZERO);
	pSprite->setScale(2.0f);
	this->_listSprite[eID::MAP_STAGE_32] = pSprite;

	pSprite = loadXMLDoc(spriteHandle, L"Resources//Map//stage33.tmx");
	pSprite->setOrigin(VECTOR2ZERO);
	pSprite->setScale(2.0f);
	this->_listSprite[eID::MAP_STAGE_33] = pSprite;

}

Sprite* SpriteManager::loadXMLDoc(LPD3DXSPRITE spritehandle, LPWSTR path)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path, pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		OutputDebugString(L"Khong tim thay file");
		return nullptr;
	}
	auto tileset_node = doc.child("map").child("tileset");
	int tilecount = tileset_node.attribute("tilecount").as_int();
	int columns = tileset_node.attribute("columns").as_int();
	auto image = tileset_node.child("image");

	string filename = image.attribute("source").as_string();
	wstring L_filename = wstring(filename.begin(), filename.end());
	wstring strpath = wstring(path);
	int index = strpath.find_last_of(L'//');
	strpath = strpath.substr(0, index);
	strpath += L"/" + L_filename;

	return new Sprite(spritehandle, (LPWSTR) strpath.c_str(), tilecount, columns);
}

Sprite* SpriteManager::getSprite(eID id)
{
	Sprite* it = this->_listSprite.find(id)->second;
	return new Sprite(*it); // get the copy version of Sprite
}

RECT SpriteManager::getSourceRect(eID id, string name)
{
	//return _sourceRectList[id].at(name);
	return _sourceRectList[id][name];
}

void SpriteManager::loadSpriteInfo(eID id, const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom);

			_sourceRectList[id][string(name)] = rect;
		}
	}

	fclose(file);
}

void SpriteManager::releaseSprite(eID id)
{
	Sprite* it = this->_listSprite.find(id)->second;
	delete it; // delete the sprite only, dont relase image
	this->_listSprite.erase(id); // erase funciotn only remove the pointer from MAP, dont delete it.
}

void SpriteManager::releaseTexture(eID id)
{
	Sprite* spr = this->_listSprite.find(id)->second;
	spr->release(); // release image
	delete spr;
	this->_listSprite.erase(id); // erase funciotn only remove the pointer from MAP, dont delete it.
}

SpriteManager* SpriteManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteManager();
	return _instance;
}

void SpriteManager::release()
{
	delete _instance; // _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}
