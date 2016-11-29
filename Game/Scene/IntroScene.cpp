#include "IntroScene.h"
#include "../Framework/Managers/SoundManager.h"
#include "../Stage21.h"

void IntroScene::updateInput(float deltatime)
{
	if (_input->isKeyDown(DIK_SPACE))
	{
		_ok = true;
	}
}

bool IntroScene::init()
{
	_introtable = SpriteManager::getInstance()->getSprite(eID::MAIN_MENU);
	_introtable->setPosition(GVector2(514.0f, 0));
	_introtable->setScale(SCALE_FACTOR);
	_introtable->setOrigin(GVector2(0.0f, 1.0f));

	_playOption = new TextSprite(eID::FONTFULL, "PUSH START KEY", GVector2(0, 280));
	_playOption->init();
	_playOption->setScale(2.0);
	_playOption->setOrigin(VECTOR2ZERO);

	_movement = new Movement(VECTOR2ZERO, GVector2(-200.0f, 0.0f), _introtable);

	_flash = new StopWatch();
	_access = new StopWatch();
	
	_ok = false;
	_draw = true;
	return true;
}

void IntroScene::onKeyPressed(KeyEventArg* key_event)
{
}

void IntroScene::update(float dt)
{
	_movement->update(dt);
	
	_playOption->setPosition(GVector2(_introtable->getPositionX() + 170.0f, _playOption->getPosition().y));

	if (_introtable->getPositionX() <= 0)
	{
		_movement->setVelocity(VECTOR2ZERO);
		_introtable->setPosition(VECTOR2ZERO);
	}

	if (_ok)
	{
		if (_flash->isTimeLoop(120))
		{
			_draw = !_draw;
		}
		if (_access->isTimeLoop(800))
		{
			auto play = new Stage21();
			SceneManager::getInstance()->replaceScene(play);
		}
	}
}

void IntroScene::draw(LPD3DXSPRITE spriteHandle)
{
	_introtable->render(spriteHandle);
	if (!_ok)
	{
		_playOption->draw(spriteHandle);
	}
	else
	{
		if (_draw)
		{
			_playOption->draw(spriteHandle);
		}
	}
}

void IntroScene::release()
{
	SAFE_DELETE(_playOption);
	SAFE_DELETE(_introtable);
	SAFE_DELETE(_movement);
	SAFE_DELETE(_flash);
	SAFE_DELETE(_access);

	if (_input != nullptr)
		__unhook(_input);
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}
