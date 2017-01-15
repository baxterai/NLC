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
 * File Name: NLClibraryGenericEntityClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q8b 20-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#ifndef HEADER_NLC_LIBRARY_GENERIC_ENTITY_CLASS
#define HEADER_NLC_LIBRARY_GENERIC_ENTITY_CLASS

#include "../source/NLCglobalDefs.h"

#define NLC_ENUM_LIST_DEFAULT_TYPE "none"

class NLCgenericEntityClass
{
public:
	NLCgenericEntityClass(void);
	string name;
	stack<int> lastSentenceReferenced;
	vector<string> aliasList;
	#ifdef NLC_USE_MATH_OBJECTS
	double value;	//numerical value (0, 1, 2, 3, 4.56 etc)
	#endif
	
	unordered_map<string, vector<NLCgenericEntityClass*>*> propertyLists;
	vector<NLCgenericEntityClass*> propertyIncomingList;
	unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> conditionLists;
	unordered_map<string, NLCgenericEntityClass*> conditionIncomingList;
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionLists;
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionIncomingLists;
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionSubjectLists;
	unordered_map<string, vector<NLCgenericEntityClass*>*> actionObjectLists;

	#ifdef NLC_USE_ENUM_LISTS
	//used to store "enums" (ie properties which cannot exist along side other properties of the same enumType, eg red) 
	string enumType;
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*> enumPropertyLists;	//store property lists by enum type, eg none, colour, temperature (hot/cold), affect (sad/happy), valence (good/bad), state (on/off), etc
	#endif
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	unordered_map<tuple<string, string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> enumConditionLists;
	#endif
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*> enumActionLists;
	unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*> enumActionIncomingLists;
	#endif
	#endif
	
	vector<NLCgenericEntityClass*> parentClassList;
};

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
extern unordered_map<string, string> enumTypeTableProperties;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
extern unordered_map<string, string> enumTypeTableConditions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_USE_ENUM_LISTS_ACTIONS
extern unordered_map<string, string> enumTypeTableActions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#endif

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
string calculateEnumTypeProperty(string entityName);
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
string calculateEnumTypeCondition(string entityName);
#endif
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING
bool checkParentClassName(NLCgenericEntityClass* object, string className);
void addEntityToReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList, NLCgenericEntityClass* NLCgenericEntity, int sentenceIndex);
void clearReferenceContextList(vector<NLCgenericEntityClass*>& referenceContextList);
#endif

#endif
