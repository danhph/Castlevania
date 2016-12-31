#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "../Framework/Scene.h"
#include "../Object/BaseObject.h"
#include "../Framework/Text.h"
#include "../Tiles/TileMap.h"
#include "../Object/QuadtreeNode.h"
#include "../Object/Player.h"
#include <algorithm>
#include "../Framework/SoundManager.h"
#include "../Scene/IntroScene.h"
#include "../Object/Player.h"
#include "../Tiles/myutils.h"
#include "../Framework/StageManager.h"

using namespace std;

#define EFFECT_COLOR_1 D3DCOLOR_RGBA(255, 0, 255, 255)
#define EFFECT_COLOR_2 D3DCOLOR_RGBA(0, 255, 0, 255)

EVENT_RECEIVER
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	bool init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;

	void setViewport(Viewport* viewport);

	BaseObject* getObject(eID id);

	Player* getPlayer();

private:
	QuadTreeNode* _root;

	// Danh sách đối tượng nằm trong vùng active.
	// Mỗi vòng lặp sẽ được kiểm tra chỉnh sửa tại update, và sử dụng lại tại draw.
	vector<BaseObject*> _activeObject;

	TileMap* _tileMap;

	BaseObject* _player;

	void updateViewport(Player* player, float dt);

	bool checkEndGame();

	void initStage();

	eID _currentStage;


	bool _isPlayingMovie;

	bool _isCrossing;
	bool _crossingEffect;
	StopWatch* _crossStopWatch;
};

#endif //
