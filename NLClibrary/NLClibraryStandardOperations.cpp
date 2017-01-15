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
 * File Name: NLClibraryStandardOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p7a 07-July-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardOperations.h"

//New NLC library Functions (generic property and condition lists) >= NLC1nXy

vector<NLCgenericEntityClass*>* getPropertyListByName(NLCgenericEntityClass* entity, string propertyName)
{
	vector<NLCgenericEntityClass*>* propertyList = getVectorListByName(entity->propertyLists, string vectorName);
	return propertyList;
}

vector<NLCgenericEntityClass*>* getVectorListByName(unordered_map<string, vector<NLCgenericEntityClass*>*>* vectorListAll, string vectorName)
{
	vector<NLCgenericEntityClass*>* vectorList = NULL;
	for(unordered_map<string, vector<NLCgenericEntityClass*>*> ::iterator iter1 = vectorListAll.begin(); iter1 != vectorListAll.end(); iter1++) 
	{
		string key = iter1->first;
		if(key->first == vectorName)
		{
			vectorList = iter1->second;
		}
	}
	return vectorList;
}

vector<NLCgenericEntityClass*>* getActionListByName(NLCgenericEntityClass* entity, string propertyName)
{
	vector<NLCgenericEntityClass*>* actionList = getVectorListByName(entity->actionListAll, string vectorName);
	return actionList;
}
vector<NLCgenericEntityClass*>* getActionIncomingListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*>* actionIncomingList = getVectorListByName(entity->actionIncomingLists, string vectorName);
	return actionIncomingList;
}
vector<NLCgenericEntityClass*>* getActionSubjectListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*>* actionSubjectList = getVectorListByName(entity->actionSubjectLists, string vectorName);
	return actionSubjectList;
}
vector<NLCgenericEntityClass*>* getActionObjectListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*>* actionObjectList = getVectorListByName(entity->actionObjectLists, string vectorName);
	return actionObjectList;
}

unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByName(NLCgenericEntityClass* entity, string conditionName, string conditionObjectName) 
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = NULL;
	for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> ::iterator iter1 = entity->conditionLists.begin(); iter1 != entity->conditionLists.end(); iter1++) 
	{
		pair<string, string> key = iter1->first;
		if((key->first == conditionName) && (key->second == conditionObjectName))
		{
			conditionList = iter1->second;
		}
	}
	return conditionList;
}

unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* getConditionListByConditionName(NLCgenericEntityClass* entity, string conditionName) 
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = NULL;
	for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> ::iterator iter1 = entity->conditionLists.begin(); iter1 != entity->conditionLists.end(); iter1++) 
	{
		pair<string, string> key = iter1->first;
		if(key->first == conditionName)
		{
			conditionList = iter1->second;
		}
	}
	return conditionList;
}

bool addPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity)
{
	bool result = false;
	
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumPropertyGeneric(entity, propertyEntity);
	#endif
	
	vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(entity, propertyEntity->name);
	if(propertyList != NULL)
	{
		result = true;
		propertyList->push_back(propertyEntity);
		propertyEntity->propertyIncomingList.push_back(entity);
	}
	else
	{
		cout << "addPropertyGeneric{} error: !getPropertyListByName, entity = " << entity->name << ", propertyEntity = " << propertyEntity->name << endl;
	}
	
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	addEnumPropertyGeneric(entity, propertyEntity);
	#endif

	return result;
}
	
bool addConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject) 
{
	bool result = false;

	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumConditionGeneric(entity, condition->name, conditionObject);
	#endif
	
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = getConditionListByName(entity, condition->name, conditionObject->name);
	if(conditionList != NULL)
	{
		result = true;
		conditionList->insert(pair<NLCgenericEntityClass*, NLCgenericEntityClass*>(condition, conditionObject));
		conditionList->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(condition->name, entity));
	}
	else
	{
		cout << "addConditionGeneric{} error: !getConditionListByName, entity = " << entity->name << ", condition = " << condition->name << ", conditionObject = " << conditionObject->name << endl;
	}
	
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	addEnumConditionGeneric(entity, condition, conditionObject);
	#endif

	return result;
}


bool removePropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity)
{
	bool result = false;
	
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumPropertyGeneric(entity, propertyEntity);
	#endif
	
	vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(entity, propertyEntity->name);
	if(propertyList != NULL)
	{
		result = true;
		//parse propertyIncomingList and remove reference to this property from them
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyEntity->propertyIncomingList.begin(); iter2 < propertyEntity->propertyIncomingList.end(); ) 
		{
			NLCgenericEntityClass* propertyParent = *iter2;
			if(propertyParent == entity)
			{
				iter2 = propertyEntity->propertyIncomingList.erase(iter2);
			}
			else
			{
				iter2++;
			}
		}
		//note this is inefficient; getPropertyListByName has already determined this iter
		removeItemFromVectorList<NLCgenericEntityClass*>(propertyList, propertyEntity);
	}
	else
	{
		cout << "addPropertyGeneric{} error: !getPropertyListByName, entity = " << entity->name << ", propertyEntity = " << propertyEntity->name << endl;
	}

	return result;
}

