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
 * File Name: NLClibraryBaseExtended.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u12b 30-September-2016
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These extended functions are not generally hard coded (unlike those in 
 * NLClibraryBase) but are still dual licensed under AGPLv3 and BAI Commercial
 *
 *******************************************************************************/
 

#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
#include "NLClibraryStandardOperations.hpp"
#endif

//Base NLC library Functions (no generic property and condition lists)

#ifdef NLC_USE_LIBRARY_BASE_EXTENDED

template <class E1, class E2>
void addProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance)
{
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	addPropertyGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), static_cast<NLCgenericEntityClass*>(E2Instance));
	#else
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumProperty<E1, E2>(E1Instance, E2Instance);
	#endif
	E2propertyList->push_back(E2Instance);
	E2Instance->propertyIncomingList.push_back(E1Instance);
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	addEnumProperty<E1, E2>(E1Instance, E2Instance, reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2propertyList));
	#endif
	#endif
}

template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addCondition(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#else
void addCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#endif
{
	/*
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	#ifdef NLC_USE_ENUM_LISTS
	cout << "addCondition{} error: NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING:NLC_USE_ENUM_LISTS not yet implemented" << endl;
	#else
	#ifdef NLC_CONDITION_LISTS_VECTOR
	E2E3conditionList->push_back(new pair<string, E3*>(E2className, E3));
	E3->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(E2className, E1));	
	#else
	E2E3conditionList->insert(pair<string, E3*>(E2className, E3));
	E3->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(E2className, E1));	
	#endif
	#endif
	#else
	*/
	E2* condition = new E2();
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	addConditionGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), static_cast<NLCgenericEntityClass*>(condition), static_cast<NLCgenericEntityClass*>(E3Instance));	
	#else
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumCondition<E1, E2, E3>(E1Instance, condition->name, E3Instance);
	#endif
	#ifdef NLC_CONDITION_LISTS_VECTOR
	E2E3conditionList->push_back(new pair<E2*, E3*>(condition, E3Instance));
	E3Instance->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(condition->name, E1Instance));	//condition->name or use E2className
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	addEnumCondition<E1, E2, E3>(E1Instance, condition, E3Instance, reinterpret_cast<vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*>(E2E3conditionList));
	#endif	
	#else
	E2E3conditionList->insert(pair<E2*, E3*>(condition, E3Instance));
	E3Instance->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(condition->name, E1Instance));	//condition->name or use E2className
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	addEnumCondition<E1, E2, E3>(E1Instance, condition, E3Instance, reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(E2E3conditionList));
	#endif
	#endif
	#endif
	/*
	#endif
	*/
}

#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addConditionInverse(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#else
void addConditionInverse(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#endif
{
	/*
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	#ifdef NLC_USE_ENUM_LISTS
	cout << "addCondition{} error: NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING:NLC_USE_ENUM_LISTS not yet implemented" << endl;
	#else
	#ifdef NLC_CONDITION_LISTS_VECTOR
	E2E3conditionList->push_back(new pair<string, E3*>(E2className, E3));
	E3->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(E2className, E1));	
	#else
	E2E3conditionList->insert(pair<string, E3*>(E2className, E3));
	E3->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(E2className, E1));	
	#endif
	#endif
	#else
	*/
	E2* condition = new E2();
	condition->inverseConditionTwoWay = true;
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	addConditionGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), static_cast<NLCgenericEntityClass*>(condition), static_cast<NLCgenericEntityClass*>(E3Instance));	
	#else
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumCondition<E1, E2, E3>(E1Instance, condition->name, E3Instance);
	#endif
	#ifdef NLC_CONDITION_LISTS_VECTOR
	E2E3conditionList->push_back(new pair<E2*, E3*>(condition, E3Instance));
	E3Instance->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(condition->name, E1Instance));	//condition->name or use E2className
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	addEnumCondition<E1, E2, E3>(E1Instance, condition, E3Instance, reinterpret_cast<vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*>(E2E3conditionList));
	#endif	
	#else
	E2E3conditionList->insert(pair<E2*, E3*>(condition, E3Instance));
	E3Instance->conditionIncomingList.insert(pair<string, NLCgenericEntityClass*>(condition->name, E1Instance));	//condition->name or use E2className
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	addEnumCondition<E1, E2, E3>(E1Instance, condition, E3Instance, reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(E2E3conditionList));
	#endif
	#endif
	#endif
	/*
	#endif
	*/
}
#endif

