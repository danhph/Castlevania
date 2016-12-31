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
	_tileMap = StageManager::getInstance()->getTileMap(_currentStage);

	auto quadTreeWidth = (_tileMap->worldWidth() >= _tileMap->worldHeight()) ? _tileMap->worldWidth() : _tileMap->worldHeight();
	RECT rectMap;
	rectMap.left = 0;
	rectMap.bottom = 0;
	rectMap.top = quadTreeWidth;
	rectMap.right = quadTreeWidth;

	_root = new QuadTreeNode(rectMap);
	QuadTreeNode::setInstance(_root);

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

	this->getPlayer()->setStage(_currentStage);
	this->getPlayer()->resetValues();
}

bool PlayScene::init()
{
	auto player = new Player();
	player->init();
	player->setPosition(64 + 16, 64);
	player->getBounding();
	this->_player = player;

	_currentStage = MAP_STAGE_21;

	initStage();

	_crossStopWatch = new StopWatch();
	_isCrossing = false;

	return true;
}

void PlayScene::updateInput(float dt)
{
	this->getPlayer()->updateInput(dt);
}

void PlayScene::update(float dt)
{
	if (this->checkEndGame() == true)
	{
		return;
	}

	if (this->getPlayer()->isChangedStage())
	{
		_currentStage = this->getPlayer()->getStage();
		initStage();
	}

	if (_player->isInStatus(eStatus::DIE) == false)
	{
		this->updateViewport(this->getPlayer(), dt);
	}

	if (this->getPlayer()->IsPlayingMove())
	{
		_player->update(dt);
		for (BaseObject* object : _activeObject)
		{
			if (object->getId() == DOOR)
				object->update(dt);
		}
		return;
	}

	RECT viewport_in_transform = _viewport->getBounding();

	_root->DeleteObjects();

	_activeObject.clear();
	_activeObject = _root->Retrieve(viewport_in_transform);

	if (this->getPlayer()->GetCross())
	{
		this->getPlayer()->UseCross();
		_isCrossing = true;
		_crossStopWatch->restart();
		_crossStopWatch->isStopWatch(600);
		auto i = 0;
		while (i < _activeObject.size())
		{
			auto objId = (int)_activeObject[i]->getId();
			if (objId > 70 && objId < 79)
			{
				_activeObject[i]->setStatus(DESTROY);
				_activeObject.erase(_activeObject.begin() + i);
			}
			i++;
		}
	}

	for (auto obj : _activeObject)
		_player->checkCollision(obj, dt);

	auto i = 0;
	int j;
	while (i < _activeObject.size() - 1)
	{
		j = i + 1;
		while (j < _activeObject.size())
		{
			if (_activeObject[i]->getId() == WALL)
				_activeObject[j]->checkCollision(_activeObject[i], dt);
			else
				_activeObject[i]->checkCollision(_activeObject[j], dt);
			j++;
		}
		i++;
	}

	_player->update(dt);

	for (BaseObject* obj : _activeObject)
	{
		obj->update(dt);
	}
}

void PlayScene::updateViewport(Player* player, float dt)
{
	GVector2 current_position = _viewport->getPositionWorld();
	GVector2 worldsize = this->_tileMap->getWorldSize();

	auto playerX = player->getPositionX();
	auto isPlayingMovie = player->IsPlayingMove();
	auto checkPoint = _tileMap->getCheckpoint();

	GVector2 new_position = GVector2(max(playerX - 260, 0), WINDOW_HEIGHT);

	if (!isPlayingMovie)
	{
		if (playerX > checkPoint && new_position.x < checkPoint)
		{
			new_position.x = checkPoint;
		}
		if (playerX < checkPoint + 32 && new_position.x + WINDOW_WIDTH > checkPoint)
		{
			new_position.x = checkPoint - WINDOW_WIDTH;
		}
	}
	else if (_player->getVelocity().x == 0)
	{
		new_position = _viewport->getPositionWorld();

		if (new_position.x + WINDOW_WIDTH / 2 <= checkPoint)
			player->StartMovieMove();

		if (player->getMapDirection() == RIGHT)
		{
			new_position.x -= 125 * dt / 1000;
			if (new_position.x + WINDOW_WIDTH <= checkPoint)
			{
				new_position.x = checkPoint - WINDOW_WIDTH;
				player->StopMovie();
			}
		}
		else
		{
			new_position.x += 125 * dt / 1000;
			if (new_position.x >= checkPoint)
			{
				new_position.x = checkPoint;
				player->StopMovie();
			}
		}
	}
	if (new_position.x + WINDOW_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOW_WIDTH;
	}

	_viewport->setPositionWorld(new_position);
}

void PlayScene::draw(LPD3DXSPRITE spriteHandle)
{
	if (_isCrossing)
	{
		if (_crossingEffect)
		{
			for (BaseObject* object : _activeObject)
			{
				object->setColor(EFFECT_COLOR_1);
			}
			_tileMap->setColor(EFFECT_COLOR_1);
			_player->setColor(EFFECT_COLOR_1);
		}
		else
		{
			for (BaseObject* object : _activeObject)
			{
				object->setColor(EFFECT_COLOR_2);
			}
			_tileMap->setColor(EFFECT_COLOR_2);
			_player->setColor(EFFECT_COLOR_2);
		}
		
		_crossingEffect = !_crossingEffect;

		if (_crossStopWatch->isStopWatch(600))
		{
			_isCrossing = false;

			for (BaseObject* object : _activeObject)
			{
				object->setColor(COLOR_WHITE);
			}
			_tileMap->setColor(COLOR_WHITE);
			_player->setColor(COLOR_WHITE);
		}
	}

	_tileMap->draw(spriteHandle, _viewport);

	if (!this->getPlayer()->IsPlayingMove())
	{
		for (BaseObject* object : _activeObject)
		{
			object->draw(spriteHandle, _viewport);
		}
	}
	else
	{
		for (BaseObject* object : _activeObject)
		{
			if (object->getId() == DOOR)
				object->draw(spriteHandle, _viewport);
		}
	}
	_player->draw(spriteHandle, _viewport);
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
