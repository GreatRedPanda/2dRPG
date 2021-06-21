#include "stdafx.h"
#include "Rule.h"


Rule::Rule()
{
}


Rule::~Rule()
{
}
bool Rule::compareRule(string ruleStr)
{
	size_t offset = 0;

	string trst = "";
	for (auto &s : rule)
	{
		for (size_t i = 0; i < s.length(); i++)
		{
			char ch=s[i];
			if (ch == '-' || ruleStr[i + offset] == ch)
			{
				trst += ch;
				continue;
			}
			else
				return false;
		}
		offset += s.length();
	}
	return true;
}
Rule Rule::fromJson(const rapidjson::Value& doc)
{
	Rule rule=Rule();

	int size = doc["size"].GetInt();
	const  rapidjson::Value& a = doc["rule"];
	assert(a.IsArray());
	int rowCount=0;
	int columnCount = 0;
	//vector<string> row = vector<string>();
	for (size_t i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
	{
		//printf("a[%d] = %d\n", i, a[i].GetString());
       rule.rule.push_back(a[i].GetString());
		
		
	}

	//doc["rule"].GetArray();
	Tile t = Tile::loadJSON(doc["tile"]);
	rule.tile = t;
	return rule;
}