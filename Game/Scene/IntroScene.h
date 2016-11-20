#ifndef __INTRO_SCENE__
#define __INTRO_SCENE__

#include "../Framework/Sprite.h"
#include "../Framework/SpriteManager.h"
#include "../Framework/Managers/SoundManager.h"
#include "../Framework/Managers/SceneManager.h"
#include "../Framework/InputController.h"
#include "../Framework/StopWatch.h"

#include "../Framework/IComponent.h"
#include "../Objects/BaseObject.h"
#include "../Objects/TextSprite.h"

#include "../Framework/Scene.h"

EVENT_RECEIVER
class IntroScene : public Scene, public IControlable
{
public:
	IntroScene();
	~IntroScene();

	bool init() override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;
	void updateInput(float deltatime) override;

private:
	Sprite* _yellowfancon;
	Sprite* _introtable;
	Movement* _movement;

	void onKeyPressed(KeyEventArg* key_event);
	StopWatch* _flash;
	StopWatch* _access;
	int _ok;
	bool _draw;
	bool _drawyellowFalcon;
	TextSprite* _playOption;
	TextSprite* _chosenOption;
};
#endif // !__INTRO_SCENE__
