// Nơi chứa các hàm hướng thủ tục.

#ifndef __UTILS_H__
#define __UTILS_H__

#include <d3dx9.h>
#include <string>
#include <vector>
#include "../Objects/BaseObject.h"
#include "define.h"
using namespace std;


// Kiểm tra hai hình chữ nhật có chồng lên nhau không.
// De-cac


bool isIntersectedInGame(RECT rect1, RECT rect2);

// Kiểm tra hai hình chữ nhật có chồng lên nhau không.
// Dùng trong hệ top left
bool isIntersectd(RECT rect1, RECT rect2);

// Kiểm tra rect1 có chứa rect2 không.
bool isContains(RECT rect1, RECT rect2);


// Tính khoảng cách giữa hai điểm
float getdistance(D3DXVECTOR2 p1, D3DXVECTOR2 p2);

std::vector<std::string> splitString(const std::string& input, char seperate);

//	Kiểm tra điểm có nằm trong hcn hay ko
bool isContain(RECT rect, D3DXVECTOR2 point);

double CalculateCoefficient(int n, int k);

using namespace pugi;

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


BaseObject* GetObjectByType(xml_node item, eID type)
{
	switch(type)
	{
	default:
		break;
	}
}

map<int, BaseObject*>* GetMapObjectFromFile(const string path)
{
	xml_document doc;
	map<int, BaseObject*>* mapObject = new map<int, BaseObject*>();

	auto result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return mapObject;
	}

	xml_node objectGroup = doc.child("map").child("objectgroup");
	if (objectGroup == NULL)
		return mapObject;

	auto objects = objectGroup.children();

	for (auto obj : objects)
	{
		int id = obj.attribute("id").as_int();
		auto type = obj.attribute("type").as_int();

		eID enumID;
		try {
			enumID = (eID)type;
		}
		catch (exception e) {
			continue;
		}

		BaseObject* baseObj = GetObjectByType(obj, enumID);

		if (obj != NULL)
			(*mapObject)[id] = baseObj;
	}
	return mapObject;
}

#endif // !__UTILS_H__
