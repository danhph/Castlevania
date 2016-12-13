#include "../Framework/define.h"
#include "../pugixml/pugixml.hpp"
#include "../Object/BaseObject.h"

using namespace pugi;

list<BaseObject*>* GetListObjectFromFile(const string path);