bool removePropertyParentsGeneric(NLCgenericEntityClass* propertyEntity)
{
	bool result = false;
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = propertyEntity->propertyIncomingList.begin(); iter1 < propertyEntity->propertyIncomingList.end(); iter1++) 
	{
		NLCgenericEntityClass* entity = *iter1;
		#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
		clearExistingEnumPropertyGeneric(entity, propertyEntity);
		#endif

		vector<NLCgenericEntityClass*>* propertyList = getPropertyListByName(entity, propertyEntity->name);
		if(propertyList != NULL)
		{
			result = true;

			//note this is inefficient; getPropertyListByName has already determined this iter
			removeItemFromVectorList<NLCgenericEntityClass*>(propertyList, propertyEntity);
		}
		else
		{
			cout << "removePropertyParentsGeneric{} error: !getPropertyListByName, entity = " << entity->name << ", propertyEntity = " << propertyEntity->name << endl;
		}
	}
	
	propertyEntity->propertyIncomingList.clear();

	return result;
}
	
	
bool removeConditionGeneric(NLCgenericEntityClass* entity, string conditionName, NLCgenericEntityClass* conditionObject) 
{
	bool result = false;

	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumConditionGeneric(entity, conditionName, conditionObject);
	#endif
	
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = getConditionListByName(entity, conditionName, conditionObject->name);
	if(conditionList != NULL)
	{
		result = true;
		//parse conditionIncomingList and remove reference to this condition from them
		for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = conditionObject->conditionIncomingList.begin(); iter2 !=  conditionObject->conditionIncomingList.end(); iter2++) 
		{
			string conditionIncomingName = iter2->first;
			NLCgenericEntityClass* conditionParent = iter2->second;
			if(conditionIncomingName == conditionName)
			{
				if(conditionParent == entity)
				{
					iter2 = conditionObject->conditionIncomingList.erase(iter2);
				}
				else
				{
					iter2++;
				}
			}
			else
			{
				iter2++;
			}
		}
		//note this is inefficient; getConditionListByName has already determined this iter
		removeItemFromUnorderedMap<NLCgenericEntityClass*, NLCgenericEntityClass*>(conditionList, conditionName, conditionObject)
	}
	else
	{
		cout << "addConditionGeneric{} error: !getConditionListByName, entity = " << entity->name << ", condition = " << conditionName << ", conditionObject = " << conditionObject->name << endl;
	}

	return result;
}

bool removeConditionParentsGeneric(NLCgenericEntityClass* conditionObject)
{
	bool result = false;
	for(unordered_map<string, NLCgenericEntityClass*> ::iterator iter1 = conditionObject->conditionIncomingList.begin(); iter1 != conditionObject->conditionIncomingList.end(); iter1++)
	{
		NLCgenericEntityClass* entity = iter1->second;
		string conditionName = iter1->first;
			
		#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
		clearExistingEnumConditionGeneric(entity, conditionName, conditionObject);
		#endif

		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = getConditionListByName(entity, conditionName, conditionObject->name);
		if(conditionList != NULL)
		{
			result = true;

			//note this is inefficient; getConditionListByName has already determined this iter
			removeItemFromUnorderedMap<NLCgenericEntityClass*, NLCgenericEntityClass*>(conditionList, conditionName, conditionObject);
		}
		else
		{
			cout << "removeConditionParentsGeneric{} error: !getConditionListByName, entity = " << entity->name << ", condition = " << conditionName << ", conditionObject = " << conditionObject->name << endl;
		}
	}
	
	conditionObject->conditionIncomingList.clear();

	return result;
}


bool removeConditionObjectsGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* conditionObject) 	//remove all conditions between entity and conditionObject
{
	bool result = false;

	for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*> ::iterator iter1 = entity->conditionLists.begin(); iter1 != entity->conditionLists.end(); iter1++) 
	{
		pair<string, string> key = iter1->first;
		if(key->second == conditionObjectName)
		{
			conditionList = iter1->second;
			for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = conditionList.begin(); iter2 != conditionList.end();) 
			{
				if(iter2->second == conditionObject)
				{
					NLCgenericEntityClass* condition = iter2->first;
					
					#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
					clearExistingEnumConditionGeneric(entity, condition->name, conditionObject);
					#endif

					result = true;
					//parse propertyIncomingList and remove reference to this property from them
					for(unordered_map<string, NLCgenericEntityClass*>::iterator iter3 = conditionObject->conditionIncomingList.begin(); iter3 !=  conditionObject->conditionIncomingList.end(); iter3++) 
					{
						string conditionIncomingName = iter2->first;
						NLCgenericEntityClass* conditionParent = iter2->second;
						if(conditionIncomingName == conditionName)
						{
							if(conditionParent == entity)
							{
								iter3 = conditionObject->conditionIncomingList.erase(iter3);
							}
							else
							{
								iter3++;
							}
						}
						else
						{
							iter3++;
						}
					}
					
					//note this is inefficient; getConditionListByName has already determined this iter
					iter2 = conditionList.erase(iter2);
				}
				else
				{
					iter2++;
				}
			}
		}
	}

	return result;
}



