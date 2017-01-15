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
 * File Name: NLClibraryStandardCopy.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q12a 22-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "../NLClibrary/NLClibraryStandardCopy.hpp"
#include "../NLClibrary/NLClibraryStandardOperations.hpp"
#include "../NLCgenerated/NLCgenerated.hpp"

//e.g. Copy the chicken [from the pie] to the apple.
void copyFunction(vector<NLCgenericEntityClass*>& copyClassList, vector<NLCgenericEntityClass*>& copyObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = copyClassList.begin(); iter1 < copyClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* copyAction = *iter1;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityFromConditionList = getConditionListByConditionName(copyAction, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_FROM_NAME); 
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(copyAction, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_TO_NAME); 

		if(NLCgenericEntityToConditionList != NULL)	//this will fail with Stanford NLP until * has been implemented
		{
			for(vector<NLCgenericEntityClass*>::iterator iter3 = copyObjectClassList.begin(); iter3 < copyObjectClassList.end(); iter3++) 
			{
				NLCgenericEntityClass* copyObject = *iter3;
				NLCgenericEntityClass* copyOfCopyObject = copyObjectAndChildren(copyObject);
				bool copyObjectFound = true;	//always true as linkEntitiesDynamicFromConditions will have linked the copy object as the child of the copy function from condition object, and the copy object parent will already have been parsed by NLC before executing the copy funciton

				if(copyObjectFound)
				{
					for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter4 = NLCgenericEntityToConditionList->begin(); iter4 != NLCgenericEntityToConditionList->end(); iter4++)
					{
						NLCgenericEntityClass* toConditionObject = iter4->second;
  						addPropertyGeneric(toConditionObject, copyOfCopyObject);
						#ifdef NLC_DEBUG_LIBRARY
						cout << "copy() pass: copyParentOld (fromConditionObject) = " << fromConditionObject->name << ", copyOfCopyObject = " << copyOfCopyObject->name << "copyParentNew (toConditionObject) = " << toConditionObject->name << endl;
						#endif
					}
				}
				else
				{
					cout << "copy() error: copy object not not found" << endl;
				}
			}
		}
		else
		{
			cout << "copy() error: copy action 'to' condition not found" << endl;
		}
	}
}

NLCgenericEntityClass* copyObjectAndChildren(NLCgenericEntityClass* objectToCopy)
{
	NLCgenericEntityClass* copyOfCopyObject = copyObjectAndProperties(objectToCopy);
	#ifdef NLC_USE_LIBRARY_COPY_FUNCTION_COPY_INTERNAL_CONDITION_LISTS
	copyConditionLinks(objectToCopy, objectToCopy, copyOfCopyObject);
	#endif
}


NLCgenericEntityClass* copyObjectAndProperties(NLCgenericEntityClass* objectToCopy)
{
	NLCgenericEntityClass* copyOfCopyObject = copyObjectByName(objectToCopy->name, objectToCopy);
	
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = objectToCopy->propertyLists.begin(); iter1 != objectToCopy->propertyLists.end(); iter1++) 
	{
		vector<NLCgenericEntityClass*>* propertyList = iter1->second;
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
		{
			NLCgenericEntityClass* property = *iter2;
			NLCgenericEntityClass* copyOfProperty = copyObjectAndChildren(property);
			addPropertyGeneric(copyOfCopyObject, copyOfProperty);
		}
	}
	
	return copyOfCopyObject;
}

#ifdef NLC_USE_LIBRARY_COPY_FUNCTION_COPY_INTERNAL_CONDITION_LISTS
void copyConditionLinks(NLCgenericEntityClass* objectToCopyTopLevel, NLCgenericEntityClass* objectToCopy, NLCgenericEntityClass* copyOfCopyObject)
{
	unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1B = copyOfCopyObject->propertyLists.begin();
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = objectToCopy->propertyLists.begin(); iter1 != objectToCopy->propertyLists.end(); iter1++)
	{
		vector<NLCgenericEntityClass*>* propertyList = iter1->second;
		vector<NLCgenericEntityClass*>* propertyListB = iter1B->second;
		vector<NLCgenericEntityClass*>::iterator iter2B = propertyListB->begin();
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
		{
			NLCgenericEntityClass* property = *iter2;
			NLCgenericEntityClass* propertyB = *iter2B;
			copyConditionLinks(objectToCopyTopLevel, property, propertyB);
			iter2B++;
		}
		iter1B++;
	}
	
	//only copy conditions which refer to properties contained in the copy hierachy
	for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = objectToCopy->conditionLists.begin(); iter1 != objectToCopy->conditionLists.end(); iter1++) 
	{
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = iter1->second;
		for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = conditionList->begin(); iter2 != conditionList->end(); iter2++) 
		{		
			NLCgenericEntityClass* condition = iter2->first;
			NLCgenericEntityClass* conditionObject = iter2->second;
			if(findObjectInPropertyHierarchy(objectToCopyTopLevel, conditionObject))
			{
				NLCgenericEntityClass* copyOfCondition = copyObjectByName(condition->name, condition);	//conditions (ie condition types) are just copied in isolation
				NLCgenericEntityClass* copyOfConditionObject = conditionObject;
				addConditionGeneric(copyOfCopyObject, copyOfCondition, copyOfConditionObject);	
			}
		}
	}	
}

bool findObjectInPropertyHierarchy(NLCgenericEntityClass* object, NLCgenericEntityClass* objectToFind)
{
	bool result = false;
	for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = object->propertyLists.begin(); iter1 != object->propertyLists.end(); iter1++) 
	{
		vector<NLCgenericEntityClass*>* propertyList = iter1->second;
		for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
		{
			NLCgenericEntityClass* property = *iter2;
			if(property == objectToFind)
			{
				result = true;
			}
			else
			{
				if(findObjectInPropertyHierarchy(property, objectToFind))
				{
					result = true;
				}
			}
		}
	}
	
	return result;
}

#endif


