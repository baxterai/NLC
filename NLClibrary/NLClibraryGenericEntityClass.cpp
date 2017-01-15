/*******************************************************************************
 *
 * This file is part of NLC.
 *
 * NLC is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * NLC is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with NLC. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryGenericEntityClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q11c 21-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryGenericEntityClass.hpp"

NLCgenericEntityClass::NLCgenericEntityClass(void)
{
	name = "NLCgenericEntity";
	#ifdef NLC_USE_MATH_OBJECTS
	value = numeric_limits<double>::quiet_NaN();
	#endif
	
	#ifdef NLC_USE_ENUM_LISTS 
	enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	#endif
};

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
unordered_map<string, string> enumTypeTableProperties;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
unordered_map<string, string> enumTypeTableConditions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_USE_ENUM_LISTS_ACTIONS
unordered_map<string, string> enumTypeTableActions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#endif

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
string calculateEnumTypeProperty(string entityName)
{
	string enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	unordered_map<string, string>::iterator enumTypeTablePropertiesIter = enumTypeTableProperties.find(entityName);
	if(enumTypeTablePropertiesIter != enumTypeTableProperties.end())
	{
		enumType = enumTypeTablePropertiesIter->second;
	}
	return enumType;
}
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
string calculateEnumTypeCondition(string entityName)
{
	string enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	unordered_map<string, string>::iterator enumTypeTableConditionsIter = enumTypeTableConditions.find(entityName);
	if(enumTypeTableConditionsIter != enumTypeTableConditions.end())
	{
		enumType = enumTypeTableConditionsIter->second;
	}
	return enumType;
}
#endif
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING
//must embed this function in NLCprintCodeBlocks.cpp code;
bool checkParentClassName(NLCgenericEntityClass* object, string className)
{
	bool result = false;
	if(object->name == className)
	{
		result = true;
	}
	for(vector<NLCgenericEntityClass*>::iterator iter1 = object->parentClassList.begin(); iter1 < object->parentClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* parent = *iter1;
		if(checkParentClassName(parent, className))
		{
			result = true;
		}
	}
	return result;
}

void addEntityToReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList, NLCgenericEntityClass* NLCgenericEntity, int sentenceIndex)
{
	referenceContextList.push_back(NLCgenericEntity);
	NLCgenericEntity->lastSentenceReferenced.push(sentenceIndex);
}

void clearReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = referenceContextList.begin(); iter1 < referenceContextList.end(); iter1++) 
	{
		NLCgenericEntityClass* NLCgenericEntity = *iter1;
		NLCgenericEntity->lastSentenceReferenced.pop();
	}
	referenceContextList.clear();
}
#endif

