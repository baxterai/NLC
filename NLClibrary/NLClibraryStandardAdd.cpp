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
 * File Name: NLClibraryStandardAdd.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1w3d 15-January-2017
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