#ifdef NLC_USE_ENUM_LISTS

#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
void addEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity, vector<NLCgenericEntityClass*>* propertyList)
{
	unordered_map<string, string>::iterator enumTypeTablePropertiesIter = enumTypeTableProperties.find(propertyEntity->name);
	if(enumTypeTablePropertiesIter != enumTypeTableProperties.end())
	{
		propertyEntity->enumType = enumTypeTablePropertiesIter->first;
		entity->enumPropertyLists.insert(pair<string, pair<string, vector<NLCgenericEntityClass*>*>>(propertyEntity->enumType, pair<string, vector<NLCgenericEntityClass*>*>(propertyEntity->name, propertyList)));
	}
}

void clearExistingEnumPropertyGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* propertyEntity)
{
	string enumType = propertyEntity->enumType;	//OR calculateEnumTypeProperty(propertyEntity->name);
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		unordered_map<string, unordered_map<string, vector<NLCgenericEntityClass*>*>>::iterator enumPropertyListsIter = entity->enumPropertyLists.find(enumType);
		if(enumPropertyListsIter != entity->enumPropertyLists.end())
		{//enumTypePropertyList found
			unordered_map<string, vector<NLCgenericEntityClass*>*>* enumTypePropertyLists = &(enumPropertyListsIter->second);

			for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator enumTypePropertyListsIter = enumTypePropertyLists->begin(); enumTypePropertyListsIter != enumTypePropertyLists->end(); enumTypePropertyListsIter++) 
			{
				string propertyListName = enumTypePropertyListsIter->first;	//NB an entity can have more than one enum type, eg a hot, blue, and healthy squirrel (where each enum type maps to an enumTypePropertyList) (but only one instance per enum type; ie blue and red, hot and cold, healthy and sick, etc is not allowed)
				//vector<NLCgenericEntityClass*>* enumTypePropertyList = getPropertyListByName(entity, propertyListName);
				vector<NLCgenericEntityClass*>* enumTypePropertyList = enumTypePropertyListsIter->second;
				
				for(vector<NLCgenericEntityClass*>::iterator iter1 = enumTypePropertyList.begin(); iter1 < enumTypePropertyList.end(); iter1++) 
				{
					//parse propertyIncomingList and remove reference to this property from them <- NB shouldnt be required because enum propertyLists should only contain qualities (eg colour, temperature, etc), and qualities should only be attached as properties of a single entity
					NLCgenericEntityClass* enumTypeProperty = *iter1;
					for(vector<E1*>::iterator iter2 = enumTypeProperty->propertyIncomingList.begin(); iter2 < enumTypeProperty->propertyIncomingList.end(); iter2++) 
					{
						parentEntity = *iter2;
						if(parentEntity != entity)
						{
							cout << "clearExistingEnumPropertyGeneric{} warning: enum property (quality) detected which is a child (property) of more than one entity: entity = " << entity->name << ", property = " << property->name << endl;
							vector<NLCgenericEntityClass*>* parentEntityPropertyList = getPropertyListByName(parentEntity, enumTypeProperty->name);
							removeItemFromVectorList(parentEntityPropertyList, enumTypeProperty);
						}
					}
					if(!(enumTypeProperty->propertyLists.empty())
					{
						cout << "clearExistingEnumPropertyGeneric{} error: enum property (quality) detected which has one or more properties: entity = " << entity->name << ", property = " << property->name << endl;
						exit(0);
					}
					if(!(enumTypeProperty->conditionLists.empty())
					{
						cout << "clearExistingEnumPropertyGeneric{} error: enum property (quality) detected which has one or more conditions: entity = " << entity->name << ", property = " << property->name << endl;
						exit(0);
					}
					//enumTypeProperty->propertyIncomingList.clear();	//redundant
					delete enumTypeProperty;
				}
				enumTypePropertyList.clear();
			}

			enumTypePropertyLists->clear();
		}
	}
	
}
#endif

