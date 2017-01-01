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

BaseObject* GetEnd(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;


	auto end = new End(x, y, width, height);
	end->setNextStage((eID)stoi(properties["next"]));
	end->setStatus((eStatus)stoi(properties["status"]));
	return end;
}

BaseObject* GetBack(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;


	auto back = new Back(x, y, width, height);
	back->setNextStage((eID)stoi(properties["next"]));
	return back;
}

BaseObject* GetRevive(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;


	auto end = new Revive(x, y, width, height);
	return end;
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
	start->setStatus((eStatus) stoi(properties["status"]));

	return start;
}

BaseObject* GetFrogRange(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;


	auto range = new FrogRange(x, y, width, height);
	range->init();
	return range;
}

BaseObject* GetBirdRange(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;


	auto birdRange = new BirdRange(x, y, width, height);
	birdRange->init();
	return birdRange;
}

BaseObject* GetDoor(xml_node item, int mapHeight)
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
	auto door = new Door(x, y);
	door->init();
	return door;
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

BaseObject* GetDinosaur(xml_node item, int mapHeight)
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

	auto dinosaur = new Dinosaur(x, y);
	dinosaur->init();
	return dinosaur;
}

BaseObject* GetTrident(xml_node item, int mapHeight)
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
	BaseObject* trident;
	if (properties["half"] != "")
		trident = new Trident(x, y, false);
	else
		trident = new Trident(x, y);
	trident->init();
	return trident;
}

BaseObject* GetBlueBat(xml_node item, int mapHeight)
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
	auto blueBat = new BlueBat(x, y);
	blueBat->init();
	return blueBat;
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
	BaseObject* candle = nullptr;
	if (properties["item"] != "")
		candle = new Candle(x, y, (eID) stoi(properties["item"]));
	else
		candle = new Candle(x, y);
	candle->init();
	return candle;
}

BaseObject* GetBreakWall1(xml_node item, int mapHeight)
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
	auto breakWall = new BreakWall1(x, y);
	breakWall->init();
	return breakWall;
}

BaseObject* GetBreakWall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;
	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);

	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 4;
	auto breakWall = new BreakWall(x, y);
	breakWall->init();
	return breakWall;
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

BaseObject* GetMedusa(xml_node item, int mapHeight)
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

	auto checkPoint = 2 * stoi(properties["checkPoint"]);

	auto next = (eID)stoi(properties["next"]);

	auto medusa = new Medusa(x, y, checkPoint, next);
	medusa->init();
	return medusa;
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

BaseObject* GetMovingStair(xml_node item, int mapHeight)
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

	auto movingStair = new MovingStair(x, y, ActiveBoundX);
	movingStair->init();
	return movingStair;
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

BaseObject* GetHeart(xml_node item, int mapHeight)
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

	auto heart = new Heart(x, y);
	heart->init();
	return heart;
}

BaseObject* GetBigHeart(xml_node item, int mapHeight)
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

	auto bigHeart = new BigHeart(x, y);
	bigHeart->init();
	return bigHeart;
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
		case MOVING_STAIR:
			return GetMovingStair(item, mapHeight);

		case START:
			return GetStart(item, mapHeight);
		case BACK:
			return GetBack(item, mapHeight);
		case END:
			return GetEnd(item, mapHeight);

		case CANDLE:
			return GetCandle(item, mapHeight);
		case TRIDENT:
			return GetTrident(item, mapHeight);
		case DINOSAUR:
			return GetDinosaur(item, mapHeight);
		case SOLDIER:
			return GetSoldier(item, mapHeight);
		case BLUEBAT:
			return GetBlueBat(item, mapHeight);
		case BIRD_RANGE:
			return GetBirdRange(item, mapHeight);
		case FROG_RANGE:
			return GetFrogRange(item, mapHeight);

		case MEDUSA:
			return GetMedusa(item, mapHeight);

		case REVIVE:
			return GetRevive(item, mapHeight);
		case DOOR:
			return GetDoor(item, mapHeight);

		case BREAKWALL:
			return GetBreakWall(item, mapHeight);
		case BREAKWALL1:
			return GetBreakWall1(item, mapHeight);

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

		auto baseObj = GetObjectByType(obj, enumID, mapHeight);

		if (baseObj != nullptr)
		{
			listObj->push_back(baseObj);
		}
	}
	return listObj;
}
