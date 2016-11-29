#ifndef __STAGE_21_H__
#define __STAGE_21_H__

#include "FrameWork/Sprite.h"
#include "FrameWork/SpriteManager.h"
#include "FrameWork/Managers/SceneManager.h"
#include "FrameWork/Text.h"
#include "FrameWork/Scenario.h"
#include "Framework/Scene.h"
#include "Objects/BaseObject.h"
#include "Objects/Player.h"
#include "Objects/Help.h"
#include "Framework/QNode.h"
#include "Tiles/TileMap.h"

using namespace std;
USE_GAMEUIT_FRAMEWORK

EVENT_RECEIVER
class Stage21 : public Scene
{
public:
	Stage21();
	~Stage21();

	bool init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;

	void setViewport(Viewport* viewport);

	BaseObject* getObject(eID id);

	Player* getPlayer();
private:
	void destroyobject(); // kiển tra nếu object hết hạn sử dụng thì phá huỷ đối tượng
	Text* _text;

	// Danh sách đối tượng dùng để tạo quadtree.
	map<string, BaseObject*> _mapObject;

	// Danh sách các đối tượng hoạt động rộng không thể đưa vào quadtree.
	vector<BaseObject*> _listObject;

	// Danh sách đối tượng nằm trong vùng active.
	// Mỗi vòng lặp sẽ được kiểm tra chỉnh sửa tại update, và sử dụng lại tại draw.
	vector<BaseObject*> _activeObject;

	vector<IControlable*> _listControlObject;

	TileMap* _tileMap;

	BaseObject* _player;

	void updateViewport(BaseObject* objTracker);

	bool checkGameLife();
};

#endif //
