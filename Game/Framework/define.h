#ifndef __GAMEUIT_FRAMEWORK__
#define __GAMEUIT_FRAMEWORK__

#define _USE_MATH_DEFINES

#include <d3d9.h>		// d3d9.lib
#include <d3dx9.h>		// d3dx9.lib
#include <dinput.h>		// dinput8.lib, dxguid.lib
#include <dsound.h>		// dsound.lib

#include <windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include "utils.h"
using namespace std;

#define WINDOW_WIDTH 514
#define WINDOW_HEIGHT 450
#define SCALE_FACTOR 1.0f

#define C_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)				// màu trắnng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)				// màu khi mà load hình nó bỏ qua > trong suốt

enum eID
{
	PLAYER = 0,
	MAIN_MENU = 1,
	FONTFULL = 2,
	FONTEX = 3,
	LIFE_ICON = 4,

	MAP_STAGE_21 = 21,
};

enum eStatus
{
	NORMAL = 0, // 00000 = 0	
	MOVING_LEFT = (1 << 0), // 00001 = 2^0
	MOVING_RIGHT = (1 << 1), // 00010 = 2^1
	JUMPING = (1 << 2), // 00100 = 2^2
	LAYING_DOWN = (1 << 3), // 01000 = 2^3
	RUNNING = (1 << 4), // 10000 = 2^4
	LOOKING_UP = (1 << 5), // 2^5
	SHOOTING = (1 << 6),
	FALLING = (1 << 7),
};

enum eMouthStatus
{
};

enum eLandType
{
	GRASS,
	WATER,
	BRIDGELAND
};

enum eDirection
{
	NONE = 0,
	TOP = 1,
	BOTTOM = 2,
	LEFT = 4,
	RIGHT = 8,
	ALL = (TOP | BOTTOM | LEFT | RIGHT),
};

enum eAirCraftType
{
};

enum eMapType
{
	VERTICAL = 0,
	HORIZONTAL = 1
};

enum eBulletType
{
};

enum eSoundId
{
	INTRO,
};

enum eWT_Status
{
};

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)
#define VECTOR2ONE  GVector2(1.0f, 1.0f)

#define EVENT_RECEIVER [event_receiver(native)]

#define GAMEUIT_FRAMEWORK		namespace Framework

#define GAMEUIT_FRAMEWORK_BEGIN	{

#define GAMEUIT_FRAMEWORK_END	}

#define USE_GAMEUIT_FRAMEWORK		using namespace Framework;

#ifndef SAFE_DELETE

#define SAFE_DELETE(p) \
if(p) \
{\
	delete (p); \
	p = nullptr; \
} \

#endif // !SAFE_DELETE


#endif // !__GAMEUIT_FRAMEWORK__
