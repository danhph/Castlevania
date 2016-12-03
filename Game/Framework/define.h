#ifndef __GAMEUIT_FRAMEWORK__
#define __GAMEUIT_FRAMEWORK__

#define _USE_MATH_DEFINES

#include <d3d9.h>		
#include <d3dx9.h>	
#include <dinput.h>		
#include <dsound.h>		
#include <windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include "utils.h"
using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 450
#define SCALE_FACTOR 1.0f

#define COLOR_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)				// màu trắnng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)				


#define MAX_OBJECTS 4
#define MAX_LEVELS 32

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
	NORMAL = 0,
	MOVING_LEFT = (1 << 0),
	MOVING_RIGHT = (1 << 1),
	JUMPING = (1 << 2),
	RUNNING = (1 << 3),
};

enum eLandType
{
	LAND,
	WALL,
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

enum eSoundId
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
