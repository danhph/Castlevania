

#include "SoundManager.h"

SoundManager* SoundManager::_instance;

SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

void SoundManager::loadSound(HWND hWnd)
{
	// Khởi tạo CSoundManager.
	DirectSound_Init(hWnd);

	CSound* sound = nullptr;

	sound = LoadSound("Resources//Sounds//intro_scene.wav");
	_listSound[INTRO_SCENE] = sound;

	sound = LoadSound("Resources//Sounds//play_scene.wav");
	_listSound[PLAY_SCENE] = sound;

	sound = LoadSound("Resources//Sounds//over_scene.wav");
	_listSound[OVER_SCENE] = sound;

	sound = LoadSound("Resources//Sounds//open_scene.wav");
	_listSound[OPEN_DOOR] = sound;

	sound = LoadSound("Resources//Sounds//win_level.wav");
	_listSound[WIN_LEVEL] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[HIT_SOUND] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[DIE_SOUND] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[FALLING_WALL] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[AXE_SOUND] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[BOOMERANG_SOUND] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[CHANGE_STAGE] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[BOSS_SOUND] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[TIME_OUT] = sound;

	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[COLISION_SOUND] = sound;
	//
	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[GET_MONEY] = sound;
	//
	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[GET_HEART] = sound;
	//
	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[GET_POTION] = sound;
	//
	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[GET_CROSS] = sound;
	//
	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[GET_ITEM] = sound;
	//
	//sound = LoadSound("Resources//Sounds//intro_scene.wav");
	//_listSound[HIDDEN_ITEM_APPEAR] = sound;
}

bool SoundManager::IsPlaying(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}

void SoundManager::Play(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		PlaySound(sound);
		this->currentSound = sound;
	}
}
void SoundManager::PlayLoop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}
void SoundManager::Stop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		StopSound(sound);
	}
}

SoundManager::SoundManager()
{
	currentSound = nullptr;
}

SoundManager::~SoundManager()
{
}