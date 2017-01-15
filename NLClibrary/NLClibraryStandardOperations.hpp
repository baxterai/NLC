/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * BAIPROJECT is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with BAIPROJECT. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardOperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u13a 02-October-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_STANDARD_OPERATIONS
#define HEADER_NLC_LIBRARY_STANDARD_OPERATIONS

#include "NLClibraryGenericEntityClass.hpp"

#define NLC_USE_LIBRARY_FUNCTION_ACTION_CONDITION_FROM_NAME "from"
#define NLC_USE_LIBRARY_FUNCTION_ACTION_CONDITION_TO_NAME "to"
#define NLC_USE_LIBRARY_FUNCTION_ACTIONOBJECT_PARENT_TEMP_VARIABLE_NAME "functionObjectParent"
#define NLC_USE_LIBRARY_FUNCTION_ACTIONOBJECT_CONDITION_AT_NAME "at"
#define NLC_USE_LIBRARY_FUNCTION_ACTIONOBJECT_CONDITION_IN_NAME "in"

//New NLC library Functions (generic property and condition lists) >= NLC1nXy

vector<NLCgenericEntityClass*>* getPropertyListByName(NLCgenericEntityClass* entity, string propertyName);
	vector<NLCgenericEntityClass*>* getVectorListByName(unordered_map<string, vector<NLCgenericEntityClass*>*>* vectorListAll, string vectorName);
vector<NLCgenericEntityClass*>* getActionListByName(NLCgenericEntityClass* entity, string actionName);
vector<NLCgenericEntityClass*>* getActionIncomingListByName(NLCgenericEntityClass* entity, string actionName);
vector<NLCgenericEntityClass*>* getActionSubjectListByName(NLCgenericEntityClass* entity, string entityName);
vector<NLCgenericEntityClass*>* getActionObjectListByName(NLCgenericEntityClass* entity, string entityName);
unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByName(NLCgenericEntityClass* entity, string conditionName, string conditionObjectName);
unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByConditionName(NLCgenericEntityClass* entity, string conditionName);

bool addPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity);
bool addConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject);
bool removePropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity);
bool removePropertyParentsGeneric(NLCgenericEntityClass* propertyEntity);
bool removeConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject);
bool removeConditionParentsGeneric(NLCgenericEntityClass* conditionObject);
bool removeConditionObjectsGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* conditionObject); 	//remove all conditions between entity and conditionObject

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
void addEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity, vector<NLCgenericEntityClass*>* propertyList);
void clearExistingEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity);
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
void addEnumConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList);
void clearExistingEnumConditionGeneric(NLCgenericEntityClass* entity, string conditionName, NLCgenericEntityClass* conditionObject);
#endif
#endif

bool removeItemFromVectorListGeneric(vector<NLCgenericEntityClass*>* vectorList, NLCgenericEntityClass* itemToRemove);
bool removeItemFromUnorderedMapGeneric(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* unorderedMap, string conditionName, NLCgenericEntityClass* itemToRemove);

#endif