template <class E1, class E2>
void addActionSubject(E1* E1action, E2* E2actionSubject, vector<E1*>* E1actionList, vector<E2*>* E2actionSubjectList)
{
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	addActionSubjectGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), static_cast<NLCgenericEntityClass*>(E2Instance));	//FINISHTHIS
	#else
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	clearExistingEnumActionSubject<E1, E2>(E1action, E2actionSubject);	//FINISHTHIS
	#endif
	E1actionList->push_back(E1action);
	E2actionSubjectList->push_back(E2actionSubject);
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	addEnumActionSubject<E1, E2>(E1action, E2actionSubject, reinterpret_cast<vector<NLCgenericEntityClass*>*>(E1actionList), reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2actionSubjectList));	//FINISHTHIS
	#endif
	#endif
}

template <class E1, class E2>
void addActionObject(E1* E1action, E2* E2actionObject, vector<E1*>* E1actionIncomingList, vector<E2*>* E2actionObjectList)
{
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	addActionSubjectGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), static_cast<NLCgenericEntityClass*>(E2Instance));	//FINISHTHIS
	#else
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	clearExistingEnumActionSubject<E1, E2>(E1action, E2actionObject);	//FINISHTHIS
	#endif
	E1actionIncomingList->push_back(E1action);
	E2actionObjectList->push_back(E2actionObject);
	#ifdef NLC_USE_ENUM_LISTS_ACTIONS
	addEnumActionSubject<E1, E2>(E1Instance, E2Instance, reinterpret_cast<vector<NLCgenericEntityClass*>*>(E1actionIncomingList), reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2actionObjectList));	//FINISHTHIS
	#endif
	#endif
}


template <class E1, class E2>
void removeProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance)
{
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	removePropertyGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), static_cast<NLCgenericEntityClass*>(E2Instance));
	#else
	#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
	clearExistingEnumProperty<E1, E2>(E1Instance, E2Instance);
	#endif
	//parse propertyIncomingList and remove reference to this property from them
	for(vector<NLCgenericEntityClass*>::iterator iter2 = E2Instance->propertyIncomingList.begin(); iter2 < E2Instance->propertyIncomingList.end(); ) 
	{
		NLCgenericEntityClass* propertyParent = *iter2;
		if(propertyParent == static_cast<NLCgenericEntityClass*>(E1Instance))
		{
			iter2 = E2Instance->propertyIncomingList.erase(iter2);
		}
		else
		{
			iter2++;
		}
	}
	removeItemFromVectorList<E2>(E2propertyList, E2Instance);	
	#endif
}

