#ifndef __INPUT_CTRL_H__
#define __INPUT_CTRL_H__

#include "define.h"
#include "Graphics.h"
#include "Event.h"
#include <vector>
#include "define.h"

#define KEYBOARD_BUFFER_SIZE 1024

typedef LPDIRECTINPUT pGInput;
typedef LPDIRECTINPUTDEVICE8 pGKeyboard;

typedef void (*KeyEvent)(int);

class KeyEventArg : public EventArg
{
	// Dont need any private or protected.
public:
	KeyEventArg(int keycode) { _key = keycode; }
	int _key;
};

[event_source(native)]
class InputController
{
public:
	~InputController();

	static InputController* getInstance();
	static void release();

	bool init(HWND, HINSTANCE); // should be called in game::init()
	void update(); // should be called in main game loop
	int isKeyDown(int keycode); // check if keycode is down.
	bool isKeyPressed(int keycode);
	bool isKeyRelease(int keycode);

	Event _keyPressed;
	Event _keyReleased;

	// dùng marco __event thì có thể trỏ được đến các hàm thành viên của các lớp. nhưng cách sử dụng phức tạp hơn
	__event void __eventkeyPressed(KeyEventArg* e);
	__event void __eventkeyReleased(KeyEventArg* e);

private:

	static InputController* _instance;

	pGInput _input;
	pGKeyboard _keyboard;
	BYTE _keyBuffer[256]; // BYTE = unsigned char
	HWND _hWnd; // refference to another place. Dont release!!!
	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];

	InputController();

	bool _previousKeyBuffer[256];
};

typedef InputController* pInputController;


#endif // !__INPUT_CTRL_H__
