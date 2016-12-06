#include "utils.h"
#include <list>
#include "../Object/Wall.h"

map<string, string> GetObjectProperties(xml_node node)
{
	map<string, string> properties;

	properties["x"] = node.attribute("x").as_string();
	properties["y"] = node.attribute("y").as_string();
	properties["width"] = node.attribute("width").as_string();
	properties["height"] = node.attribute("height").as_string();

	// parameters
	auto params = node.child("properties");
	if (params)
	{
		for (auto item : params)
		{
			auto key = item.attribute("name").as_string();
			auto value = item.attribute("value").as_string();
			properties[key] = value;
		}
	}

	return properties;
}


BaseObject* GetWall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto x = 2*stoi(properties["x"]);
	auto y = 2*stoi(properties["y"]);
	auto width = 2*stoi(properties["width"]);
	auto height = 2*stoi(properties["height"]);
	
	auto wall = new Wall(x, mapHeight - y - height, width, height);
	wall->init();
	return wall;
}

BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight)
{
	switch (type)
	{
		case WALL:
			GetWall(item, mapHeight);
		break;
		default:
			return nullptr;
	}
	
}

list<BaseObject*>* GetListObjectFromFile(const string path)
{
	xml_document doc;
	list<BaseObject*>* listObj = new list<BaseObject*>();

	auto result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return listObj;
	}
	auto map = doc.child("map");
	if (map == NULL)
		return listObj;
	
	auto mapHeight = map.attribute("tileheight").as_int()*map.attribute("height").as_int();

	xml_node objectGroup = map.child("objectgroup");
	if (objectGroup == NULL)
		return listObj;

	auto objects = objectGroup.children();

	for (auto obj : objects)
	{
		int id = obj.attribute("id").as_int();
		auto type = obj.attribute("type").as_int();

		eID enumID;
		try
		{
			enumID = (eID)type;
		}
		catch (exception e)
		{
			continue;
		}

		BaseObject* baseObj = GetObjectByType(obj, enumID, mapHeight);

		if (baseObj != NULL)
		{
			listObj->push_back(baseObj);
		}
	}
	return listObj;
}
