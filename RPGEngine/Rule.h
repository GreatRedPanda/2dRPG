#pragma once
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include "rapidjson.h"
#include "Document.h"
#include <vector>

class Rule
{

public:
	Rule();
	~Rule();
	Tile tile;
	vector< string> rule;

	rapidjson::Document getRuleJSON()
	{
		rapidjson::Value json_val;
		rapidjson::Document doc;
		auto &alloc = doc.GetAllocator();
		doc.SetObject();

		json_val.SetInt(rule.size());
		doc.AddMember("size", json_val, alloc);
		json_val.SetArray();
		for (auto &i : rule)
		{
			rapidjson::Value json_valStr;
			json_valStr.SetString(i.c_str(), alloc);
				json_val.PushBack(json_valStr, alloc);

		}	
		doc.AddMember("rule",json_val, alloc);
		json_val.CopyFrom(tile.saveJSON(), alloc);
		doc.AddMember("tile", json_val, alloc);
		return doc;
	}

	bool compareRule(string ruleStr);

	static Rule fromJson(const rapidjson::Value& doc);
};

