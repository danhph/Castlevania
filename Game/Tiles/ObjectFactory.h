

#ifndef __OBJECT_READER__
#define __OBJECT_READER__

#include "../FrameWork/define.h"
#include "../pugixml/pugixml.hpp"
#include "../objects/BaseObject.h"

using namespace pugi;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	static map<string, BaseObject*>* getMapObjectFromFile(const string path);
	static vector<BaseObject*>* getListObjectFromFile(const string path);
private: 
	static BaseObject* getObjectById(xml_node node, eID id);
	static BaseObject* getLand(xml_node node);
	static BaseObject* getRifleMan(xml_node node);
	static BaseObject* getSoldier(xml_node node);
	static BaseObject* getRedCannon(xml_node node);
	static BaseObject* getWallTurret(xml_node node);
	static BaseObject* getAirCraft(xml_node node);
	static BaseObject* getCreator(xml_node node);
	static BaseObject* getBridge(xml_node node);
	static BaseObject* getFalcon(xml_node node);
	static BaseObject* getGreatWall(xml_node node);
	static BaseObject* getRockFly(xml_node node);
	static BaseObject* getRockFall(xml_node node);
	static BaseObject* getScubaSoldier(xml_node node);
	static BaseObject* getFire(xml_node node);
	static BaseObject* getShadowBeast(xml_node node);
	
	static map<string, string> getObjectProperties(xml_node node);

};

#endif // !__OBJECT_READER__
