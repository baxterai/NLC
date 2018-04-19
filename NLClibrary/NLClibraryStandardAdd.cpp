/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardAdd.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f8a 18-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardAdd.hpp"
#include "NLClibraryStandardOperations.hpp"
#include "NLCgenerated.hpp"

//e.g. "Add the apple to the tree." / "Add the reference to the item's forwardReferenceClassList."
void addFunction(vector<NLCgenericEntityClass*>& addClassList, vector<NLCgenericEntityClass*>& addObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = addClassList.begin(); iter1 < addClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* addAction = *iter1;

		for(vector<NLCgenericEntityClass*>::iterator iter2 = addObjectClassList.begin(); iter2 < addObjectClassList.end(); iter2++) 
		{
			NLCgenericEntityClass* addObject = *iter2;
			
			//see redistributeStanfordRelationsConnectToAndFromConditions{} for necessary preprocessing of to conditions
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(addAction, NLC_LIBRARY_FUNCTION_ACTION_CONDITION_TO_NAME); 

			if(NLCgenericEntityToConditionList != NULL)
			{	
				//eg "Add the apple to the tree." / "Add the reference to the item's forwardReferenceClassList."
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter3 = NLCgenericEntityToConditionList->begin(); iter3 != NLCgenericEntityToConditionList->end(); iter3++)
				{
					NLCgenericEntityClass* toConditionObject = iter3->second;
					addPropertyGeneric(toConditionObject, addObject);
				}
			}
		}
	}
}




