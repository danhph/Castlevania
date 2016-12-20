#include "myutils.h"

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

BaseObject* GetStart(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;


	auto start = new Start(x, y, width, height);
	start->init();
	start->setPosition(GVector2(x, y));
	start->setStatus((eStatus) stoi(properties["status"]));

	return start;
}

BaseObject* GetWall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;


	auto wall = new Wall(x, y, width, height);
	wall->init();
	return wall;
}

BaseObject* GetCandle(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;
	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;
	auto candle = new Candle(x, y);
	candle->init();
	return candle;
}

BaseObject* GetSoldier(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;
	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto ActiveBoundX = 2 * stoi(properties["ActiveBoundX"]);

	ActiveBoundX = ActiveBoundX + width / 2;
	
	auto soldier = new Soldier(x, y, ActiveBoundX);
	soldier->init();
	return soldier;
}

BaseObject* GetStairEnd(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto direct = false;
	if (properties["direct"] == "true")
		direct = true;

	auto stair = new StairEnd(x, y, width, height, direct);
	stair->init();
	return stair;
}

BaseObject* GetStair(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto direct = false;
	if (properties["direct"] == "true")
		direct = true;


	auto stair = new Stair(x, y, width, height, direct);
	stair->init();
	return stair;
}

BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight)
{
	switch (type)
	{
		case WALL:
			return GetWall(item, mapHeight);
			
		case STAIR:
			return GetStair(item, mapHeight);
		
		case STAIR_END:
			return GetStairEnd(item, mapHeight);

		case START:
			return GetStart(item, mapHeight);

		case CANDLE:
			return GetCandle(item, mapHeight);

		case SOLDIER:
			return GetSoldier(item, mapHeight);

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

	auto mapHeight = 2 * map.attribute("tileheight").as_int() * map.attribute("height").as_int();

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
