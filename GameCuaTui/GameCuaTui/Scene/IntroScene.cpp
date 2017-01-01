#include "IntroScene.h"
#include "../Framework/SoundManager.h"

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
	_introtable->setPosition(256,240);

	_playOption = new TextSprite(eID::FONTFULL, "PUSH START KEY", GVector2(160, 300));
	_playOption->init();
	_playOption->setScale(2.0);

	_huuDanh = new TextSprite(eID::FONTFULL, "HUU DANH   - 14520134", GVector2(20, 350));
	_huuDanh->init();
	_huuDanh->setScale(2.0);

	_thanhLiem = new TextSprite(eID::FONTFULL, "THANH LIEM - 14520462", GVector2(20, 375));
	_thanhLiem->init();
	_thanhLiem->setScale(2.0);

	_lanAnh = new TextSprite(eID::FONTFULL, "LAN ANH    - 14520021", GVector2(20, 400));
	_lanAnh->init();
	_lanAnh->setScale(2.0);

	_flash = new StopWatch();
	_access = new StopWatch();
	
	_ok = false;
	_draw = true;

	SoundManager::getInstance()->PlayLoop(INTRO_SCENE);

	return true;
}

void IntroScene::onKeyPressed(KeyEventArg* key_event)
{
}

void IntroScene::update(float dt)
{
	if (_ok)
	{
		if (_flash->isTimeLoop(120))
		{
			_draw = !_draw;
		}
		if (_access->isTimeLoop(800))
		{
			SceneManager::getInstance()->replaceScene(new PlayScene());
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
	_huuDanh->draw(spriteHandle);
	_thanhLiem->draw(spriteHandle);
	_lanAnh->draw(spriteHandle);
}

void IntroScene::release()
{
	SoundManager::getInstance()->Stop(INTRO_SCENE);
	SAFE_DELETE(_playOption);
	SAFE_DELETE(_introtable);
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
