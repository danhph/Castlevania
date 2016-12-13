#include "../Framework/define.h"
#include "../pugixml/pugixml.hpp"
#include "../Object/BaseObject.h"

using namespace pugi;

map<string, string> GetObjectProperties(pugi::xml_node node);

BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight);

list<BaseObject*>* GetListObjectFromFile(const string path);