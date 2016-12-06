#include <algorithm>
#include "../Framework/SoundManager.h"
#include "../Scene/IntroScene.h"
#include "PlayScene.h"
#include "../Object/Player.h"
#include "../Tiles/utils.h"

#if _DEBUG
#include <time.h>
#endif


PlayScene::PlayScene()
{
	_viewport = new Viewport(0, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
}

PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}

void PlayScene::setViewport(Viewport* viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

bool PlayScene::init()
{
	auto player = new Player();
	player->init();
	player->setPosition(64 + 16, 64);
	player->getBounding();
	this->_player = player;
	_activeObject.push_back(_player);

	_text = new Text(L"Arial", "", 10, 25);

	_tileMap = TileMap::LoadFromFile("Resources//Map//stage21.tmx", eID::MAP_STAGE_21);

	auto quadTreeWidth = (_tileMap->worldWidth() >= _tileMap->worldHeight()) ? _tileMap->worldWidth() : _tileMap->worldHeight();
	RECT rectMap;
	rectMap.left = 0;
	rectMap.bottom = 0;
	rectMap.top = quadTreeWidth;
	rectMap.right = quadTreeWidth;


	_root = new QuadTreeNode(rectMap);

	auto listObject = GetListObjectFromFile("Resources//Map//stage21.tmx");
	for (auto obj : (*listObject))
	{
		_root->Insert(obj);
	}
	listObject->clear();

	return true;
}

void PlayScene::updateInput(float dt)
{
	this->getPlayer()->updateInput(dt);
}

void PlayScene::update(float dt)
{
	char str[100];
	sprintf(str, "delta time: %f", dt);
	_text->setText(str);

	if (this->checkEndGame() == true)
		return;

	GVector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();

	RECT screen;
	screen.left = viewport_in_transform.left;
	screen.right = viewport_in_transform.right;
	screen.top = this->_tileMap->getWorldSize().y - viewport_position.y;
	screen.bottom = screen.top + _viewport->getHeight();

	_root->DeleteObjects();

	_activeObject.clear();
	_activeObject = _root->Retrieve(screen);
	_activeObject.push_back(_player);

	for (auto obj : _activeObject)
	{
		if (obj == nullptr || obj->isInStatus(eStatus::DESTROY) || obj->getId() == eID::WALL)
			continue;
		for (BaseObject* passiveObj : _activeObject)
		{
			if (passiveObj == nullptr || passiveObj == obj || passiveObj->isInStatus(eStatus::DESTROY))
				continue;
			obj->checkCollision(passiveObj, dt);
		}
	}

	for (BaseObject* obj : _activeObject)
	{
		obj->update(dt);
	}
}

void PlayScene::updateViewport(BaseObject* objTracker)
{
	GVector2 current_position = _viewport->getPositionWorld();
	GVector2 worldsize = this->_tileMap->getWorldSize();

	GVector2 new_position = GVector2(max(objTracker->getPositionX() - 260, 0), WINDOW_HEIGHT);

	if (new_position.x < current_position.x)
	{
		new_position.x = current_position.x;
	}

	if (new_position.x + WINDOW_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOW_WIDTH;
	}

	_viewport->setPositionWorld(new_position);
}

void PlayScene::draw(LPD3DXSPRITE spriteHandle)
{
	_tileMap->draw(spriteHandle, _viewport);

	for (BaseObject* object : _activeObject)
	{
		object->draw(spriteHandle, _viewport);
	}

#if _DEBUG
	_text->draw();
#endif
}

void PlayScene::release()
{
	_root->Release();
	SAFE_DELETE(_root);
	_tileMap->release();
	SAFE_DELETE(_tileMap);
}

bool PlayScene::checkEndGame()
{
	if (((Player*)_player)->getLifeNumber() < 0)
	{
		auto gameoverScene = new IntroScene();
		SceneManager::getInstance()->replaceScene(gameoverScene);
		return true;
	}
	return false;
}

BaseObject* PlayScene::getObject(eID id)
{
	if (id == eID::PLAYER)
		return getPlayer();

	eID objectID;
	if (_activeObject.size() == 0)
	{
		return nullptr;
	}
	for (BaseObject* object : _activeObject)
	{
		objectID = object->getId();
		if (objectID == id)
			return object;
	}
	return nullptr;
}

Player* PlayScene::getPlayer()
{
	return (Player*) this->_player;
}
