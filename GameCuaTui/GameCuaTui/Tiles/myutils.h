#ifndef __MYUTIL_H__
#define __MYUTIL_H__

#include "../Framework/define.h"
#include "../pugixml/pugixml.hpp"
#include "../Object/BaseObject.h"
#include <list>
#include "../Object/Door.h"
#include "../Object/Wall.h"
#include "../Object/BreakWall.h"
#include "../Object/BreakWall1.h"
#include "../Object/Stair.h"
#include "../Object/StairEnd.h"
#include "../Object/Start.h"
#include "../Object/End.h"
#include "../Object/Back.h"
#include "../Object/Revive.h"
#include "../Object/Soldier.h"
#include "../Object/Candle.h"
#include "../Object/Heart.h"
#include "../Object/BigHeart.h"
#include <ctime>
using namespace pugi;

map<string, string> GetObjectProperties(xml_node node);
BaseObject* GetStart(xml_node item, int mapHeight);
BaseObject* GetEnd(xml_node item, int mapHeight);
BaseObject* GetBack(xml_node item, int mapHeight);
BaseObject* GetRevive(xml_node item, int mapHeight);
BaseObject* GetDoor(xml_node item, int mapHeight);
BaseObject* GetWall(xml_node item, int mapHeight);
BaseObject* GetBreakWall(xml_node item, int mapHeight);
BaseObject* GetBreakWall1(xml_node item, int mapHeight);
BaseObject* GetStair(xml_node item, int mapHeight);
BaseObject* GetSoldier(xml_node item, int mapHeight);
BaseObject* GetStairEnd(xml_node item, int mapHeight);
BaseObject* GetCandle(xml_node item, int mapHeight);
BaseObject* GetHeart(xml_node item, int mapHeight);
BaseObject* GetBigHeart(xml_node item, int mapHeight);
BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight);
list<BaseObject*>* GetListObjectFromFile(const string path);

#endif