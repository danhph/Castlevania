#ifndef __CASTLEVANIA_GAME_H__
#define __CASTLEVANIA_GAME_H__

#include "Game.h"
#include "Framework/SpriteManager.h"
#include "Framework/define.h"
#include "Framework/SceneManager.h"
#include "Framework/SoundManager.h"
#include "Scene/IntroScene.h"
#include "Scene/PlayScene.h"
#include "Scene/OverScene.h"
#include "Framework/StageManager.h"

class CastlevaniaGame : public Game
{
public:
	CastlevaniaGame(HINSTANCE hInstance, LPWSTR title);
	~CastlevaniaGame();

	void init();						// init your objects
	void release();						// release your objects

	void updateInput(float deltatime);	// update input, include played objects and menu button
	void update(float deltatime);		// update your objects
	void draw();						// draw your objects
	void loadResource();

private:

};

#endif // !__CASTLEVANIA_GAME_H__
