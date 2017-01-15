#include "NLCgeneratedmoveClass.hpp"
#include "NLClibrary.hpp"

moveClass::moveClass(void)
{
	name = "move";
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("to", "land"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&toClasslandClassConditionList)));
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("NLCgenericEntity", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&NLCgenericEntityClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

