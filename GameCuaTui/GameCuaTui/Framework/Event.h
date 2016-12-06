#ifndef __EVENT_H__
#define __EVENT_H__
#include <vector>
using namespace std;
#include "define.h"
#include <functional>

class EventArg;
typedef void (*EventFunction)(EventArg*);

class Event
{
public:
	Event();
	virtual ~Event();
	virtual void fireEvent(EventArg* e); // active an event - kích hoạt sự kiện
	void operator+=(EventFunction pFunction); // regist an action - đăng kí sự kiện
	void operator-=(EventFunction pFucntion); // remove an action - huỷ sự kiện
private:
	vector<EventFunction> _listaction;
};

typedef Event* pEvent;

class EventArg
{
public:
	EventArg()
	{
	}

	virtual ~EventArg()
	{
	}
};


#endif // !__EVENT_H__
