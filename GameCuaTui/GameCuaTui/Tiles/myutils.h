#ifndef __MYUTIL_H__
#define __MYUTIL_H__

#include "../Framework/define.h"
#include "../pugixml/pugixml.hpp"
#include "../Object/BaseObject.h"
#include <list>
#include "../Object/Wall.h"
#include "../Object/Stair.h"
#include "../Object/StairEnd.h"
#include "../Object/Start.h"
#include "../Object/Soldier.h"
#include "../Object/Candle.h"

using namespace pugi;

map<string, string> GetObjectProperties(xml_node node);
BaseObject* GetStart(xml_node item, int mapHeight);
BaseObject* GetWall(xml_node item, int mapHeight);
BaseObject* GetStair(xml_node item, int mapHeight);
BaseObject* GetSoldier(xml_node item, int mapHeight);
BaseObject* GetStairEnd(xml_node item, int mapHeight);
BaseObject* GetCandle(xml_node item, int mapHeight);
BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight);
list<BaseObject*>* GetListObjectFromFile(const string path);

#endif