#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
void addEnumConditionGeneric(NLCgenericEntityClass* entity, NLCgenericEntityClass* condition, NLCgenericEntityClass* conditionObject, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList) 
{
	unordered_map<string, string>::iterator enumTypeTableConditionsIter = enumTypeTableConditions.find(condition->name);
	if(enumTypeTableConditionsIter != enumTypeTableConditions.end())
	{
		condition->enumType = enumTypeTableConditionsIter->first;
		entity->enumConditionLists.insert(pair<string, pair<string, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>>(condition->enumType, pair<string, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(condition->name, conditionList)));
	}
}

void clearExistingEnumConditionGeneric(NLCgenericEntityClass* entity, string conditionName, NLCgenericEntityClass* conditionObject) 
{
	string enumType = calculateEnumTypeCondition(conditionName);	//NB condition enum types are stored with condition, not with conditionObject
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		unordered_map<string, unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>>::iterator enumConditionListsIter = entity->enumConditionLists.find(enumType);
		if(enumConditionListsIter != entity->enumConditionLists.end())
		{//enumTypePropertyList found
			unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* enumTypeConditionLists = &(enumConditionListsIter->second);

			for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*::iterator enumTypeConditionListsIter = enumTypeConditionLists->begin(); enumTypeConditionListsIter != enumTypeConditionLists->end(); enumTypeConditionListsIter++) 
			{
				pair<string, string>* key = enumTypeConditionListsIter->first;
				string conditionName = key->first;
				string conditionObjectName = key->second; 
				//unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* enumTypeConditionList = getConditionListByName(entity, conditionName, conditionObjectName);
				unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* enumTypeConditionList = enumTypeConditionListsIter->second;
				
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter1 = enumTypeConditionList.begin(); iter1 != enumTypeConditionList.end();) 
				{
					//parse conditionIncomingList and remove reference to this condition from them
					NLCgenericEntityClass* enumTypeCondition = iter1->first;
					NLCgenericEntityClass* enumTypeConditionObject = iter1->second;
					for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = enumTypeConditionObject->conditionIncomingList.begin(); iter2 < enumTypeConditionObject->conditionIncomingList.end();) 
					{
						parentEntity = iter2->second;
						if(parentEntity == entity)
						{
							iter2 = enumTypeConditionObject->conditionIncomingList.erase(iter2);
						}
						else
						{
							iter2++;
						}
					}
					delete enumTypeCondition;
				}
				enumTypeConditionList.clear();
			}

			enumTypeConditionLists->clear();
		}
	}
	
}
#endif
#endif

template <class E1>
bool removeItemFromVectorList(vector<E1*>* vectorList, E1* itemToRemove)
{
	bool result = false;	
	vector<E2*>::iterator iter1 = find(propertyList.begin(), propertyList.end(), propertyEntity);
	if(iter1 != propertyList.end())
	{
		propertyList.erase(iter1);
		result = true;
	}
	
	/*inefficient:
	bool result = false;
	for(vector<E1*>::iterator iter1 = vectorList.begin(); iter1 < vectorList.end();) 
	{
		itemTemp = *iter1;
		if(itemToRemove == itemTemp)
		{
			iter1 = vectorList->erase(iter1);
			result = true;
		}
		else
		{
			iter1++;
		}
	}
	*/
}

template <class E1, class E2>
bool removeItemFromUnorderedMap(unordered_map<E1*, E2*>* unorderedMap, string conditionName, E2* itemToRemove)
{
	/*efficient (NOT POSSIBLE);
	bool result = false;
	unordered_map<E1*, E2*>::iterator iter1 = find(itemToRemove->first);
	if(iter1 != unorderedMap.end())
	{
		unorderedMap.erase(iter1);
		result = true;
	}
	*/
		
	for(unordered_map<E1*, E2*>::iterator iter1 = unorderedMap.begin(); iter1 != unorderedMap.end();) 
	{
		NLCgenericEntityClass* first = iter1->first;
		NLCgenericEntityClass* second = iter1->second;
		if(first->name == conditionName)
		{
			if(second == itemToRemove)
			{
				iter1 = unorderedMap->erase(iter1);
				result = true;
			}
			else
			{
				iter1++;
			}
		}
		else
		{
			cout << "removeItemFromUnorderedMap{} error: this function is designed to be used for conditionLists in which all entities in [first] are of the same name, and all in [second] are of the same name" << endl;
			iter1++;
		}
	}
}

/*
template <class E1, class E2>
void removeObjectFromUnorderedMap(unordered_map<E1*, E2*>* unorderedMap, E2 *objectToRemove)
{
	for(unordered_map<E1*, E2*> ::iterator iter1 = unorderedMap.begin(); iter1 != unorderedMap.end();) 
	{
		NLCgenericEntityClass* second = iter1->second;
		if((itemToRemove->second == objectToRemove))
		{
			iter1 = unorderedMap->erase(iter1);
		}
		else
		{
			iter1++;
		}
	}
}
*/

