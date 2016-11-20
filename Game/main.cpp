#include <Windows.h>
#include <iostream>
#include "CastlevaniaGame.h"

using namespace std;
USE_GAMEUIT_FRAMEWORK

#define APP_TITTLE L"Contra"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine,  int nCmdShow)
{
	Game* myGame;
	myGame = new CastlevaniaGame(hInstance, APP_TITTLE);

	myGame->init();
	myGame->run();
	myGame->release();

	delete myGame;
}