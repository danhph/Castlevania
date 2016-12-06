

#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__
#include "define.h"
#include "dxaudio.h"

#include <map>
#include <wincon.h>

using namespace std;
class SoundManager
{
public:
	~SoundManager();
	static SoundManager* getInstance();
	void loadSound(HWND hWnd);
	void Play(eSoundId);
	void Stop(eSoundId);
	void PlayLoop(eSoundId);
	bool IsPlaying(eSoundId);
private:
	SoundManager();
	static SoundManager* _instance;
	map<eSoundId, CSound*> _listSound;
	CSound* currentSound;
	float volume;
};

#endif // !__SOUND_MANAGER__
