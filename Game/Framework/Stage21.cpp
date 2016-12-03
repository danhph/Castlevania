#include "../Stage21.h"
#include "Managers/SoundManager.h"
#include "../Scene/IntroScene.h"

#if _DEBUG
#include <time.h>
#endif


Stage21::Stage21()
{
	_viewport = new Viewport(0, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Stage21::~Stage21()
{
	delete _viewport;
	_viewport = nullptr;
}

void Stage21::setViewport(Viewport* viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

bool Stage21::init()
{
	auto player = new Player();
	player->init();
	player->setPosition(50, 50);

	this->_player = player;
	_listControlObject.push_back(player);
	_listObject.push_back(player);

	_text = new Text(L"Arial", "", 10, 25);

	//_root = QNode::loadQuadTree("Resources//Map//stage1_quadtree.xml");

	_tileMap = TileMap::LoadFromFile("Resources//Map//stage21.tmx", eID::MAP_STAGE_21);


	return true;
}

void Stage21::updateInput(float dt)
{
	for (IControlable* obj : _listControlObject)
	{
		obj->updateInput(dt);
	}
}

void Stage21::update(float dt)
{
	char str[100];
	sprintf(str, "delta time: %f", dt);
	_text->setText(str);

	if (this->checkGameLife() == true)
		return;

	GVector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();

	RECT screen;
	screen.left = viewport_in_transform.left;
	screen.right = viewport_in_transform.right;
	screen.top = this->_tileMap->getWorldSize().y - viewport_position.y;
	screen.bottom = screen.top + _viewport->getHeight();

}

void Stage21::destroyobject()
{
}

void Stage21::updateViewport(BaseObject* objTracker)
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

void Stage21::draw(LPD3DXSPRITE spriteHandle)
{
	_tileMap->draw(spriteHandle, _viewport);

	_player->draw(spriteHandle, _viewport);

	for (BaseObject* object : _activeObject)
	{
		object->draw(spriteHandle, _viewport);
	}

#if _DEBUG
	_text->draw();
#endif
}

void Stage21::release()
{
	for (auto object : _listObject)
	{
		object->release();
		SAFE_DELETE(object);
	}
	_tileMap->release();
	SAFE_DELETE(_tileMap);
}

bool Stage21::checkGameLife()
{
	if (((Player*)_player)->getLifeNumber() < 0)
	{
		auto gameoverScene = new IntroScene();
		SceneManager::getInstance()->replaceScene(gameoverScene);
		return true;
	}
	return false;
}

BaseObject* Stage21::getObject(eID id)
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

Player* Stage21::getPlayer()
{
	return (Player*) this->_player;
}
