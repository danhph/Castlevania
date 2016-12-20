#include "PlayScene.h"



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

void PlayScene::initStage()
{
	this->getPlayer()->setStage(_currentStage);
	this->getPlayer()->resetValues();

	_tileMap = StageManager::getInstance()->getTileMap(_currentStage);
	
	auto quadTreeWidth = (_tileMap->worldWidth() >= _tileMap->worldHeight()) ? _tileMap->worldWidth() : _tileMap->worldHeight();
	RECT rectMap;
	rectMap.left = 0;
	rectMap.bottom = 0;
	rectMap.top = quadTreeWidth;
	rectMap.right = quadTreeWidth;

	_root = new QuadTreeNode(rectMap);

	auto listObject = StageManager::getInstance()->getListObject(_currentStage);

	for (auto obj : (*listObject))
	{
		if (obj->getId() == START)
		{
			_player->setPosition(obj->getPosition());
			this->getPlayer()->setStatus(obj->getStatus());
		}
		else
			_root->Insert(obj);
	}
	listObject->clear();
}

bool PlayScene::init()
{
	auto player = new Player();
	player->init();
	player->setPosition(64 + 16, 64);
	player->getBounding();
	this->_player = player;
	_activeObject.push_back(_player);

	_currentStage = MAP_STAGE_21;

	initStage();

	return true;
}

void PlayScene::updateInput(float dt)
{
	this->getPlayer()->updateInput(dt);
}

void PlayScene::update(float dt)
{
	if (this->getPlayer()->getStage() != _currentStage)
	{
		_currentStage = this->getPlayer()->getStage();
		initStage();
	}

	if (this->checkEndGame() == true)
	{
		return;
	}

	if (_player->isInStatus(eStatus::DIE) == false)
	{
		this->updateViewport(_player);
	}

	RECT viewport_in_transform = _viewport->getBounding();

	_root->DeleteObjects();

	_activeObject.clear();
	_activeObject = _root->Retrieve(viewport_in_transform);
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