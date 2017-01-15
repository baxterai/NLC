/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryGenericEntityClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1r5o 15-August-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryGenericEntityClass.hpp"

NLCgenericEntityClass::NLCgenericEntityClass(void)
{
	name = "NLCgenericEntity";
	#ifdef NLC_USE_MATH_OBJECTS
	numericalValue = numeric_limits<double>::quiet_NaN();
	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
	#ifdef NLC_USE_MATH_OBJECTS_STRING
	textValue = "";
	#endif
	#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
	booleanValue = false;
	#endif
	#endif
	#endif
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	inverseConditionTwoWay = false;
	#endif
		
	#ifdef NLC_USE_ENUM_LISTS 
	enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	#endif
	
	#ifdef NLC_API
	thirdpartyAPIobject = NULL;
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

#ifdef NLC_SUPPORT_REDEFINITIONS
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
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
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

