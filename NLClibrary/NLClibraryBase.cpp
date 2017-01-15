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
 * File Name: NLClibraryBase.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q8b 20-August-2015
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These functions are hard coded and dual licensed under AGPLv3 and BAI Commercial
 *
 *******************************************************************************/
 
//Base NLC library Functions (no generic property and condition lists)

template <class E1, class E2>
void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0)
{
	if(!(find(entityCategoryList.begin(), entityCategoryList.end(), entity0) != entityCategoryList.end()))
	{
		entityCategoryList.push_back(entity0);
	}
}

template <class E1, class E2>
vector<E2*>& castVector(vector<E1*>& E1List)
{
	vector<E2*>& E2List = reinterpret_cast<vector<E2*>& >(E1List);
	return E2List;
}

//not currently used
template <class E1, class E2, class E3, class E4>
unordered_map<E3*, E4*>& castUnorderedMap(unordered_map<E1*, E2*>& E1E2List)
{
	unordered_map<E3*, E4*>& E3E4List = reinterpret_cast<unordered_map<E3*, E4*>& >(E1E2List);
	return E3E4List;
}





#ifdef NLC_USE_ADVANCED_REFERENCING
template <class E1, class E2>
void addToCategoryIfPassSingularDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0)
{
	if(!(entity0->lastSentenceReferenced.empty()))
	{
		if(entityCategoryList.empty())
		{
			entityCategoryList.push_back(entity0);
		}
		else
		{
			if(entity0->lastSentenceReferenced.top() > (entityCategoryList.back())->lastSentenceReferenced.top())
			{
				entityCategoryList.clear();
				entityCategoryList.push_back(entity0);
			}
			else if(entity0->lastSentenceReferenced.top() == (entityCategoryList.back())->lastSentenceReferenced.top())
			{
				if(!(find(entityCategoryList.begin(), entityCategoryList.end(), entity0) != entityCategoryList.end()))
				{
					entityCategoryList.push_back(entity0);
				}
			}
			else
			{
			}
		}
	}
	//Singular definite plurality tests
	if(entityCategoryList.size() > 1)
	{
		cout << "Execution warning: multiple objects have been added to a singular definite variable (category) - should the entity have been defined as plural instead?" << endl;
	}
}

template <class E1>
void findAliasAndAddToCategoryList(vector<E1*>& E1List, string aliasName, vector<E1*>& E1CategoryList)
{
	for(typename vector<E1*>::iterator iter1 = E1List.begin(); iter1 < E1List.end(); iter1++) 
	{
		E1* NLCgenericEntity = *iter1;
		if((find(NLCgenericEntity->aliasList.begin(), NLCgenericEntity->aliasList.end(), aliasName) != NLCgenericEntity->aliasList.end()))
		{
			E1CategoryList.push_back(NLCgenericEntity);
		}
	}
}

template <class E1>
bool findAlias(E1* E1Instance, string aliasName)
{
	bool result = false;
	if((find(E1Instance->aliasList.begin(), E1Instance->aliasList.end(), aliasName) != E1Instance->aliasList.end()))
	{
		result = true;
	}
	return result;
}

#endif