template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void removeCondition(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#else
void removeCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#endif
{
	E2 condition;
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	removeConditionGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), E2className, static_cast<NLCgenericEntityClass*>(E3Instance));	
	#else
	#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
	clearExistingEnumCondition<E1, E2, E3>(E1Instance, condition->name, E3Instance);
	#endif
	//parse conditionIncomingList and remove reference to this property from them
	for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = E3Instance->conditionIncomingList.begin(); iter2 != E3Instance->conditionIncomingList.end(); iter2++) 
	{
		string conditionIncomingName = iter2->first;
		NLCgenericEntityClass* conditionParent = iter2->second;
		if(conditionIncomingName == condition.name)	//condition->name or use E2className
		{
			if(conditionParent == static_cast<NLCgenericEntityClass*>(E1Instance))
			{
				iter2 = E3Instance->conditionIncomingList.erase(iter2);
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
	removeItemFromConditionList<E2, E3>(E2E3conditionList, condition->name, E3Instance);
	#endif
}	

template <class E1, class E2>
void removeProperties(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance)
{
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	vector<NLCgenericEntityClass*>* E2propertyListGeneric = reinterpret_cast<vector<NLCgenericEntityClass*>*>(E2propertyList);
	removeProperties(static_cast<NLCgenericEntityClass*>(E1Instance), E2propertyListGeneric);
	#else
	for(typename vector<E2*>::iterator iter1 = E2propertyList.begin(); iter1 < E2propertyList.end(); iter1++) 
	{
		E2* property = *iter1;
		#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
		clearExistingEnumProperty<E1, E2>(E1Instance, property);
		#endif
		//parse propertyIncomingList and remove reference to this property from them
		for(vector<NLCgenericEntityClass*>::iterator iter2 = property->propertyIncomingList.begin(); iter2 < property->propertyIncomingList.end(); ) 
		{
			NLCgenericEntityClass* propertyParent = *iter2;
			if(propertyParent == static_cast<NLCgenericEntityClass*>(E1Instance))
			{
				iter2 = property->propertyIncomingList.erase(iter2);
			}
			else
			{
				iter2++;
			}
		}	
	}
	E2propertyList.clear();
	#endif
}

template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void removeConditions(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#else
void removeConditions(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)	//NB E2className is redundant as it can be generated from new E2()
#endif
{
	#ifdef NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS
	#ifdef NLC_CONDITION_LISTS_VECTOR
	vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* E2E3conditionListGeneric = reinterpret_cast<vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*>(E2E3conditionList);	
	#else
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* E2E3conditionListGeneric = reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(E2E3conditionList);
	#endif
	removeConditionsGeneric(static_cast<NLCgenericEntityClass*>(E1Instance), E2E3conditionListGeneric);	
	#else
	#ifdef NLC_CONDITION_LISTS_VECTOR
	for(typename vector<pair<E2*, E3*>*>::iterator iter1 = E2E3conditionList.begin(); iter1 != E2E3conditionList.end(); iter1++) 	
	#else
	for(typename unordered_map<E2*, E3*>::iterator iter1 = E2E3conditionList.begin(); iter1 != E2E3conditionList.end(); iter1++) 
	#endif
	{
		#ifdef NLC_CONDITION_LISTS_VECTOR
		E2* condition = (*iter1)->first;
		E3* conditionObject = (*iter1)->second;		
		#else
		E2* condition = iter1->first;
		E3* conditionObject = iter1->second;
		#endif
		#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
		clearExistingEnumCondition<E1, E2, E3>(E1Instance, condition->conditionName, conditionObject);
		#endif
		//parse conditionIncomingList and remove reference to this condition from them
		for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = conditionObject->conditionIncomingList.begin(); iter2 != conditionObject->conditionIncomingList.end(); iter2++) 
		{
			NLCgenericEntityClass* conditionIncoming = iter2->first;
			NLCgenericEntityClass* conditionParent = iter2->second;
			if(conditionIncoming->name == condition->name)	//condition->name or use E2className
			{
				if(conditionParent == static_cast<NLCgenericEntityClass*>(E1Instance))
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
	}
	E2E3conditionList.clear();
	#endif
}


#ifdef NLC_USE_ENUM_LISTS

#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
template <class E1, class E2>
void addEnumProperty(E1* E1Instance, E2* E2Instance, vector<NLCgenericEntityClass*>* propertyList)
{
	unordered_map<string, string>::iterator enumTypeTablePropertiesIter = enumTypeTableProperties.find(E2Instance->name);
	if(enumTypeTablePropertiesIter != enumTypeTableProperties.end())
	{
		E2Instance->enumType = enumTypeTablePropertiesIter->second;
		E1Instance->enumPropertyLists.insert(pair<pair<string, string>*, vector<NLCgenericEntityClass*>*>(new pair<string, string>(E2Instance->enumType, E2Instance->name), propertyList));
	}	
}

template <class E1, class E2>
void clearExistingEnumProperty(E1* E1Instance, E2* E2Instance)
{
	string enumType = E2Instance->enumType;		//OR calculateEnumTypeProperty(E2Instance->name);
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		for(unordered_map<pair<string, string>*, vector<NLCgenericEntityClass*>*>::iterator enumPropertyListsIter = E1Instance->enumPropertyLists.begin(); enumPropertyListsIter != E1Instance->enumPropertyLists.end();) 
		{
			pair<string, string>* key = enumPropertyListsIter->first;
			if(key->first == enumType)
			{
				string propertyListName = key->second;	//NB an entity can have more than one enum type, eg a hot, blue, and healthy squirrel (where each enum type maps to an enumTypePropertyList) (but only one instance per enum type; ie blue and red, hot and cold, healthy and sick, etc is not allowed)
				vector<NLCgenericEntityClass*>* enumTypePropertyList = enumPropertyListsIter->second;
				for(vector<NLCgenericEntityClass*>::iterator iter1 = enumTypePropertyList->begin(); iter1 < enumTypePropertyList->end(); iter1++) 
				{
					//parse propertyIncomingList and remove reference to this property from them <- NB shouldnt be required because enum propertyLists should only contain qualities (eg colour, temperature, etc), and qualities should only be attached as properties of a single entity
					NLCgenericEntityClass* enumTypeProperty = *iter1;
					for(typename vector<NLCgenericEntityClass*>::iterator iter2 = enumTypeProperty->propertyIncomingList.begin(); iter2 < enumTypeProperty->propertyIncomingList.end(); ) 
					{
						NLCgenericEntityClass* parentEntity = *iter2;
						if(parentEntity == E1Instance)
						{
							iter2 = enumTypeProperty->propertyIncomingList.erase(iter2);
						}
						else
						{
							cout << "clearExistingEnumPropertyGeneric{} error: enum property (quality) detected which is a child (property) of more than one entity: entity = " << E1Instance->name << ", property = " << E2Instance->name << endl;
							exit(0);
							iter2++;
						}
					}
					if(!(enumTypeProperty->propertyLists.empty()))
					{
						cout << "clearExistingEnumProperty{} error: enum property (quality) detected which has one or more properties: entity = " << E1Instance->name << ", property = " << E2Instance->name << endl;
						exit(0);
					}
					if(!(enumTypeProperty->conditionLists.empty()))
					{
						cout << "clearExistingEnumProperty{} error: enum property (quality) detected which has one or more conditions: entity = " << E1Instance->name << ", property = " << E2Instance->name << endl;
						exit(0);
					}
					//enumTypeProperty->propertyIncomingList.clear();	//redundant
					delete enumTypeProperty;
				}
				enumPropertyListsIter = E1Instance->enumPropertyLists.erase(enumPropertyListsIter);
			}
			else
			{
				enumPropertyListsIter++;
			}				
		}
	}
}
#endif

#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* conditionList)
#else
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList)
#endif
{
	unordered_map<string, string>::iterator enumTypeTableConditionsIter = enumTypeTableConditions.find(E2Instance->name);
	if(enumTypeTableConditionsIter != enumTypeTableConditions.end())
	{
		E2Instance->enumType = enumTypeTableConditionsIter->second;
		#ifdef NLC_CONDITION_LISTS_VECTOR
		E1Instance->enumConditionLists.insert(pair<tuple<string, string, string>*, vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*>(new tuple<string, string, string>(E2Instance->enumType, E2Instance->name, E3Instance->name), conditionList));		
		#else
		E1Instance->enumConditionLists.insert(pair<tuple<string, string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new tuple<string, string, string>(E2Instance->enumType, E2Instance->name, E3Instance->name), conditionList));
		#endif
	}
}

template <class E1, class E2, class E3>
void clearExistingEnumCondition(E1* E1Instance, string E2className, E3* E3Instance)
{
	string enumType = calculateEnumTypeCondition(E2className);	//NB condition enum types are stored with condition, not with conditionObject
	if(enumType != NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM)
	{
		#ifdef NLC_CONDITION_LISTS_VECTOR
		for(unordered_map<tuple<string, string, string>*, vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>*>::iterator enumConditionListsIter = E1Instance->enumConditionLists.begin(); enumConditionListsIter != E1Instance->enumConditionLists.end();) 		
		#else
		for(unordered_map<tuple<string, string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator enumConditionListsIter = E1Instance->enumConditionLists.begin(); enumConditionListsIter != E1Instance->enumConditionLists.end();) 
		#endif
		{
			tuple<string, string, string>* key = enumConditionListsIter->first;
			if(get<0>(*key) == enumType)
			{
				string conditionName = get<1>(*key);
				string conditionObjectName = get<2>(*key);
				#ifdef NLC_CONDITION_LISTS_VECTOR
				vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* enumTypeConditionList = enumConditionListsIter->second;
				for(vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = enumTypeConditionList->begin(); iter1 != enumTypeConditionList->end(); iter1++) 	
				#else
				unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* enumTypeConditionList = enumConditionListsIter->second;
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter1 = enumTypeConditionList->begin(); iter1 != enumTypeConditionList->end(); iter1++) 
				#endif
				{
					//parse conditionIncomingList and remove reference to this condition from them
					#ifdef NLC_CONDITION_LISTS_VECTOR
					NLCgenericEntityClass* enumTypeCondition = (*iter1)->first;
					NLCgenericEntityClass* enumTypeConditionObject = (*iter1)->second;					
					#else
					NLCgenericEntityClass* enumTypeCondition = iter1->first;
					NLCgenericEntityClass* enumTypeConditionObject = iter1->second;
					#endif
					for(unordered_map<string, NLCgenericEntityClass*>::iterator iter2 = enumTypeConditionObject->conditionIncomingList.begin(); iter2 != enumTypeConditionObject->conditionIncomingList.end();) 
					{
						NLCgenericEntityClass* parentEntity = iter2->second;
						if(parentEntity == E1Instance)
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
				enumConditionListsIter = E1Instance->enumConditionLists.erase(enumConditionListsIter);
			}
			else
			{
				enumConditionListsIter++;
			}
		}
	}
}
#endif

#endif

template <class E1>
E1* addNewEntityToLocalList(vector<E1*>* E1classList)
{
	E1* entity = new E1();
	E1classList->push_back(entity);
	return entity;
}

template <class E1>
void addEntityToLocalList(vector<E1*>* E1classList, E1* E1Instance)
{
	E1classList->push_back(E1Instance);
}



template <class E1>
bool removeItemFromVectorList(vector<E1*>* vectorList, E1* itemToRemove)
{
	bool result = false;	
	typename vector<E1*>::iterator iter1 = find(vectorList->begin(), vectorList->end(), itemToRemove);
	if(iter1 != vectorList->end())
	{
		vectorList->erase(iter1);
		result = true;
	}
	
	/*inefficient:
	bool result = false;
	for(vector<E1*>::iterator iter1 = vectorList->begin(); iter1 < vectorList->end();) 
	{
		E1* itemTemp = *iter1;
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
	return result;
}


template <class E1, class E2>
#ifdef NLC_CONDITION_LISTS_VECTOR
bool removeItemFromConditionList(vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* conditionList, string conditionName, E2* itemToRemove)
#else
bool removeItemFromConditionList(unordered_map<E1*, E2*>* conditionList, string conditionName, E2* itemToRemove)
#endif
{
	bool result = false;
	
	/*efficient (NOT POSSIBLE);
	bool result = false;
	unordered_map<E1*, E2*>::iterator iter1 = find(itemToRemove->first);
	if(iter1 != conditionList.end())
	{
		conditionList.erase(iter1);
		result = true;
	}
	*/
		
	#ifdef NLC_CONDITION_LISTS_VECTOR
	for(typename vector<pair<E1*, E2*>*>::iterator iter1 = conditionList->begin(); iter1 != conditionList->end();) 	
	#else
	for(typename unordered_map<E1*, E2*>::iterator iter1 = conditionList->begin(); iter1 != conditionList->end();) 
	#endif
	{
		#ifdef NLC_CONDITION_LISTS_VECTOR
		NLCgenericEntityClass* first = (*iter1)->first;
		NLCgenericEntityClass* second = (*iter1)->second;
		#else
		NLCgenericEntityClass* first = iter1->first;
		NLCgenericEntityClass* second = iter1->second;		
		#endif
		if(first->name == conditionName)
		{
			if(second == itemToRemove)
			{
				iter1 = conditionList->erase(iter1);
				result = true;
			}
			else
			{
				iter1++;
			}
		}
		else
		{
			cout << "removeItemFromConditionList{} error: this function is designed to be used for conditionLists in which all entities in [first] are of the same name, and all in [second] are of the same name" << endl;
			iter1++;
		}
	}
	return result;
}

/*
template <class E1, class E2>
void removeObjectFromConditionList(unordered_map<E1*, E2*>* unorderedMap, E2 *objectToRemove)
{
	for(unordered_map<E1*, E2*>::iterator iter1 = unorderedMap.begin(); iter1 != unorderedMap.end();) 
	{
		E2* NLCgenericEntityClass* second = iter1->second;
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



#endif
