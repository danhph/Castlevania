#include "OverScene.h"
#include "../Framework/SoundManager.h"

void OverScene::updateInput(float deltatime)
{
	if (_input->isKeyPressed(DIK_UP) || _input->isKeyPressed(DIK_DOWN))
	{
		_choice = !_choice;
	}
	if (_input->isKeyPressed(DIK_RETURN))
	{
		_ok = true;
	}
}

bool OverScene::init()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::HEART_ICON);
	_sprite->setPosition(130, 250);

	_gameover = new TextSprite(eID::FONTFULL, "GAME OVER", GVector2(160, 200));
	_gameover->init();
	_gameover->setScale(2.0);

	_continue = new TextSprite(eID::FONTFULL, "Play again", GVector2(160, 250));
	_continue->init();
	_continue->setScale(2.0);

	_quit = new TextSprite(eID::FONTFULL, "Quit", GVector2(160, 300));
	_quit->init();
	_quit->setScale(2.0);

	_flash = new StopWatch();
	_access = new StopWatch();

	_ok = false;
	_choice = true;
	_draw = true;

	return true;
}

void OverScene::update(float dt)
{
	if (_choice)
		_sprite->setPosition(130, 250);
	else
		_sprite->setPosition(130, 300);

	if (_ok)
	{
		if (_flash->isTimeLoop(120))
		{
			_draw = !_draw;
		}
		if (_access->isTimeLoop(800))
		{
			if (_choice)
				SceneManager::getInstance()->replaceScene(new PlayScene());
			else
				SceneManager::getInstance()->replaceScene(new IntroScene());
		}
	}
}

void OverScene::draw(LPD3DXSPRITE spriteHandle)
{
	_info->draw(spriteHandle, nullptr);
	_gameover->draw(spriteHandle);
	_continue->draw(spriteHandle);
	_quit->draw(spriteHandle);

	if (_draw)
		_sprite->render(spriteHandle);
}

void OverScene::release()
{
	SAFE_DELETE(_flash);
	SAFE_DELETE(_access);
	SAFE_DELETE(_info);
	if (_input != nullptr)
		__unhook(_input);
}

OverScene::OverScene(Info* info)
{
	_info = info;
}

OverScene::~OverScene()
{
}
