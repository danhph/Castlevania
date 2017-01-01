#ifndef _OVER_SCENE_
#define _OVER_SCENE_

#include "../Framework/Sprite.h"
#include "../Framework/SpriteManager.h"
#include "../Framework/SceneManager.h"
#include "../Framework/InputController.h"
#include "../Framework/StopWatch.h"

#include "../Framework/IComponent.h"
#include "../Object/BaseObject.h"
#include "../Object/TextSprite.h"
#include "../Object/Info.h"
#include "../Framework/Scene.h"

#include "PlayScene.h"
#include "IntroScene.h"

EVENT_RECEIVER
class OverScene : public Scene, public IControlable
{
public:
	OverScene(Info* info);
	~OverScene();

	bool init() override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;
	void updateInput(float deltatime) override;

private:
	StopWatch* _flash;
	StopWatch* _access;

	bool _ok;
	bool _choice;
	bool _draw;

	Sprite* _sprite;
	TextSprite* _gameover;
	TextSprite* _continue;
	TextSprite* _quit;	
	Info* _info;
};
#endif // !_OVER_SCENE_
